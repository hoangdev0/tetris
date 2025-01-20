#include <raylib.h>
#include <bits/stdc++.h>
#include <iostream>
#include "game.h"
using namespace std;

enum gameState
{
    menu,
    instruct,
    gameplay,
    difficult,
    mode,
};
enum dif
{
    easy = 6,
    medium = 4,
    hard = 2
};
Vector2 defaultWindowSize = {500, 620},
        multiWindowSize = {1005, 620};
bool gameplay2 = false;
bool Pause = false;
double lastUpdateTime = 0;
double lastUpdateTime2 = 0;
double tick, tickDefault;
double tick2, tickDefault2;
bool cpm(Vector2 a, Rectangle b)
{
    return (CheckCollisionPointRec(a, b));
}
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
bool EventTriggered2(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime2 >= interval)
    {
        lastUpdateTime2 = currentTime;
        return true;
    }
    return false;
}
int main()
{

    InitWindow(defaultWindowSize.x, defaultWindowSize.y, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Texture2D bgtext = LoadTexture("D:/Hoang/Tetris/src/bg4.png");

    gameState Gamestate = menu;
    Game game = Game(),
         game2 = Game();
    dif Dif = medium;
    tick = tickDefault = 1.0 * Dif / 10;
    tick2 = tickDefault2 = 1.0 * Dif / 10;

    while (WindowShouldClose() == false) // escape
    {
        if (Gamestate == menu)
            SetWindowSize(defaultWindowSize.x, defaultWindowSize.y);
        else if (Gamestate == gameplay && gameplay2 == true)
            SetWindowSize(multiWindowSize.x, multiWindowSize.y);
        BeginDrawing();
        ClearBackground(darkblue);
        DrawTexture(bgtext, 0, 0, WHITE);
        DrawTexture(bgtext, 505, 0, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            Gamestate = menu;
            game.Reset();
        }
        if (Gamestate == menu)
        {
            DrawText("TETRIS", 250 - MeasureText("TETRIS", 80) / 2, 44, 80, BLACK);
            DrawText("TETRIS", 250 - MeasureText("TETRIS", 77) / 2, 40, 77, WHITE);
            //                            x      y    w   h
            Rectangle Nut_Start = {(500 - 200) / 2, 200, 200, 70};
            DrawRectangleRounded(Nut_Start, 0.5, 30, violet);
            DrawText("Start Game", Nut_Start.x + 20, Nut_Start.y + 25, 30, lightviolet);

            Rectangle Nut_Tut = {(500 - 200) / 2, 300, 200, 70};
            DrawRectangleRounded(Nut_Tut, 0.5, 30, violet);
            DrawText("Instruct", Nut_Tut.x + 40, Nut_Tut.y + 25, 30, lightviolet);

            Rectangle Nut_Dif = {(500 - 200) / 2, 400, 200, 70};
            DrawRectangleRounded(Nut_Dif, 0.5, 30, violet);
            DrawText("Dificulty", Nut_Dif.x + 40, Nut_Dif.y + 25, 30, lightviolet);

            Rectangle Nut_Mode = {(500 - 200) / 2, 500, 200, 70};
            DrawRectangleRounded(Nut_Mode, 0.5, 30, violet);
            DrawText("Game Mode", Nut_Mode.x + 20, Nut_Mode.y + 25, 30, lightviolet);

            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && cpm(GetMousePosition(), Nut_Start))
            {
                game.Reset();
                game2.Reset();
                Gamestate = gameplay;
            }
            if (click && cpm(GetMousePosition(), Nut_Tut))
                Gamestate = instruct;
            if (click && cpm(GetMousePosition(), Nut_Dif))
                Gamestate = difficult;
            if (click && cpm(GetMousePosition(), Nut_Mode))
                Gamestate = mode;
        }
        else if (Gamestate == gameplay)
        {
            /* Game play 1*/
            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightblue);
            DrawRectangleRounded({320, 190, 170, 150}, 0.3, 6, lightblue);
            DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Next", {365, 150}, 38, 2, WHITE);
            char scoreText2[10];
            sprintf(scoreText2, "%d", game2.score);
            Vector2 textSize = MeasureTextEx(font, scoreText2, 38, 2);
            DrawTextEx(font, scoreText2, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
            game2.curblock = game.curblock;
            if (gameplay2 == false && IsKeyPressed(KEY_SPACE))
                Pause = !Pause;
            if (game2.gameover)
            {
                game2.UpdateHightScore();
                Rectangle HightScore = {320, 400, 170, 50};
                DrawRectangleRounded(HightScore, 0.3, 6, violet);
                DrawTextEx(font, "Hight Score", {HightScore.x + 5, HightScore.y - 35}, 25, 3, red2);
                const char *txt = (game2.GetHightScore()).c_str();
                Vector2 TxtSz = MeasureTextEx(font, txt, 38, 2);
                DrawTextEx(font, txt, {320 + (170 - TxtSz.x) / 2, HightScore.y + 5}, 35, 2, WHITE);

                DrawTextEx(font, "GAME OVER", {335, 460}, 30, 2, RED);
                DrawRectangleRounded({320, 500, 170, 50}, 0.2, 6, lightblue);
                DrawTextEx(font, "RETURN", {360, 510}, 30, 2, WHITE);
                bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
                if (click && cpm(GetMousePosition(), {320, 500, 170, 50}))
                    Gamestate = menu;
            }
            if (!Pause)
            {
                /* Hand Input */
                int key = GetKeyPressed();
                if ( key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT)
                    game.Inp(key);
                else if (key == KEY_D || key == KEY_A || key == KEY_W)
                    game2.Inp2(key);

                if (EventTriggered2(tick2))
                    game2.MoveDown();
                if (IsKeyDown(KEY_S))
                    tick2 -= 0.005;
                else if (tick2 < 1)
                    tick2 = tickDefault2;
            }
            else if (game2.gameover == false)
            {
                Rectangle pause = {320, 370, 170, 50};
                DrawRectangleRounded(pause, 0.3, 6, lightblue);
                DrawText("PAUSED", pause.x + 35, pause.y + 15, 25, WHITE);
            }
            game2.Draw(0);
            if (gameplay2 == true)
            {
                /* Game play 2 */
                DrawRectangleRounded({505 + 320, 55, 170, 60}, 0.3, 6, lightblue);
                DrawRectangleRounded({505 + 320, 190, 170, 150}, 0.3, 6, lightblue);
                DrawTextEx(font, "Score", {505 + 365, 15}, 38, 2, WHITE);
                DrawTextEx(font, "Next", {505 + 365, 150}, 38, 2, WHITE);
                char scoreText[10];
                sprintf(scoreText, "%d", game.score);
                Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                DrawTextEx(font, scoreText, {505 + 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
                if (game.gameover)
                {
                    game.UpdateHightScore();
                    Rectangle HightScore = {505 + 320, 400, 170, 50};
                    DrawRectangleRounded(HightScore, 0.3, 6, violet);
                    DrawTextEx(font, "Hight Score", {HightScore.x + 5, HightScore.y - 35}, 25, 3, red2);
                    const char *txt = (game.GetHightScore()).c_str();
                    Vector2 TxtSz = MeasureTextEx(font, txt, 38, 2);
                    DrawTextEx(font, txt, {505 + 320 + (170 - TxtSz.x) / 2, HightScore.y + 5}, 35, 2, WHITE);

                    DrawTextEx(font, "GAME OVER", {505 + 335, 460}, 30, 2, RED);
                    DrawRectangleRounded({505 + 320, 500, 170, 50}, 0.2, 6, lightblue);
                    DrawTextEx(font, "RETURN", {505 + 360, 510}, 30, 2, WHITE);
                    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
                    if (click && cpm(GetMousePosition(), {505 + 320, 500, 170, 50}))
                        Gamestate = menu;
                }
                if (EventTriggered(tick))
                    game.MoveDown();
                if (IsKeyDown(KEY_DOWN))
                    tick -= 0.005;
                else if (tick < 1)
                    tick = tickDefault;
                game.Draw(505);
            }
        }
        else if (Gamestate == instruct)
        {
            DrawRectangleRounded({5, 80, 490, 400}, 0.1, 6, {0, 0, 0, 110});
            DrawText("Instructions", 500 / 2 - MeasureText("Instructions", 40) / 2, 20, 40, WHITE);
            DrawText("Press Enter to return to the Main Menu ", 15, 100, 18, WHITE);
            DrawText("Press arrow up or W key to rotate the blocks ", 15, 130, 18, WHITE);
            DrawText("Press arrow left or A key to move the blocks ", 15, 160, 18, WHITE);
            DrawText("Press arrow right or D key to move the blocks ", 15, 190, 18, WHITE);
            DrawText("Press arrow down or S key to move the blocks ", 15, 220, 18, WHITE);
            DrawText("Hold arrow down key to accelerate the game ", 15, 250, 18, WHITE);
            DrawText("When game over press on any arrow key to continue", 15, 280, 18, WHITE);
            DrawText("Press space bar to stop the game  ", 15, 310, 18, WHITE);
            DrawText("Press space bar again to continue the game  ", 15, 340, 18, WHITE);
            DrawText("Click Difficulty button to adjust game difficulty ", 15, 370, 18, WHITE);
            DrawText("Press ESC to escape the programme ", 15, 400, 18, WHITE);
            Rectangle back = {165, 500, 170, 60};
            DrawRectangleRounded(back, 0.3, 6, lightblue);
            DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && cpm(GetMousePosition(), back))
                Gamestate = menu;
        }
        else if (Gamestate == difficult)
        {
            DrawText("Difficulty", 500 / 2 - MeasureText("Difficulty", 40) / 2, 20, 40, WHITE);
            Rectangle easyb = {135, 100, 230, 60};
            DrawRectangleRounded(easyb, 0.2, 6, (Dif == easy) ? red2 : pink);
            DrawText("Easy", easyb.x + 80, easyb.y + 17, 30, (Dif != easy) ? red2 : pink);

            Rectangle mediumb = {135, 200, 230, 60};
            DrawRectangleRounded(mediumb, 0.2, 6, (Dif == medium) ? red2 : pink);
            DrawText("Medium", mediumb.x + 75, mediumb.y + 17, 30, (Dif != medium) ? red2 : pink);

            Rectangle hardb = {135, 300, 230, 60};
            DrawRectangleRounded(hardb, 0.2, 6, (Dif == hard) ? red2 : pink);
            DrawText("Hard", hardb.x + 80, hardb.y + 17, 30, (Dif != hard) ? red2 : pink);

            Rectangle back = {165, 500, 170, 60};
            DrawRectangleRounded(back, 0.3, 6, lightblue);
            DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && cpm(GetMousePosition(), back))
                Gamestate = menu;

            if (click && cpm(GetMousePosition(), easyb))
                Dif = easy, Gamestate = menu;
            else if (click && cpm(GetMousePosition(), mediumb))
                Dif = medium, Gamestate = menu;
            else if (click && cpm(GetMousePosition(), hardb))
                Dif = hard, Gamestate = menu;
            tick = tickDefault = 1.0 * Dif / 10;
            tick2 = tickDefault2 = 1.0 * Dif / 10;
        }
        else if (Gamestate == mode)
        {
            DrawText("Game Mode", 500 / 2 - MeasureText("Game Mode", 40) / 2, 20, 40, WHITE);
            Rectangle mode1 = {135, 100, 230, 60};
            DrawRectangleRounded(mode1, 0.2, 6, (gameplay2 == false) ? red2 : pink);
            DrawText("1 Player", mode1.x + 60, mode1.y + 17, 30, (gameplay2 != false) ? red2 : pink);

            Rectangle mode2 = {135, 200, 230, 60};
            DrawRectangleRounded(mode2, 0.2, 6, (gameplay2 == true) ? red2 : pink);
            DrawText("2 Player", mode2.x + 60, mode2.y + 17, 30, (gameplay2 != true) ? red2 : pink);
            Rectangle back = {165, 500, 170, 60};
            DrawRectangleRounded(back, 0.3, 6, lightblue);
            DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);

            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && cpm(GetMousePosition(), back))
                Gamestate = menu;
            if (click && cpm(GetMousePosition(), mode1))
                gameplay2 = false, Gamestate = menu;
            else if (click && cpm(GetMousePosition(), mode2))
                gameplay2 = true, Gamestate = menu;
        }
        EndDrawing();
    }

    CloseWindow();
}
/*
    game 1 người chơi tăng độ khó thêm level
    game 2 người chơi cùng block 
    lưu người chơi: 

    ** chơi online trên 2 máy 
 */