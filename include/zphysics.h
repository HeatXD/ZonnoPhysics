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
  ecs_world_t* world;
}ZPWorld;

typedef struct {
  float x, y;
}ZPPoint, ZPPosition, ZPVelocity, ZPAcceleration;

typedef struct {
  float width, height;
} ZPSize;

typedef struct {
  float mass;
} ZPMass;

///-------------------------------------------------------
//Definitions
///-------------------------------------------------------

int zp_world_setup(ZPWorld* zpw);
int zp_world_step(ZPWorld* zpw, float dt);
int zp_world_stop(ZPWorld* zpw);

void zp_rect_dynamics(ecs_iter_t* it);

#endif