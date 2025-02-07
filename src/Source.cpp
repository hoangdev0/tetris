#include "Source.h"

int main()
{
    InitWindow(defaultWindowSize.width, defaultWindowSize.height, "Tetris");
    SetTargetFPS(60);

    Texture2D bgtext = LoadTexture("src/bg4.png");
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    gameState Gamestate = menu;
    int seed = time(0);
    Game game = Game(seed),
         game2 = Game(seed);

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
            // SaveGame(game, game2);
            if (Gamestate == gameplay)
                Gamestate = save;
            else
            {
                game.Reset();
                game2.Reset();
                CreateBlock(Dif, game, game2);
            }
        }

        switch (Gamestate)
        {
        // menu
        case menu:
        {
            //                            x      y               width             height
            DrawRectangleRounded(defaultWindowSize, 0.1, 6, {0, 0, 0, 50});
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
                Gamestate = ctn;
            if (click && CheckCollisionPointRec(GetMousePosition(), but[1]))
                Gamestate = instruct;
            if (click && CheckCollisionPointRec(GetMousePosition(), but[2]))
                Gamestate = difficult;
            if (click && CheckCollisionPointRec(GetMousePosition(), but[3]))
                Gamestate = mode;
        }
        break;
        // save
        case save:
        {
            DrawRectangleRounded(defaultWindowSize, 0, 6, {0, 0, 0, 60});
            DrawText("SAVE", 500 / 2 - MeasureText("SAVE", 40) / 2, 20, 40, WHITE);
            Rectangle but[] = {{135, 200, 230, 60},
                               {135, 300, 230, 60},
                               {135, 400, 230, 60}};
            const char *txt[] = {"SAVE", "DON'T SAVE"};
            DrawButton(but[0], txt[0], 15);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[1]))
            {
                game.Reset();
                game2.Reset();
                CreateBlock(Dif, game, game2);
                Gamestate = menu;
            }

            DrawButton(but[1], txt[1], 15);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[0]))
            {
                Gamestate = menu;
                SaveGameMode();
                SaveGame(game, game2);
            }
            DrawButton(but[2], "Continue", 15);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[2]))
                Gamestate = gameplay;
        }
        break;
        // continue
        case ctn:
        {
            DrawRectangleRounded(defaultWindowSize, 0, 6, {0, 0, 0, 60});
            DrawText("Continue", 500 / 2 - MeasureText("Continue", 40) / 2, 20, 40, WHITE);
            Rectangle but[] = {{135, 200, 230, 60},
                               {135, 300, 230, 60}};
            const char *txt[] = {"New Game", "Continue"};
            DrawButton(but[0], txt[0], 15);
            bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[0]))
            {
                game.Reset();
                game2.Reset();
                CreateBlock(Dif, game, game2);
                Gamestate = gameplay;
            }

            DrawButton(but[1], txt[1], 15);
            if (click && CheckCollisionPointRec(GetMousePosition(), but[1]))
            {
                LoadGameMode();
                LoadGame(game, game2);
                Gamestate = gameplay;
            }
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

            // Key Down
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
    // SaveGame(game, game2);
    CloseWindow();
}

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
        DrawButton(but[i], txt[i], 20);
}
void DrawButton(Rectangle Button, const char *txt, int h)
{
    DrawRectangleRounded(Button, 0.5, 30, violet);
    DrawText(txt, Button.x + (Button.width - MeasureText(txt, 30)) / 2, Button.y + h, 30, lightviolet);
}
void DrawButton2(Rectangle Button, const char *txt, bool b)
{
    DrawRectangleRounded(Button, 0.5, 6, b ? red2 : pink);
    DrawText(txt, Button.x + (Button.width - MeasureText(txt, 30)) / 2, Button.y + 17, 30, !b ? red2 : pink);
}
void DrawButton3(Rectangle Button, const char *txt)
{
    DrawRectangleRounded(Button, 0.5, 30, violet);
    string t = "-";
    if (txt == t.c_str())
        Button.x += 2, Button.y += 2;
    DrawText(txt, Button.x + MeasureText(txt, 30) / 2, Button.y, 30, lightviolet);
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
    DrawRectangleRounded({5, 80, 490, 400}, 0.1, 6, {0, 0, 0, 110});
    DrawText("Instructions", (defaultWindowSize.width - MeasureText("Instructions", 40)) / 2, 20, 40, WHITE);
    vector<const char *> instructions = {
        {"Press Enter to return to the Main Menu"},
        {"Press arrow up or W key to rotate the blocks "},
        {"Press arrow left or A key to move the blocks "},
        {"Press arrow right or D key to move the blocks "},
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
void BackButton(gameState &Gamestate)
{
    Rectangle back = {165, 510, 170, 60};
    DrawRectangleRounded(back, 0.3, 6, lightblue);
    DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (click && CheckCollisionPointRec(GetMousePosition(), back))
    {
        Gamestate = menu;
        SaveGameMode();
    }
}
void DrawGameMode()
{
    Rectangle mode[] = {{135, 100, 230, 60}, {135, 200, 230, 60}};
    DrawText("Game Mode", (defaultWindowSize.width - MeasureText("Game Mode", 40)) / 2, 20, 40, WHITE);
    DrawButton2(mode[0], "1 Player", gameplay2 == false);
    DrawButton2(mode[1], "2 Player", gameplay2 == true);

    Rectangle backgr = {5, 275, 480, 180};
    Color lightblack = {0, 0, 0, 110};
    DrawRectangleRounded(backgr, 0.1, 6, lightblack);

    Vector2 pos[] = {{50, 330}, {50, 380}};
    DrawText("Speed", (defaultWindowSize.width - MeasureText("Speed", 40)) / 2, 280, 40, WHITE);
    DrawText("Player 1: ", pos[0].x, pos[0].y, 20, WHITE);

    Rectangle but[] = {
        {pos[0].x + 100, pos[0].y, 30, 30}, // 1 -
        {pos[0].x + 300, pos[0].y, 30, 30}, // 1 +
        {pos[1].x + 100, pos[1].y, 30, 30}, // 2 -
        {pos[1].x + 300, pos[1].y, 30, 30}  // 2 +
    };
    DrawButton3(but[0], "+");
    stringstream s1, s2;
    s1 << (1 - tickDefault) * 10;
    const char *spd1 = s1.str().c_str();
    s2 << (1 - tickDefault2) * 10;
    const char *spd2 = s2.str().c_str();

    DrawButton3(but[0], "-");
    DrawText(spd1, pos[0].x + 200 - MeasureText(spd1, 20) / 2, pos[0].y, 20, WHITE);
    DrawButton3(but[1], "+");
    if (gameplay2)
    {
        DrawText("Player 2: ", pos[1].x, pos[1].y, 20, WHITE);
        DrawButton3(but[2], "-");
        DrawText(spd2, pos[1].x + 200 - MeasureText(spd2, 20) / 2, pos[1].y, 20, WHITE);
        DrawButton3(but[3], "+");
    }

    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (click)
    {
        if (CheckCollisionPointRec(GetMousePosition(), mode[0]))
            gameplay2 = false;
        else if (CheckCollisionPointRec(GetMousePosition(), mode[1]))
            gameplay2 = true;

        if (CheckCollisionPointRec(GetMousePosition(), but[0]) && (tickDefault * 10 < 9))
            tickDefault += 0.1;
        if (CheckCollisionPointRec(GetMousePosition(), but[1]) && (tickDefault * 10 > 2))
            tickDefault -= 0.1;
        if (CheckCollisionPointRec(GetMousePosition(), but[2]) && (tickDefault2 * 10 < 9))
            tickDefault2 += 0.1;
        if (CheckCollisionPointRec(GetMousePosition(), but[3]) && (tickDefault2 * 10 > 2))
            tickDefault2 -= 0.1;
    }
}

void CreateBlock(dif Dif, Game &game, Game &game2)
{
    int row = 10;
    int count = Dif;
    for (int i = 0; i < count; i++)
    {
        int ro = rand() % 4;
        while (ro--)
        {
            game.RotateBlock();
            game2.RotateBlock();
        }
        //           x
        int x = 1 + rand() % (row);
        while (x--)
        {
            game.MoveRight();
            game2.MoveRight();
        }

        x = 1 + rand() % (row);
        while (x--)
        {
            game.MoveLeft();
            game2.MoveLeft();
        }
        // game.curblock.Move(0, x);
        game.FitMoveDown();
        game2.FitMoveDown();
    }
}
bool CheckErrFile(const char *p, string s)
{
    if (s == "in")
    {
        ifstream f(p, ios_base::in | ios_base::binary);
        if (!f)
        {
            cerr << "loi mo tep!" << endl;
            return false;
        }
        cerr << "Load " << p << " successfully" << endl;
        return true;
    }
    else if (s == "out")
    {
        ofstream f(p, ios_base::out | ios_base::binary);
        if (!f)
        {
            cerr << "loi mo tep!" << endl;
            return false;
        }
        cerr << "Saved " << p << " successfully" << endl;
        return true;
    }
    return false;
}
void LoadGameMode()
{
    if (CheckErrFile("save/save.mode", "in"))
    {
        ifstream f("save/save.mode", ios_base::in | ios_base::binary);
        f.read(reinterpret_cast<char *>(&gameplay2), sizeof(gameplay2));
        f.read(reinterpret_cast<char *>(&tickDefault), sizeof(tickDefault));
        f.read(reinterpret_cast<char *>(&tickDefault2), sizeof(tickDefault2));
        f.close();
    }
}
void SaveGameMode()
{
    if (CheckErrFile("save/save.mode", "out"))
    {
        ofstream f("save/save.mode", ios_base::out | ios_base::binary);
        f.write(reinterpret_cast<char *>(&gameplay2), sizeof(gameplay2));       // save mode
        f.write(reinterpret_cast<char *>(&tickDefault), sizeof(tickDefault));   // same sleep game 1
        f.write(reinterpret_cast<char *>(&tickDefault2), sizeof(tickDefault2)); // save game 2
        f.close();
    }
}

void SaveGame(Game &game, Game &game2)
{
    if (CheckErrFile("save/game1.save", "out"))
    {
        ofstream f("save/game1.save", ios_base::out | ios_base::binary);
        game.saveGame("save/game1.save");
    }
    if (CheckErrFile("save/game2.save", "out"))
    {
        ofstream f("save/game2.save", ios_base::out | ios_base::binary);
        game2.saveGame("save/game2.save");
    }
}

void LoadGame(Game &game, Game &game2)
{
    if (CheckErrFile("save/game1.save", "in"))
    {
        ofstream f("save/game1.save", ios_base::in | ios_base::binary);
        game.loadGame("save/game1.save");
    }
    if (CheckErrFile("save/game2.save", "in"))
    {
        ofstream f("save/game2.save", ios_base::in | ios_base::binary);
        game2.loadGame("save/game2.save");
    }
}
