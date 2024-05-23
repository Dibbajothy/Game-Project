#include "grid.h"
#include<iostream>

using namespace std;

Grid::Grid(){

    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();

}

void Grid::Initialize(){

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            grid[i][j] = 0;
        }
        
    }
    
}

void Grid::Print(){

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

}

vector<Color> Grid::GetCellColors(){

    Color darkgrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {232, 18, 18, 255};
    Color orange = {226, 116, 17, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};
    Color cyan = {21, 204, 209, 255};
    Color blue = {33, 64, 216, 255};

    return {darkgrey, green, red, orange, yellow, purple, cyan, blue};

}

void Grid::Draw(){

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int cellValue = grid[i][j];

            DrawRectangle(j*cellSize + 1, i*cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }

}