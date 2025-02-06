#pragma once
#include <bits/stdc++.h>
#include "grid.h"
#include "tetrominos.cpp"
using namespace std;
vector<Block> GetAllBlock();
class Game
{
public:
	Game(int seed);
	int seed;
	bool gameover;
	int score;
	void Draw(int start);
	void Inp(int key);
	void Inp2(int key);
	void HandMoveDown();
	void Reset();
	string GetHightScore();
	void UpdateHightScore();
	Block curblock;
	Block nexblock;
	Block GetRandBlock();
	vector<Block> blocks;
	bool BlockFit();
	int id;							// Vị trí hiện tại trong blockPool			// Seed ban đầu
	// static vector<Block> blockPool; // Danh sách block chung
	// static void InitBlockPool();	// Khởi tạo blockPool với seed hiện tại
	vector<Block> blockPool;		// Danh sách block chung
	void InitBlockPool();
	void MoveDown();
	Grid grid;

private:
	bool checkArrowKey(int key);
	void updateScore(int lineclear, int movedown);
	void MoveLeft();
	void MoveRight();
	bool isBlockOut();
	void RotateBlock();
	void LockBlock();
};