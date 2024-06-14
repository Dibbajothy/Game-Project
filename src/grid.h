#pragma once
#include<vector>
#include <raylib.h>
using namespace std;

class Grid{

    private:
        bool IsRowFull(int row);
        void CLearRow(int row);
        void MoveRowDown(int row, int numRows);
        int numRows, numCols;
        int cellSize;
        vector<Color> colors;

    public:
        Grid();
        void Initialize();
        void Print();
        void Draw();
        bool IsCellOutside(int row, int column);
        bool IsCellEmpty(int row, int column);
        int ClearFullRows();
        int grid[20][10];

};