#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Reset();
        void HandleInput();
        void MoveBlockDown();
        bool GameOver;
        int score;
        Music music;

    private:
        Block GetRandomBlock();
        vector<Block> GetAllBlocks();
        bool IsBlockOutside();
        void RotateBlock();
        void MoveBlockLeft();
        void MoveBlockRight();
        void LockBlock();
        bool BlockFits();
        void UpdateScore(int linesCleared, int moveDownPoints);
        Grid grid;
        vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;
        
};