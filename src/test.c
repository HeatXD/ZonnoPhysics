#include <stdio.h>
#include "raylib.h"
#include "zphysics.h"
#include "memory.h"

int basic_dymanics_test(void);

int main(void)
{
    printf("test!\n");
    basic_dymanics_test();
}

int basic_dymanics_test(void){
    // Create a Raylib window
    InitWindow(500, 500, "Dynamics test");
    // Create a ZonnoPhysics World
    ZPWorld zpw;
    // Init the world
    zp_world_setup(&zpw);
    // Create some entities
    zp_entity_t entity_arr[2];

    for (int i = 0; i < 2; i++){
        zp_entity_t e = zp_world_create_rect(&zpw);
        ZPPoint p = {250, 250};
        ZPPoint v = {0, 0};

        zp_rect_set_position(&zpw, e, &p);
        zp_rect_set_velocity(&zpw, e, &v);
        zp_rect_set_size(&zpw, e, 20, 20);

        entity_arr[i] = e;
    }
    
    do
    {
        //Update Simulation
        zp_world_step(&zpw, 0.01667);
        ///Draw Simulation
        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < 2; i++)
        {
            ZPRect* zpr = zp_get_rect_info(&zpw, entity_arr[i]);
            Vector2 pos = {zpr->position.x, zpr->position.y};
            printf("X: %.6f, Y: %.6f",pos.x, pos.y);
            Vector2 size = {zpr->w, zpr->h};
            DrawRectangleV(pos, size, RED);
        }
        
        //DrawRectangle(10,10, 100, 50, WHITE);

        EndDrawing();


    } while (!WindowShouldClose());

    zp_world_stop(&zpw);

    CloseWindow();
    return 0;
}