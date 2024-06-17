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


typedef struct Button{
    Rectangle rect;
    Color color;
} Button;

void init_button(Button *button, Rectangle rect, Color color){

    button->rect = rect;
    button->color = color;

}

bool is_mouse_over_button(Button button){
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}




int main()
{

    InitWindow(500, 620, "Tetris");
    Texture2D blocksImage = LoadTexture("Image/blocks.png");
    SetTargetFPS(60);
    SetWindowIcon(icon);

    Font font = LoadFontEx("Font/TitilliumWeb-Bold.ttf", 500, 0, 0);
    Font tittle = LoadFontEx("Font/Tiny5-Regular.ttf", 500, 0, 0);
    Font font_treb = LoadFontEx("Font/trebucbd.ttf", 500, 0, 0);

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


        if(true){

            // FIrst page Before Any Game Start 

            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 5, WHITE); // WHole Rectangle

            DrawRectangleRoundedLines({131, 109, 242, 63}, 0, 0, 2.1, WHITE);
            DrawTextEx(tittle, "TETRIS", {140, 100}, 80, 2, WHITE);

            
            Button start_button, level_button, lead_button, about_button;
            init_button(&start_button, {183, 274, 132, 38}, lightWhite);
            init_button(&level_button, {174, 333, 151, 39}, lightWhite);
            init_button(&lead_button, {109, 393, 281, 40}, lightWhite);
            init_button(&about_button, {180, 452, 141, 38}, lightWhite);

            {
                if(is_mouse_over_button(start_button)){
                    start_button.color = lightestGreen;
                }
                else{
                    start_button.color = lightWhite;
                }
            }
            {
                if(is_mouse_over_button(level_button)){
                    level_button.color = BLUE;
                }
                else{
                    level_button.color = lightWhite;
                }
            }
            {
                if(is_mouse_over_button(lead_button)){
                    lead_button.color = BLUE;
                }
                else{
                    lead_button.color = lightWhite;
                }
            }
            {
                if(is_mouse_over_button(about_button)){
                    about_button.color = BLUE;
                }
                else{
                    about_button.color = lightWhite;
                }
            }



            DrawRectangleRounded(start_button.rect, 0.2, 20, start_button.color);
            DrawRectangleRounded(level_button.rect, 0.2, 20, level_button.color);
            DrawRectangleRounded(lead_button.rect, 0.2, 20, lead_button.color);
            DrawRectangleRounded(about_button.rect, 0.2, 20, about_button.color);


            DrawTextEx(font_treb, "START", {192, 277}, 34, 7, WHITE);
            DrawTextEx(font_treb, "LEVELS", {183, 336}, 34, 7, WHITE);
            DrawTextEx(font_treb, "LEADERBOARD", {119, 397}, 33, 7, WHITE);
            DrawTextEx(font_treb, "ABOUT", {189, 455}, 34, 7, WHITE);


        }














        if(false){
            
            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 5, WHITE); // WHole Rectangle

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






        if(false){
            // Main Game Part
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