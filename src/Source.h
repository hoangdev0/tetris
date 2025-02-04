#pragma once
#include <raylib.h>
#include <iostream>
#include "game.h"
using namespace std;

enum gameState
{
    menu,      // 0
    instruct,  // 1
    gameplay,  // 2
    difficult, // 3
    mode       // 4
};

enum dif
{
    easy = 6,
    medium = 4,
    hard = 2
};

Rectangle defaultWindowSize = {0, 0, 500, 620},
          multiWindowSize = {0, 0, 1005, 620};
bool gameplay2 = false;
bool Pause = false;
double lastUpdateTime = 0, lastUpdateTime2 = 0;
double tick = 0.5, tickDefault = 0.5;
double tick2 = 0.5, tickDefault2 = 0.5;
int displayGame1 = 0, displayGame2 = 505;
Rectangle buttonBase = {150, 0, 200, 70};

void EventTriggered(double, double &, Game &);
void DrawMenu(const Rectangle[], const char *[], int);
void DrawButton(Rectangle, const char *);
void DrawButton2(Rectangle, const char *, bool);
void DrawButton3(Rectangle, const char *);
void ResizeWindow(gameState, bool, Texture2D);
void SetSate(gameState);
void DrawPause();
void DrawOver(Game &, gameState &, float, Font);
void DrawScore(Game &, float, Font);
void DrawInstruction();
void HandInput(Game &, Game &);
void BackButton(gameState &);
void DrawGameMode();
void SaveGameMode();
void LoadGameMode();
void SaveGrid(Game &, Game &);
void LoadGrid(Game &, Game &);
int main()
{
    InitWindow(defaultWindowSize.width, defaultWindowSize.height, "Tetris");
    SetTargetFPS(60);

    Texture2D bgtext = LoadTexture("src/bg4.png");
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    gameState Gamestate = menu;

    Game game = Game(),
         game2 = Game();

    dif Dif = medium;

    LoadGameMode();
    
    while (WindowShouldClose() == false) // escape
    {
        BeginDrawing();
        ClearBackground(darkblue);

        // Resize window
        ResizeWindow(Gamestate, gameplay2, bgtext);
        // Return Menu & ResetGame
        if (IsKeyPressed(KEY_ENTER))
        {
            SaveGrid(game, game2);
            Gamestate = menu;
            game.Reset();
            game2.Reset();
        }

        switch (Gamestate)
        {
        // menu
        case menu:
        {
            //                            x      y               width             height
            Rectangle but[] = {
                {buttonBase.x, 200, buttonBase.width, buttonBase.height}, // Strat
                {buttonBase.x, 300, buttonBase.width, buttonBase.height}, // Instruct
                {buttonBase.x, 400, buttonBase.width, buttonBase.height}, // Dificulty
                {buttonBase.x, 500, buttonBase.width, buttonBase.height}  // Game Mode
            };
            const char *txt[] = {"Start Game", "Instruct", "Dificulty", "Game Mode"};
            DrawMenu(but, txt, 4);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[0]))
            {
                game.Reset();
                game2.Reset();
                Gamestate = gameplay;
                LoadGrid(game, game2);
            }
            if (click && CheckCollisionPointRec(GetMousePosition(), but[1]))
                Gamestate = instruct;
            if (click && CheckCollisionPointRec(GetMousePosition(), but[2]))
                Gamestate = difficult;
            if (click && CheckCollisionPointRec(GetMousePosition(), but[3]))
                Gamestate = mode;
        }
        break;
        // gameplay
        case gameplay:
        {

            if (gameplay2 == false && IsKeyPressed(KEY_SPACE))
                Pause = !Pause;

            // draw score gameplay 1
            DrawScore(game, displayGame1, font);

            // gameplay 1 over
            if (game.gameover)
                DrawOver(game, Gamestate, displayGame1, font);

            else if (!Pause)
            {
                // Hand Input
                HandInput(game, game2);
                // move down block
                EventTriggered(tick, lastUpdateTime, game);
            }
            else
                DrawPause();

            if (IsKeyDown(KEY_S))
                tick -= 0.01;
            else if (tick < 1)
                tick = tickDefault;

            if (IsKeyDown(KEY_DOWN))
                tick2 -= 0.01;
            else if (tick2 < 1)
                tick2 = tickDefault2;

            game.Draw(displayGame1);

            /*=== Game play 2 ===*/
            
            if (gameplay2)
            {
                // draw score gameplay 2
                DrawScore(game2, displayGame2, font);

                // gameplay 2 over
                if (game2.gameover)
                    DrawOver(game2, Gamestate, displayGame2, font);
                else
                    EventTriggered(tick2, lastUpdateTime2, game2);
                game2.Draw(displayGame2);
            }
        }
        break;
            // instruct
        case instruct:
        {
            DrawInstruction();
            BackButton(Gamestate);
        }
        break;
        // difficult
        case difficult:
        {
            DrawText("Difficulty", 500 / 2 - MeasureText("Difficulty", 40) / 2, 20, 40, WHITE);
            Rectangle but[] = {{135, 100, 230, 60},
                               {135, 200, 230, 60},
                               {135, 300, 230, 60}};
            int j = 0;
            vector<pair<const char *, dif>> txt = {{"Easy", easy}, {"Medium", medium}, {"Hard", hard}};
            for (auto i : txt)
                DrawButton2(but[j], i.first, (Dif == i.second)), j++;

            BackButton(Gamestate);

            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[0]))
                Dif = easy, Gamestate = menu;
            else if (click && CheckCollisionPointRec(GetMousePosition(), but[1]))
                Dif = medium, Gamestate = menu;
            else if (click && CheckCollisionPointRec(GetMousePosition(), but[2]))
                Dif = hard, Gamestate = menu;
        }
        break;
            // mode
        case mode:
        {
            DrawGameMode();
            BackButton(Gamestate);
        }
        break;
        }
        EndDrawing();
    }
    CloseWindow();
}