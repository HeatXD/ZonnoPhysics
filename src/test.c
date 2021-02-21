#include <stdio.h>
#include "raylib.h"
#include "zphysics.h"

int basic_dymanics_test(void);

int main(void)
{
    printf("test!\n");
    basic_dymanics_test();
}

int basic_dymanics_test(void){
    // Create a Raylib window
    InitWindow(500, 500, "Dynamics test");
    // Create the ZonnoPhysics world
    ZPWorld zpw;
    // Init the world
    zp_world_setup(&zpw);
    // Create a entity
    ZPEntity e = zp_world_create_rect(&zpw);
    ZPPoint pv = {0, 0}, pp = {250, 250}, pa = {0, .8};
    ZPSize s = {50, 50};

    zp_rect_set_size(&zpw, e, &s);
    zp_rect_set_position(&zpw, e, &pp);
    zp_rect_set_velocity(&zpw, e, &pv);
    zp_rect_set_acceleration(&zpw, e, &pa);
    //check if entity has been added
    printf("rects: %d \n", zp_get_entity_rect_count(&zpw));

    ZPPoint* pos_test = zp_rect_get_position(&zpw, e);
    ZPPoint* vel_test = zp_rect_get_velocity(&zpw, e);
    ZPPoint* accel_test = zp_rect_get_acceleration(&zpw, e);
    ZPSize* siz_test = zp_rect_get_size(&zpw, e);

    printf("pos = x:%f, y:%f \n", pos_test->x, pos_test->y);
    printf("vel = x:%f, y:%f \n", vel_test->x, vel_test->y);
    printf("accel = x:%f, y:%f \n", accel_test->x, accel_test->y);
    printf("size = w:%f, h:%f \n", siz_test->width, siz_test->height);
    //..
    do{
        // Update Simulation
        zp_world_step(&zpw, 0.0025);
        // Draw Simulation
        BeginDrawing();
        ClearBackground(BLACK);
        // Draw a nice border
        DrawRectangleLines(1, 1, 498, 498, BLUE);
        // Draw AABB
        if (zp_get_entity_rect_count(&zpw) > 0)
        {
            ZPPoint* pos = zp_rect_get_position(&zpw, e);
            ZPSize* size = zp_rect_get_size(&zpw, e);
            Vector2 dpos = {pos->x, pos->y}, dsize = {size->width, size->height};
            DrawRectangleV(dpos, dsize, RED);
        }

        EndDrawing();

    } while (!WindowShouldClose());

    CloseWindow();
    return 0;
}