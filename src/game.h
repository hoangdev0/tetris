#pragma once
#include <bits/stdc++.h>
#include "grid.h"
#include "tetrominos.cpp"
using namespace std;
vector<Block> GetAllBlock();
class Game
{
public:
	Game();
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
	Block nexblock;
	Block GetRandBlock();
	vector<Block> blocks;
	bool BlockFit();
	static vector<Block> blockPool; // Danh sách block chung
	int id;							// Vị trí hiện tại trong blockPool			// Seed ban đầu
	static void InitBlockPool();	// Khởi tạo blockPool với seed hiện tại

private:
	bool checkArrowKey(int key);
	void updateScore(int lineclear, int movedown);
	void MoveLeft();
	void MoveRight();
	Grid grid;
	bool isBlockOut();
	void RotateBlock();
	void LockBlock();
};