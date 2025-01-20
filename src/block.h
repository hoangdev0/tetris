#pragma once
#include <bits/stdc++.h>
#include "position.h"
#include "color.h"
using namespace std;
class Block
{
public:
	Block();
	void Draw(int x, int y);
	void Move(int rows, int cols);
	vector<position> getCells();
	int id;
	map<int, vector<position>> cells;
	void Rotate();
	void UnRotate();

private:
	int cellSize, rotation;
	vector<Color> color;
	int rowOffset, colOffset;
};