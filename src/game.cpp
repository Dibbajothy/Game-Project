#include "game.h"
#include <random>

Game::Game()
{

    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    GameOver = false;
    score = 0;
    totalRowCleared = 0;
    BlockLastUpdateTime = 0;
    SpeedLastUpdateTime = 0;
    LastUpdateTime = 0;
    highestScore = 0;
    pause = -1;
    sound = 1;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    bgm = LoadMusicStream("Sounds/maingame.mp3");
    gameOverBgm = LoadMusicStream("Sounds/gameover.mp3");
    highScoreBgm = LoadMusicStream("Sounds/highscore.mp3");
    PlayMusicStream(music);
    PlayMusicStream(bgm);
    PlayMusicStream(gameOverBgm);
    PlayMusicStream(highScoreBgm);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{

    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    UnloadMusicStream(bgm);
    UnloadMusicStream(gameOverBgm);
    UnloadMusicStream(highScoreBgm);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{

    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return block;
}

vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{

    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {

    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    switch (keyPressed)
    {
    case KEY_H:
        pause *= -1;
        break;
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        if (pause == -1)
            UpdateScore(0, 1);
        break;
    case KEY_SPACE:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!GameOver && pause == -1)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}
void Game::MoveBlockRight()
{
    if (!GameOver && pause == -1)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}
void Game::MoveBlockDown()
{
    if (!GameOver && pause == -1)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!GameOver && pause == -1)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
            if (sound == 1)
                PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();

    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }

    currentBlock = nextBlock;

    if (BlockFits() == false)
    {

        long long int lastScore, bestScore;

        FILE *record = fopen("Score/records.txt", "r");
        fscanf(record, "%lld%lld", &lastScore, &bestScore);
        highestScore = bestScore;
        fclose(record);

        lastScore = score;
        bestScore = (score > bestScore) ? score : bestScore;

        FILE *record1 = fopen("Score/records.txt", "w");
        fprintf(record1, "%lld %lld", lastScore, bestScore);
        fclose(record1);

        GameOver = true;
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();

    if (rowsCleared > 0)
    {
        totalRowCleared += rowsCleared;
        if (sound == 1)
            PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

void Game::Exit()
{
    long long int lastScore, bestScore;

    FILE *record = fopen("Score/records.txt", "r");
    fscanf(record, "%lld%lld", &lastScore, &bestScore);
    highestScore = bestScore;
    fclose(record);

    lastScore = score;
    bestScore = (score > bestScore) ? score : bestScore;

    FILE *record1 = fopen("Score/records.txt", "w");
    fprintf(record1, "%lld %lld", lastScore, bestScore);
    fclose(record1);

    GameOver = true;
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    totalRowCleared = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        if (linesCleared)
            score += 1000;
        break;
    }
    score += moveDownPoints;
}

bool Game::EventTriggered(double interval)
{

    double CurrentTime = GetTime();
    if (CurrentTime - LastUpdateTime >= interval)
    {
        LastUpdateTime = CurrentTime;
        return true;
    }

    return false;
}

bool Game::blockUpdateTime(double interval)
{

    double CurrentTime = GetTime();
    if (CurrentTime - BlockLastUpdateTime >= interval)
    {
        BlockLastUpdateTime = CurrentTime;
        return true;
    }
    return false;
}

bool Game::SpeedUpdateTime(double interval)
{
    double CurrentTime = GetTime();
    if (CurrentTime - SpeedLastUpdateTime >= interval)
    {
        SpeedLastUpdateTime = CurrentTime;
        return true;
    }
    return false;
}
