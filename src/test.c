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
    SetTargetFPS(60);
    // Create the ZonnoPhysics world
    ZPWorld zpw;
    // Init the world
    zp_world_setup(&zpw);
    // Create a entity
    ZPEntity e = zp_world_create_rect(&zpw);
    ZPPoint pv = {500, 0}, pp = {250, 250}, pa = {0, 400};
    ZPSize s = {50, 50};

    zp_rect_set_size(&zpw, e, &s);
    zp_rect_set_position(&zpw, e, &pp);
    zp_rect_set_velocity(&zpw, e, &pv);
    zp_rect_set_acceleration(&zpw, e, &pa);
    //check if entity has been added
    //printf("rects: %d \n", zp_get_entity_rect_count(&zpw));
    ZPPoint* pos_test = zp_rect_get_position(&zpw, e);
    ZPPoint* vel_test = zp_rect_get_velocity(&zpw, e);
    ZPPoint* accel_test = zp_rect_get_acceleration(&zpw, e);
    ZPSize* siz_test = zp_rect_get_size(&zpw, e);
    //printf("pos = x:%f, y:%f \n", pos_test->x, pos_test->y);
    //printf("vel = x:%f, y:%f \n", vel_test->x, vel_test->y);
    //printf("accel = x:%f, y:%f \n", accel_test->x, accel_test->y);
    //printf("size = w:%f, h:%f \n", siz_test->width, siz_test->height);
    //..
    do{
        // Update Simulation
        zp_world_step(&zpw, 0.017);
        // Some come to make the rectangle bounce off the walls
        ZPPoint* po = zp_rect_get_position(&zpw, e);
        ZPSize* si = zp_rect_get_size(&zpw, e);
        ZPPoint* ve = zp_rect_get_velocity(&zpw, e);
        ZPPoint* ac = zp_rect_get_acceleration(&zpw, e);

        if ((po->x < 0) || (po->x + si->width > 500))
        {
            ZPPoint p;
            if ((po->x < 0))
            {
                p.x = 0;
                p.y = po->y;
                zp_rect_set_position(&zpw, e, &p);
            }else{

                p.x = 500 - si->width;
                p.y = po->y;
                zp_rect_set_position(&zpw, e, &p);
            }  
            p.x = ve->x * -1;
            p.y = ve->y;
            zp_rect_set_velocity(&zpw, e, &p);

        }else if ((po->y < 0) || (po->y + si->height > 500)){
            ZPPoint p;

            if ((po->y < 0))
            {
                p.x = po->x;
                p.y = 0;
                zp_rect_set_position(&zpw, e, &p);
            }else{
                p.x = po->x;
                p.y = 500 - si->height;
                zp_rect_set_position(&zpw, e, &p);
            }
            
            p.y = ve->y * -1;
            p.x = ve->x;
            zp_rect_set_velocity(&zpw, e, &p);
        }
        // Draw Simulation
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(5, 5);
        // Draw a nice border
        DrawRectangleLines(1, 1, 498, 498, WHITE);
        // Draw AABB
        if (zp_get_entity_rect_count(&zpw) > 0)
        {
            ZPPoint* pos = zp_rect_get_position(&zpw, e);
            ZPSize* size = zp_rect_get_size(&zpw, e);
            Vector2 dpos = {pos->x, pos->y}, dsize = {size->width, size->height};
            Vector2 startPos = {pos->x + (size->width/2), pos->y + (size->height/2)};
            Vector2 velPos = {pos->x + (ve->x/6) , pos->y + (ve->y/6)};
            Vector2 accelPos = {pos->x + (ac->x/6) + (size->width/2) , pos->y + (ac->y/6)};
            DrawRectangleV(dpos, dsize, RED);
            DrawLineEx(startPos, velPos , 5, GREEN);
            DrawLineEx(startPos, accelPos, 5, BLUE);
        }
        EndDrawing();

    } while (!WindowShouldClose());

    CloseWindow();
    return 0;
}