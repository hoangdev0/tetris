#pragma once
#include <bits/stdc++.h>
#include "grid.h"
#include "tetrominos.cpp"
#include "path.h"
using namespace std;
vector<Block> GetAllBlock();
class Game
{
public:
	Grid grid;
	Game(int seed);
	int seed;
	int id;							// Vị trí hiện tại trong blockPool			// Seed ban đầu
	int score;
	bool gameover;
	Block curblock;
	Block nexblock;
	vector<Block> blockPool;		// Danh sách block chung
	void Draw(int start);
	void Inp(int key);
	void Inp2(int key);
	void FitMoveDown();
	void Reset();
	string GetHightScore();
	void UpdateHightScore();
	Block GetRandBlock();
	vector<Block> blocks;
	bool BlockFit();
	// static vector<Block> blockPool; // Danh sách block chung
	// static void InitBlockPool();	// Khởi tạo blockPool với seed hiện tại
	void InitBlockPool();
	void MoveDown();
	bool checkArrowKey(int key);
	void updateScore(int lineclear, int movedown);
	void MoveLeft();
	void MoveRight();
	bool isBlockOut();
	void RotateBlock();
	void LockBlock();
	void saveGame(const char *);
	void loadGame(const char *);

private:
	//...
};