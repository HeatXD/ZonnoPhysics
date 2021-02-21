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
    zp_entity_t e = zp_world_create_rect(&zpw);
    //check if entity has been added
    printf("rects: %d \n", zp_get_entity_rect_count(&zpw));
    do
    {
        // Update Simulation
        zp_world_step(&zpw, 0.01667);
        // Draw Simulation
        BeginDrawing();

        ClearBackground(BLACK);
        // Draw a nice border
        DrawRectangleLines(1, 1, 498, 498, BLUE);
        
        EndDrawing();

    } while (!WindowShouldClose());

    CloseWindow();
    return 0;
}