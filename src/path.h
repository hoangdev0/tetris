#pragma once
#include <bits/stdc++.h>
using namespace std;
#define PATH_LIST                 \
	X(ft, "font/monogram.ttf")    \
	X(bg, "src/background.png")   \
	X(hs, "save/hightscore.save") \
	X(g1, "save/game1.save")      \
	X(g2, "save/game2.save")      \
	X(sgm, "save/mode.save")

enum Path
{
#define X(name, path) name,
	PATH_LIST
#undef X
};

extern const char *paths[];
extern const char *getPath(Path path);