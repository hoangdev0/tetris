#include "Source.h"

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
    DrawText(txt, Button.x + (Button.width - MeasureText(txt, 30)) / 2, Button.y + 25, 30, lightviolet);
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
void BackButton(gameState &Gamestate)
{
    Rectangle back = {165, 510, 170, 60};
    DrawRectangleRounded(back, 0.3, 6, lightblue);
    DrawText("BACK", back.x + 45, back.y + 17, 30, WHITE);
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (click && CheckCollisionPointRec(GetMousePosition(), back)){
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
void LoadGameMode()
{
    ifstream f("save/save.mode", ios_base::binary);
    if (!f) {
        cerr << "loi mo tep!" << endl;
        return;
    }
    cerr << "Load Mode and Speed ok." << endl;
    f.read(reinterpret_cast<char *>(&gameplay2), sizeof(gameplay2));
    f.read(reinterpret_cast<char *>(&tickDefault), sizeof(tickDefault));
    f.read(reinterpret_cast<char *>(&tickDefault2), sizeof(tickDefault2));
    f.close();
}
void SaveGameMode()
{
    ofstream f("save/save.mode", ios_base::binary);
    if (!f) {
        cerr << "loi mo tep!" << endl;
        return;
    }
    cerr << "Saved mode and speed." << endl;
    f.write(reinterpret_cast<char *>(&gameplay2), sizeof(gameplay2)); // save mode
    f.write(reinterpret_cast<char *>(&tickDefault), sizeof(tickDefault)); // same sleep game 1
    f.write(reinterpret_cast<char *>(&tickDefault2), sizeof(tickDefault2)); // save game 2
    f.close();
}

void SaveGrid(Game &game, Game &game2)
{
    ofstream f("save/save.gird", ios_base::binary);
    if (!f) {
        cerr << "loi mo tep!" << endl;
        return;
    }
    cerr << "Saved grid." << endl;
    f.write(reinterpret_cast<char *>(&game.grid), sizeof(game.grid));
    f.write(reinterpret_cast<char *>(&game2.grid), sizeof(game2.grid));
    game.grid.print(); cout <<"\n";
    game2.grid.print();
    f.close();
}

void LoadGrid(Game &game, Game &game2)
{
    ifstream f("save/save.gird", ios_base::binary);
    if (!f) {
        cerr << "loi mo tep!" << endl;
        return;
    }
    cerr << "Load Grid ok." << endl;
    f.read(reinterpret_cast<char *>(&game.grid), sizeof(game.grid));
    f.read(reinterpret_cast<char *>(&game2.grid), sizeof(game2.grid));
    game.grid.print(); cout <<"\n";
    game2.grid.print();
    f.close();
}
