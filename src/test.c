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
    // Init the world
    ZPWorld zpw;
    
    do
    {
        ///Draw Simulation
        BeginDrawing();

        ClearBackground(BLACK);
        //draw a nice border
        DrawRectangleLines(1, 1, 498, 498, BLUE);
        
        EndDrawing();


    } while (!WindowShouldClose());

    CloseWindow();
    return 0;
}