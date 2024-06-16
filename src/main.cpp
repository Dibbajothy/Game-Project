#include<iostream>
#include <raylib.h>
#include "game.h"
#include "colors.h"
using namespace std;

double LastUpdateTime = 0;

float start = 105;

bool EventTriggered(double interval){

    double CurrentTime = GetTime();
    if(CurrentTime - LastUpdateTime >= interval){
        LastUpdateTime = CurrentTime;
        return true;
    }
    return false;
}

Image icon = LoadImage("Image/tetris-logo.png"); // Game Logo On Tittle Bar



int main()
{

    InitWindow(500, 620, "Tetris");
    Texture2D blocksImage = LoadTexture("Image/blocks.png");
    SetTargetFPS(60);
    SetWindowIcon(icon);

    Font font = LoadFontEx("Font/TitilliumWeb-Bold.ttf", 64, 0, 0);
    Font tittle = LoadFontEx("Font/Tiny5-Regular.ttf", 500, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();

        if(EventTriggered(0.5)){
            game.MoveBlockDown();
        }
        BeginDrawing();

        ClearBackground(darkBlue);



        if(false){
            
            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 0.7, WHITE); // WHole Rectangle

            DrawRectangleRoundedLines({131, 109, 242, 63}, 0, 0, 2.1, WHITE);
            DrawTextEx(tittle, "TETRIS", {140, 100}, 80, 2, WHITE);
            //Blocks
            DrawTextureEx(blocksImage, {153, 230}, 0, 0.07, WHITE);
            //end

            // This Section Is For Loading Bar| Declared a Global Variable
            // start = 105
            DrawText("LOADING", 210, 415, 20, WHITE);
            DrawRectangleRoundedLines({100, 445, 315, 26}, 0, 0, 1.7, WHITE);
            DrawRectangleRec({105, 450, start + 5, 16}, lightGreen);
            if(EventTriggered(0.07) && start < 300){
                start += 5;
            }
            // ENds Here 

        }

        if(true){
            DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

            if(game.GameOver){
                DrawTextEx(font, "GAME OVER", {320, 450}, 45, 2, WHITE);
            }

            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170-textSize.x)/2, 65}, 38, 2, WHITE);

            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
            game.Draw();
        }
        EndDrawing();
    }
    
    CloseWindow();
}