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