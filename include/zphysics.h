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
//Macros
///-------------------------------------------------------

#define ZPARRLEN(x) (sizeof(x) / sizeof((x)[0]))

///-------------------------------------------------------
//Structures
///-------------------------------------------------------
typedef struct {
  int32_t pos_col, vel_col;
  int32_t accel_col, size_col;
  int32_t mass_col;
}ZPWColumns;

typedef struct {
  ecs_world_t* world;
  ecs_table_t* rect_table;
  ZPWColumns rect_cols;
}ZPWorld;

typedef struct {
  float x, y;
}ZPPoint, ZPPosition, ZPVelocity, ZPAcceleration;

typedef struct {
  ZPPoint a, b;
} ZPLine;

typedef struct {
  float width, height;
} ZPSize;

typedef struct {
  float mass;
} ZPMass;

typedef ecs_entity_t ZPEntity;

///-------------------------------------------------------
//Definitions
///-------------------------------------------------------

ZPEntity zp_world_create_rect(ZPWorld* zpw);
int zp_world_setup(ZPWorld* zpw);
int zp_world_step(ZPWorld* zpw, float dt);
int zp_world_stop(ZPWorld* zpw);
int zp_get_entity_rect_count(ZPWorld* zpw);

void zp_rect_dynamics(ecs_iter_t* it);

void zp_rect_set_position(ZPWorld* zpw, ZPEntity e, ZPPoint* p);
void zp_rect_set_velocity(ZPWorld* zpw, ZPEntity e, ZPPoint* p);
void zp_rect_set_acceleration(ZPWorld* zpw, ZPEntity e, ZPPoint* p);
void zp_rect_set_size(ZPWorld* zpw, ZPEntity e, ZPSize* s);

ZPPoint* zp_rect_get_position(ZPWorld* zpw, ZPEntity e);
ZPPoint*  zp_rect_get_velocity(ZPWorld* zpw, ZPEntity e);
ZPPoint* zp_rect_get_acceleration(ZPWorld* zpw, ZPEntity e);
ZPSize* zp_rect_get_size(ZPWorld* zpw, ZPEntity e);

#endif