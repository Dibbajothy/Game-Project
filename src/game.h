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
        bool EventTriggered(double interval);
        bool blockUpdateTime(double interval);
        bool SpeedUpdateTime(double interval);
        bool GameOver;
        int score;
        int highestScore;
        int totalRowCleared;
        Music music;
        Music bgm;
        Music gameOverBgm;
        Music highScoreBgm;

    private:
        Block GetRandomBlock();
        vector<Block> GetAllBlocks();
        double BlockLastUpdateTime;
        double SpeedLastUpdateTime;
        double LastUpdateTime;
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