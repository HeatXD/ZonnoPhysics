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

#include "flecs.h"

#ifndef ZONNO_PHYS
#define ZONNO_PHYS
///-------------------------------------------------------
//Structures
///-------------------------------------------------------
typedef ecs_entity_t zp_entity_t;

typedef struct ZPPoint {
    float x, y;
}ZPPoint;

typedef struct ZPLine {
    ZPPoint a, b;
}ZPLine;

typedef struct ZPRect {
    ZPPoint position, velocity, acceleration;
    float w, h;
}ZPRect;

typedef struct ZPWorld {
    ecs_world_t* world;
}ZPWorld;

///-------------------------------------------------------
//Definitions
///-------------------------------------------------------

void zp_rect_update_position(ecs_iter_t *it);

int zp_world_setup(ZPWorld* zpw);
int zp_world_step(ZPWorld* zpw, float dt);
int zp_world_stop(ZPWorld* zpw);

zp_entity_t zp_world_create_rect(ZPWorld* zpw);
zp_entity_t zp_rect_set_velocity(ZPWorld* zpw, zp_entity_t e, ZPPoint* v);
zp_entity_t zp_rect_set_acceleration(ZPWorld* zpw, zp_entity_t e, ZPPoint* a);

#endif