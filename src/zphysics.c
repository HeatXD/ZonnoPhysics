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

// Declare Rectangle Component globally
ECS_COMPONENT_DECLARE(ZPRect);

int zp_world_setup(ZPWorld* zpw){
    // Create The ecs world 
    zpw->world = ecs_init();
    // Define ZPRect component
    ECS_COMPONENT_DEFINE(zpw->world, ZPRect);
    // Create a tag for each phase in the custom pipeline. 
    ECS_TAG(zpw->world, ZPWDynamics);
    ECS_TAG(zpw->world, ZPWCollisions);
    // Create the custom pipeline
    ECS_PIPELINE(zpw->world, ZPPipeline, ZPWDynamics, ZPWCollisions);
    // Set the pipeline
    ecs_set_pipeline(zpw->world, ZPPipeline);
    // ZPWDynamics systems
    ECS_SYSTEM(zpw->world, zp_rect_update_position, ZPWDynamics, ZPRect);
    // ZPWCollisions systems
    return 0;
}

int zp_world_step(ZPWorld* zpw, float dt){
    // Advance ZPWorld
    return ecs_progress(zpw->world, dt);
}

int zp_world_stop(ZPWorld* zpw){
    // Clean up resources
    return ecs_fini(zpw->world);
}

void zp_rect_update_position(ecs_iter_t* it){

    ZPRect* zpr = ecs_column(it, ZPRect, 1);

    for (int i = 0; i < it->count; i++)
    {
        // Update Velocity
        zpr[i].velocity.x += zpr[i].acceleration.x * it->delta_time;
        zpr[i].velocity.y += zpr[i].acceleration.y * it->delta_time;
        // Update Position
        zpr[i].position.x += zpr[i].velocity.x * it->delta_time;
        zpr[i].position.y += zpr[i].velocity.y * it->delta_time;
    }   
}

zp_entity_t zp_world_create_rect(ZPWorld* zpw){
    // Create entity with type ZPRect and return 
    return ecs_new(zpw->world, ZPRect);
}

zp_entity_t zp_rect_set_position(ZPWorld* zpw, zp_entity_t e, ZPPoint* p){
    // Sets the position of a ZPRect, should return the entity. if e == null returns a new entity
    return ecs_set(zpw->world, e, ZPRect, {.position.x = p->x, .position.y = p->y});
}

zp_entity_t zp_rect_set_velocity(ZPWorld* zpw, zp_entity_t e, ZPPoint* v){
    // Sets the velocity of a ZPRect, should return the entity. if e == null returns a new entity
    return ecs_set(zpw->world, e, ZPRect, {.velocity.x = v->x, .velocity.y = v->y});
}

zp_entity_t zp_rect_set_acceleration(ZPWorld* zpw, zp_entity_t e, ZPPoint* a){
    // Sets the acceleration of a ZPRect, should return the entity. if e == null returns a new entity
    return ecs_set(zpw->world, e, ZPRect, {.acceleration.x = a->x, .acceleration.y = a->y});
}

zp_entity_t zp_rect_set_size(ZPWorld* zpw, zp_entity_t e, float _w, float _h){
    // Sets the size of a ZPRect, should return the entity. if e == null returns a new entity
    return ecs_set(zpw->world, e, ZPRect, {.w = _w, .h = _h});
}