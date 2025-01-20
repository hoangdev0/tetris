#pragma once
#include <bits/stdc++.h>
#include "color.h"
#include <raylib.h>
using namespace std;
class Grid
{
private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row,int num);
	int row, col, cellSize;
	vector<Color> color;

public:
	Grid();
	int grid[20][10];
	void khoitao();
	void print();
	void draw(int start);
	bool IsCellOut(int row, int col);
	bool IsCellEmpt(int row, int col);
	int ClearFullRow();
};