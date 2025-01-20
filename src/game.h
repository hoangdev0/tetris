#pragma once
#include <bits/stdc++.h>
#include "grid.h"
#include "tetrominos.cpp"
using namespace std;

class Game
{
public:
	Game();
	vector<Block> GetAllBlock();
	bool gameover;
	int score;
	void Draw(int start);
	void Inp(int key);
	void Inp2(int key);
	void MoveDown();
	void Reset();
	string GetHightScore();
	void UpdateHightScore();
	Block curblock;

private:
	bool checkArrowKey(int key);
	Block GetRandBlock();
	void updateScore(int lineclear, int movedown);
	void MoveLeft();
	void MoveRight();
	Grid grid;
	bool isBlockOut();
	void RotateBlock();
	void LockBlock();
	bool BlockFit();
	vector<Block> blocks;
	Block nexblock;
};