#include<iostream>

#include <raylib.h>
#include "game.h"
#include "colors.h"
#include "button.h"

using namespace std;

double LastUpdateTime = 0;
bool EventTriggered(double interval){

    double CurrentTime = GetTime();
    if(CurrentTime - LastUpdateTime >= interval){
        LastUpdateTime = CurrentTime;
        return true;
    }
    return false;
}

float start = 105;


Image icon = LoadImage("Image/tetris-logo.png"); // Game Logo On Tittle Bar



bool front_page = true;
bool leaderboard_page = false;
bool about_page = false;
bool loading_page = false;
bool main_game = false;

int main()
{


    InitWindow(500, 620, "Tetris");

    Texture2D blocksImage = LoadTexture("Image/blocks.png");
    Texture2D aboutImage = LoadTexture("Image/aboutpage2.png");


    SetTargetFPS(60);
    SetWindowIcon(icon);

    Font font = LoadFontEx("Font/TitilliumWeb-Bold.ttf", 500, 0, 0);
    Font tittle = LoadFontEx("Font/Tiny5-Regular.ttf", 500, 0, 0);
    Font font_treb = LoadFontEx("Font/trebucbd.ttf", 500, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        BeginDrawing();

        ClearBackground(darkBlue);

        if(front_page){

            // FIrst page Before Any Game Start 

            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 5, WHITE); // WHole Rectangle

            DrawRectangleRoundedLines({131, 109, 242, 63}, 0, 0, 2.1, WHITE);
            DrawTextEx(tittle, "TETRIS", {140, 100}, 80, 2, WHITE);
    
            Button start_button, help_button, lead_button, about_button;

            init_button(&start_button, {183, 274, 132, 38}, lightWhite);
            init_button(&help_button, {196, 333, 109, 39}, lightWhite);
            init_button(&lead_button, {109, 393, 281, 40}, lightWhite);
            init_button(&about_button, {180, 452, 141, 38}, lightWhite);

            button_color_change(&start_button, lightWhite, lightestGreen);
            button_color_change(&help_button, lightWhite, BLUE);
            button_color_change(&lead_button, lightWhite, BLUE);
            button_color_change(&about_button, lightWhite, BLUE);

            DrawRectangleRounded(start_button.rect, 0.2, 20, start_button.color);
            DrawRectangleRounded(help_button.rect, 0.2, 20, help_button.color);
            DrawRectangleRounded(lead_button.rect, 0.2, 20, lead_button.color);
            DrawRectangleRounded(about_button.rect, 0.2, 20, about_button.color);

            DrawTextEx(font_treb, "START", {192, 277}, 34, 7, WHITE);
            DrawTextEx(font_treb, "HELP", {205, 336}, 34, 7, WHITE);
            DrawTextEx(font_treb, "LEADERBOARD", {119, 397}, 33, 7, WHITE);
            DrawTextEx(font_treb, "ABOUT", {189, 455}, 34, 7, WHITE);

            if(button_in_action(about_button)){
                front_page = false;
                about_page = true;
            }
            if(button_in_action(start_button)){
                front_page = false;
                loading_page = true;
            }
            if(button_in_action(lead_button)){
                front_page = false;
                leaderboard_page = true;
            }

        }

        

        if(leaderboard_page){
            
            FILE *record = fopen("Score/records.txt", "r");

            long long int last_score, best_score;
            char lastScore[20], bestScore[20];

            fscanf(record, "%lld%lld", &last_score, &best_score);

            fclose(record);

            sprintf(lastScore, "%lld", last_score);
            sprintf(bestScore, "%lld", best_score);

            Vector2 lastScoreSize = MeasureTextEx(font_treb, lastScore, 38, 3);
            Vector2 bestScoreSize = MeasureTextEx(font_treb, bestScore, 38, 3);


            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 5, WHITE);

            DrawRectangleRoundedLines({131, 109, 242, 63}, 0, 0, 2.1, WHITE);
            DrawTextEx(tittle, "TETRIS", {140, 100}, 80, 2, WHITE);



            DrawTextEx(font_treb, "Last Score", {164, 250}, 33, 4, WHITE);
            DrawRectangleRounded({135, 290, 229, 70}, 0.2, 20, lightWhite);
            DrawTextEx(font_treb, lastScore, {135 + (229 - lastScoreSize.x)/2, 307}, 38, 3, WHITE);


            DrawTextEx(font_treb, "Best Score", {164, 369}, 33, 4, WHITE);
            DrawRectangleRounded({135, 410, 229, 70}, 0.2, 20, lightWhite);
            DrawTextEx(font_treb, bestScore, {135 + (229 - bestScoreSize.x)/2, 425}, 38, 3, WHITE);


            // Reseting The Score

            Button reset_button;
            init_button(&reset_button, {384, 560, 89, 34}, lightWhite);        
            button_color_change(&reset_button, lightWhite, RED);
            DrawRectangleRounded(reset_button.rect, 0.2, 20, reset_button.color);
            DrawTextEx(font_treb, "RESET", {391, 565}, 25, 3, WHITE);

            if(button_in_action(reset_button)){
                FILE *record = fopen("Score/records.txt", "w");
                fprintf(record, "%d %d", 0 , 0);
                fclose(record);
            }

            //

            // For Going Back To The First page Without any game

            Button back_button;
            init_button(&back_button, {15, 16, 77, 33}, lightWhite);        
            button_color_change(&back_button, lightWhite, BLUE);
            DrawRectangleRounded(back_button.rect, 0.2, 20, back_button.color);
            DrawTextEx(font_treb, "BACK", {22, 20}, 25, 3, WHITE);

            if(button_in_action(back_button)){
                front_page = true;
                leaderboard_page = false;
            }


        }



        if(about_page){

            DrawRectangleRoundedLines({3, 3, 494, 614}, 0, 0, 5, WHITE);
            
            // Drawing The About JPG
            DrawTextureEx(aboutImage, {3, 3}, 0, 0.119, WHITE);
            //ENds

            Button back_button;
            init_button(&back_button, {15, 16, 77, 33}, lightWhite);        
            button_color_change(&back_button, lightWhite, BLUE);
            DrawRectangleRounded(back_button.rect, 0.2, 20, back_button.color);
            DrawTextEx(font_treb, "BACK", {22, 20}, 25, 3, WHITE);

            if(button_in_action(back_button)){
                front_page = true;
                about_page = false;
            }

        }




        if(loading_page){
            
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
                if(start == 300.0){
                    loading_page = false;
                    main_game = true;
                }
            }
            // ENds Here 

        }



        if(main_game){
            // Main Game Part

            game.HandleInput();

            if(EventTriggered(0.5)){
                game.MoveBlockDown();
            }

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


