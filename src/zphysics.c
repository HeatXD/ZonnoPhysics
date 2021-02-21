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
    // Create the pipeline phases
    ECS_TAG(zpw->world, ZPWDynamics);
    // Create the pipeline
    ECS_PIPELINE(zpw->world, ZPWPipeline, ZPWDynamics);
    // Set the world to use the pipeline
    ecs_set_pipeline(zpw->world, ZPWPipeline);
    // ZPWDynamics systems
    ECS_SYSTEM(zpw->world, zp_rect_dynamics, ZPWDynamics, ZPRectangle);
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
    return ecs_count(zpw->world, ZPRectangle);
}
zp_entity_t zp_world_create_rect(ZPWorld* zpw){
    return ecs_new(zpw->world, ZPRectangle);
}

zp_entity_t zp_rect_set_position(ZPWorld* zpw, zp_entity_t e, ZPPoint p){
    return ecs_set(zpw->world, e, ZPPosition, {p.x, p.y});
}

zp_entity_t zp_rect_set_velocity(ZPWorld* zpw, zp_entity_t e, ZPPoint p){
   return ecs_set(zpw->world, e, ZPVelocity, {p.x, p.y});
}

zp_entity_t zp_rect_set_acceleration(ZPWorld* zpw, zp_entity_t e, ZPPoint p){
   return ecs_set(zpw->world, e, ZPAcceleration, {p.x, p.y});
}

zp_entity_t zp_rect_set_size(ZPWorld* zpw, zp_entity_t e, ZPSize s){
    return ecs_set(zpw->world, e, ZPSize, {s.width, s.height});
}