/**
MIT License

Copyright (c) 2021 HeatXD

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#include "zphysics.h"
#include "flecs.h"
#include <stdio.h>

// Declare components globally in this file
ECS_COMPONENT_DECLARE(ZPPosition);
ECS_COMPONENT_DECLARE(ZPVelocity);
ECS_COMPONENT_DECLARE(ZPAcceleration);
ECS_COMPONENT_DECLARE(ZPSize);
ECS_COMPONENT_DECLARE(ZPMass);

// Declare Rectangle type globally
ECS_TYPE_DECLARE(ZPRectangle);

int zp_world_setup(ZPWorld* zpw){
    // Create The ecs world 
    zpw->world = ecs_init();
    // define components
    ECS_COMPONENT_DEFINE(zpw->world, ZPPosition);
    ECS_COMPONENT_DEFINE(zpw->world, ZPVelocity);
    ECS_COMPONENT_DEFINE(zpw->world, ZPAcceleration);
    ECS_COMPONENT_DEFINE(zpw->world, ZPSize);
    ECS_COMPONENT_DEFINE(zpw->world, ZPMass);
    // Define rectangle type
    ECS_TYPE_DEFINE(zpw->world, ZPRectangle, ZPPosition, ZPVelocity, ZPAcceleration, ZPSize, ZPMass);
    // Get the ZPRectangle Table for later operations and all the needed columns
    zpw->rect_table = ecs_table_from_type(zpw->world, ecs_type(ZPRectangle));
    zpw->rect_cols.pos_col = ecs_table_find_column(zpw->rect_table, ecs_typeid(ZPPosition));
    zpw->rect_cols.vel_col = ecs_table_find_column(zpw->rect_table, ecs_typeid(ZPVelocity));
    zpw->rect_cols.accel_col = ecs_table_find_column(zpw->rect_table, ecs_typeid(ZPAcceleration));
    zpw->rect_cols.size_col = ecs_table_find_column(zpw->rect_table, ecs_typeid(ZPSize));
    zpw->rect_cols.mass_col = ecs_table_find_column(zpw->rect_table, ecs_typeid(ZPMass));
    // Create the pipeline phases
    ECS_TAG(zpw->world, ZPWDynamics);
    ECS_TAG(zpw->world, ZPWCollisions);
    // Create the pipeline
    ECS_PIPELINE(zpw->world, ZPWPipeline, ZPWDynamics, ZPWCollisions);
    // Set the world to use the pipeline
    ecs_set_pipeline(zpw->world, ZPWPipeline);
    // ZPWDynamics systems
    ECS_SYSTEM(zpw->world, zp_rect_dynamics, ZPWDynamics, ZPPosition, ZPVelocity, ZPAcceleration);
    //..
    return 0;
}

void zp_rect_dynamics(ecs_iter_t* it){
    ZPPosition* zpp = ecs_column(it, ZPPosition, 1);
    ZPVelocity* zpv = ecs_column(it, ZPVelocity, 2);
    ZPAcceleration* zpa = ecs_column(it, ZPAcceleration, 3);
    
    for (int i = 0; i < it->count; i++){
        // Update Velocity
        zpv[i].x += (zpa[i].x * it->delta_time);
        zpv[i].y += (zpa[i].y * it->delta_time);
        // Update Position
        zpp[i].x += (zpv[i].x * it->delta_time);
        zpp[i].y += (zpv[i].y * it->delta_time);
    }
}

int zp_world_step(ZPWorld* zpw, float dt){
    // Advance ZPWorld
    return ecs_progress(zpw->world, dt);    
}

int zp_world_stop(ZPWorld* zpw){
    // Clean up resources
    return ecs_fini(zpw->world);
}
int zp_get_entity_rect_count(ZPWorld* zpw){
    // Get the count of active rectangles in the world
    return ecs_count(zpw->world, ZPRectangle);
}
ZPEntity zp_world_create_rect(ZPWorld* zpw){
    // Create a new rectangle and return this entity
    return ecs_new(zpw->world, ZPRectangle);
}

void zp_rect_set_position(ZPWorld* zpw, ZPEntity e, ZPPoint* p){
    //Get table record
    ecs_record_t* rec = ecs_record_find(zpw->world, e);
    ZPPosition *p_mut = ecs_record_get_column(rec, zpw->rect_cols.pos_col, sizeof(ZPPosition));
    // Set the Position of this rectangle
    p_mut->x = p->x;
    p_mut->y = p->y;
}

void zp_rect_set_velocity(ZPWorld* zpw, ZPEntity e, ZPPoint* p){
    //Get table record
    ecs_record_t* rec = ecs_record_find(zpw->world, e);
    ZPVelocity *v_mut = ecs_record_get_column(rec, zpw->rect_cols.vel_col, sizeof(ZPVelocity));
    // Set the Velocity of this rectangle
    v_mut->x = p->x;
    v_mut->y = p->y;
}

void zp_rect_set_acceleration(ZPWorld* zpw, ZPEntity e, ZPPoint* p){
    //Get table record
    ecs_record_t* rec = ecs_record_find(zpw->world, e);
    ZPAcceleration *a_mut = ecs_record_get_column(rec, zpw->rect_cols.accel_col, sizeof(ZPAcceleration));
    // Set the Acceleration of this rectangle
    a_mut->x = p->x;
    a_mut->y = p->y;
}

void zp_rect_set_size(ZPWorld* zpw, ZPEntity e, ZPSize* s){
    //Get table record
    ecs_record_t* rec = ecs_record_find(zpw->world, e);
    ZPSize *s_mut = ecs_record_get_column(rec, zpw->rect_cols.size_col, sizeof(ZPSize));
    // Set the Acceleration of this rectangle
    s_mut->height = s->height;
    s_mut->width = s->width;
}

// using ecs_get might not be best practice but i dont have another solution yet
ZPPoint* zp_rect_get_position(ZPWorld* zpw, ZPEntity e){
    return ecs_get(zpw->world, e, ZPPosition);
}

ZPPoint* zp_rect_get_velocity(ZPWorld* zpw, ZPEntity e){
    return ecs_get(zpw->world, e, ZPVelocity);
}

ZPPoint* zp_rect_get_acceleration(ZPWorld* zpw, ZPEntity e){
    return ecs_get(zpw->world, e, ZPAcceleration);
}

ZPSize* zp_rect_get_size(ZPWorld* zpw, ZPEntity e){
    return ecs_get(zpw->world, e, ZPSize);
}