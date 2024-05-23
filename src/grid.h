#pragma once
#include<vector>
#include <raylib.h>
using namespace std;

class Grid{
    private:
        vector<Color> GetCellColors();
        int numRows, numCols;
        int cellSize;
        vector<Color> colors;

    public:
        Grid();
        void Initialize();
        void Print();
        void Draw();
        int grid[20][10];

};