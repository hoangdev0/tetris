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
double tick, tickDefault;
double tick2, tickDefault2;
int displayGame1 = 0, displayGame2 = 505;
Rectangle buttonBase = {150, 0, 200, 70};

void EventTriggered(double, double &, Game &);
void DrawMenu(const Rectangle[], const char *[], int);
void DrawButton(Rectangle, const char *);
void ResizeWindow(gameState, bool, Texture2D);
void SetSate(gameState);
void DrawPause();
void DrawOver(Game &, gameState &, float, Font);
void DrawScore(Game &, float, Font);
void DrawInstruction();
void HandInput(Game &, Game &);
int main()
{

    InitWindow(defaultWindowSize.width, defaultWindowSize.height, "Tetris");
    SetTargetFPS(60);

    Texture2D bgtext = LoadTexture("D:/hoang/tetris/src/bg4.png");
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    gameState Gamestate = menu;

    Game game = Game(),
         game2 = Game();

    dif Dif = medium;

    tick = tickDefault = 1.0 * Dif / 10;
    tick2 = tickDefault2 = 1.0 * Dif / 10;

    Rectangle back = {165, 510, 170, 60};

    while (WindowShouldClose() == false) // escape
    {

        BeginDrawing();
        ClearBackground(darkblue);

        // Resize window
        ResizeWindow(Gamestate, gameplay2, bgtext);
        // Return Menu & ResetGame
        if (IsKeyPressed(KEY_ENTER))
        {
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
            } // vector<Block>Temp = 100
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

            if (!Pause)
            {
                // Hand Input
                HandInput(game, game2);
                // move down block
                EventTriggered(tick, lastUpdateTime, game);
                EventTriggered(tick2, lastUpdateTime2, game2);
            }
            else
                DrawPause();

            if (IsKeyDown(KEY_S))
                tick -= 0.005;
            else if (tick < 1)
                tick = tickDefault;

            if (IsKeyDown(KEY_DOWN))
                tick2 -= 0.005;
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
                game2.Draw(displayGame2);
            }
        }
        break;
            // instruct
        case instruct:
        {
            DrawInstruction();
            DrawRectangleRounded(back, 0.3, 6, lightblue);
            DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), back))
                Gamestate = menu;
        }
        break;
        // difficult
        case difficult:
        {
            DrawText("Difficulty", 500 / 2 - MeasureText("Difficulty", 40) / 2, 20, 40, WHITE);
            Rectangle button = {135, 100, 230, 60};

            vector<pair<const char *, dif>> but = {{"Easy", easy}, {"Medium", medium}, {"Hard", hard}};
            for (auto i : but)
            {
                DrawRectangleRounded(button, 0.2, 6, (Dif == i.second) ? red2 : pink);
                DrawText(i.first, button.x + 75, button.y + 17, 30, (Dif != i.second) ? red2 : pink);
                button.y += 100;
            }

            DrawRectangleRounded(back, 0.3, 6, lightblue);
            DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), back))
                Gamestate = menu;

            if (click && CheckCollisionPointRec(GetMousePosition(), {button.x, 100, button.width, button.height}))
                Dif = easy, Gamestate = menu;
            else if (click && CheckCollisionPointRec(GetMousePosition(), {button.x, 200, button.width, button.height}))
                Dif = medium, Gamestate = menu;
            else if (click && CheckCollisionPointRec(GetMousePosition(), {button.x, 300, button.width, button.height}))
                Dif = hard, Gamestate = menu;
            tick = tickDefault = 1.0 * Dif / 10;
            tick2 = tickDefault2 = 1.0 * Dif / 10;
        }
        break;
            // mode
        case mode:
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
            if (click && CheckCollisionPointRec(GetMousePosition(), back))
                Gamestate = menu;
            if (click && CheckCollisionPointRec(GetMousePosition(), mode1))
                gameplay2 = false, Gamestate = menu;
            else if (click && CheckCollisionPointRec(GetMousePosition(), mode2))
                gameplay2 = true, Gamestate = menu;
        }
        break;
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

