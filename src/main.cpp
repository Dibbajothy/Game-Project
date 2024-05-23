#include<iostream>
#include <raylib.h>
#include "grid.h"

using namespace std;



int main()
{
    Color darkblue = {44, 44, 127, 255};
    InitWindow(300, 600, "Tetris");

    SetTargetFPS(60);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[1][4] = 2;
    grid.grid[7][2] = 3;
    grid.grid[5][9] = 6;
    grid.Print();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkblue);
        grid.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}