void EventTriggered(double interval, double &lastUpdateTime, Game &game)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        game.MoveDown();
        return;
    }
}
void DrawMenu(const Rectangle but[], const char *txt[], int count)
{
    DrawText("TETRIS", 250 - MeasureText("TETRIS", 80) / 2, 44, 80, BLACK);
    DrawText("TETRIS", 250 - MeasureText("TETRIS", 77) / 2, 40, 77, WHITE);
    for (int i = 0; i < count; i++)
        DrawButton(but[i], txt[i]);
}
void DrawButton(Rectangle Button, const char *txt)
{
    DrawRectangleRounded(Button, 0.5, 30, violet);
    DrawText(txt, Button.x + (Button.width - MeasureText(txt, 30))/2, Button.y + 25, 30, lightviolet);
}
void ResizeWindow(gameState Gamestate, bool gameplay2, Texture2D bgtext)
{
    // draw picture
    DrawTexture(bgtext, displayGame1, 0, WHITE);
    DrawTexture(bgtext, displayGame2, 0, WHITE); // 505 is width of window
    if (Gamestate == menu)
        SetWindowSize(defaultWindowSize.width, defaultWindowSize.height);
    else if (Gamestate == gameplay && gameplay2 == true)
        SetWindowSize(multiWindowSize.width, multiWindowSize.height);
}
void DrawScore(Game &game, float start, Font font)
{
    Rectangle rec[] = {{start + 320, 55, 170, 60},
                       {start + 320, 190, 170, 150}};
    DrawRectangleRounded(rec[0], 0.3, 6, lightblue);
    DrawRectangleRounded(rec[1], 0.3, 6, lightblue);

    Vector2 pos[] = {{start + 365, 15}, {start + 365, 150}};
    DrawTextEx(font, "Score", pos[0], 38, 2, WHITE);
    DrawTextEx(font, "Next", pos[1], 38, 2, WHITE);

    char scoreText2[10];
    sprintf(scoreText2, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText2, 38, 2);
    DrawTextEx(font, scoreText2, {start + 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
}
void DrawOver(Game &game, gameState &Gamestate, float start, Font font)
{
    game.UpdateHightScore();
    Rectangle HightScore = {start + 320, 400, 170, 50},
              Return = {start + 320, 500, 170, 50};
    DrawRectangleRounded(HightScore, 0.3, 6, violet);
    DrawTextEx(font, "Hight Score", {HightScore.x + 5, HightScore.y - 35}, 25, 3, red2);
    const char *txt = (game.GetHightScore()).c_str();
    Vector2 TxtSz = MeasureTextEx(font, txt, 38, 2);
    DrawTextEx(font, txt, {start + 320 + (170 - TxtSz.x) / 2, HightScore.y + 5}, 35, 2, WHITE);

    DrawTextEx(font, "GAME OVER", {start + 335, 460}, 30, 2, RED);
    DrawRectangleRounded(Return, 0.2, 6, lightblue);
    DrawTextEx(font, "RETURN", {start + 360, 510}, 30, 2, WHITE);
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (click && CheckCollisionPointRec(GetMousePosition(), Return))
        Gamestate = menu;
}
void DrawPause()
{
    Rectangle pause = {320, 370, 170, 50};
    DrawRectangleRounded(pause, 0.3, 6, lightblue);
    DrawText("PAUSED", pause.x + 35, pause.y + 15, 25, WHITE);
    // DrawRectangleRounded({defaultWindowSize}, 0, 10, {27, 27, 29, 150});
}
void HandInput(Game &game, Game &game2)
{
    int key = GetKeyPressed();
    if (key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT)
        game2.Inp(key);
    else if (key == KEY_D || key == KEY_A || key == KEY_W)
        game.Inp2(key);
    if (Pause && game.gameover == false)
        DrawPause();
}
void DrawInstruction()
{
    Rectangle backgr = {5, 80, 490, 400};
    Color lightblack = {0, 0, 0, 110};
    DrawRectangleRounded(backgr, 0.1, 6, lightblack);
    DrawText("Instructions", (defaultWindowSize.width - MeasureText("Instructions", 40)) / 2, 20, 40, WHITE);
    vector<const char *> instructions = {
        {"Press Enter to return to the Main Menu"},
        {"Press arrow up or W key to rotate the blocks "},
        {"Press arrow left or A key to move the blocks "},
        {"Press arrow right or D key to move the blocks "},
        // {"Press arrow down or S key to move the blocks "},
        {"Hold arrow down or S key to accelerate the game "},
        {"When game over press on any arrow key to continue"},
        {"Press space bar to stop the game only 1 Player"},
        {"Press space bar again to continue the game"},
        {"Press ESC to escape the programme "}

    };
    int base = 100; // first line
    for (auto line : instructions)
        DrawText(line, 15, base, 18, WHITE), base += 30;
}