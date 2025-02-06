#include "game.h"
// vector<Block> Game::blockPool = {};
Game::Game(int seed) : seed(seed)
{
	blockPool = {};
	grid = Grid();
	id = 0;
	blocks = GetAllBlock();
	curblock = GetRandBlock();
	nexblock = GetRandBlock();
	gameover = false;
	score = 0;
}

Block Game::GetRandBlock()
{
	if (blockPool.empty() || id >= (int)blockPool.size())
	{
		InitBlockPool();
		id = 0; // Reset index
	}
	// Lấy block tại vị trí id và tăng index
	Block block = blockPool[id];
	id++;
	return block;
}
vector<Block> GetAllBlock()
{
	return {JBlock(), IBlock(), LBlock(), OBlock(), SBlock(), ZBlock(), TBlock()};
}
void Game::Draw(int start)
{
	grid.draw(start);
	curblock.Draw(start + 11, 11);
	switch (nexblock.id)
	{
	case 3:
		nexblock.Draw(start + 255, 255);
		break;
	case 4:
		nexblock.Draw(start + 255, 245);
		break;

	default:
		nexblock.Draw(start + 270, 235);
		break;
	}
}
void Game::MoveLeft()
{
	if (!gameover)
	{
		curblock.Move(0, -1);
		if (isBlockOut() || BlockFit() == false)
			curblock.Move(0, 1);
	}
}
void Game::MoveRight()
{
	if (!gameover)
	{
		curblock.Move(0, 1);
		if (isBlockOut() || BlockFit() == false)
			curblock.Move(0, -1);
	}
}
void Game::MoveDown()
{
	if (!gameover)
	{
		curblock.Move(1, 0);
		if (isBlockOut() || BlockFit() == false)
		{
			curblock.Move(-1, 0);
			LockBlock();
		}
	}
}
void Game::FitMoveDown()
{
	if (!gameover)
	{
		while (1)
		{
			curblock.Move(1, 0);
			if (isBlockOut() || BlockFit() == false)
			{
				curblock.Move(-1, 0);
				LockBlock();
				break;
			}
		}
	}
}
void Game::RotateBlock()
{
	if (!gameover)
	{
		curblock.Rotate();
		if (isBlockOut() || BlockFit() == false)
			curblock.UnRotate();
	}
}
void Game::InitBlockPool()
{
	srand(seed);
	blockPool.clear();
	vector<Block> temp = GetAllBlock();
	shuffle(temp.begin(), temp.end(), default_random_engine(seed));
	blockPool.insert(blockPool.end(), temp.begin(), temp.end());
	seed = rand() % 1000;
}
bool Game::checkArrowKey(int key)
{
	return (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_DOWN || key == KEY_UP);
}
void Game::Inp(int key)
{
	switch (key)
	{
	case KEY_RIGHT:
		MoveRight();
		break;
	case KEY_LEFT:
		MoveLeft();
		break;
	case KEY_DOWN:
		MoveDown();
		break;
	case KEY_UP:
		RotateBlock();
		break;
	}
}
void Game::Inp2(int key)
{
	switch (key)
	{
	case KEY_D:
		MoveRight();
		break;
	case KEY_A:
		MoveLeft();
		break;
	case KEY_S:
		MoveDown();
		break;
	case KEY_W:
		RotateBlock();
		break;
	}
}

void Game::Reset()
{
	InitBlockPool();
	id = 0;
	grid.khoitao();
	blocks = GetAllBlock();
	curblock = GetRandBlock();
	nexblock = GetRandBlock();
	gameover = false;
	score = 0;
}

string Game::GetHightScore()
{
	string highscore;
	ifstream f("src/tetris.hightscore");
	getline(f, highscore);
	f.close();
	return highscore;
}

void Game::UpdateHightScore()
{
	int highscore = stoi(GetHightScore());
	if (score > highscore)
	{
		highscore = score;
		ofstream f;
		f.open("src/tetris.hightscore");
		f << highscore;
		f.close();
	}
}

void Game::updateScore(int lineclear, int movedown)
{
	int score_m[] = {100, 300, 500, 700};

	if (lineclear > 0 && lineclear <= 4)
		score += score_m[lineclear - 1];
}

bool Game::isBlockOut()
{
	vector<position> title = curblock.getCells();
	for (auto i : title)
		if (grid.IsCellOut(i.row, i.col))
			return true;
	return false;
}

void Game::LockBlock()
{
	vector<position> title = curblock.getCells();
	for (auto i : title)
		grid.grid[i.row][i.col] = curblock.id;
	curblock = nexblock;
	if (BlockFit() == false)
	{
		gameover = true;
		curblock.Move(-1, 0);
	}
	nexblock = GetRandBlock();
	updateScore(grid.ClearFullRow(), 0);
}

bool Game::BlockFit()
{
	vector<position> title = curblock.getCells();
	for (auto i : title)
		if (grid.IsCellEmpt(i.row, i.col) == false)
			return false;
	return true;
}
// save Game
void Game::saveGame(const char *path)
{
	// ofstream f(path, ios_base::out | ios_base::binary);
	ofstream f(path, ios_base::out);
	// Grid grid;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			f.write(reinterpret_cast<const char *>(&grid.grid[i][j]), sizeof(grid.grid[i][j]));
	// Game(int seed);
	// int seed;
	f.write(reinterpret_cast<const char *>(&seed), sizeof(seed));
	// int id;
	f.write(reinterpret_cast<const char *>(&id), sizeof(id));
	// int score;
	f.write(reinterpret_cast<const char *>(&score), sizeof(score));
	// bool gameover;
	// Block curblock;
	vector<position> title = curblock.getCells();
	for (auto i : title)
		f.write(reinterpret_cast<const char *>(&i), sizeof(i));
	// Block nexblock;
	vector<position> title1 = nexblock.getCells();
	for (auto i : title)
		f.write(reinterpret_cast<const char *>(&i), sizeof(i));
	// vector<Block> blockPool;
	for(auto i : blockPool)
	{
		vector<position> title2 = i.getCells();
		for (auto j : title2)
			f.write(reinterpret_cast<const char *>(&j), sizeof(j));
	}
	f.close();
}
// load Game
void Game::loadGame(const char *path)
{
	// ifstream f(path, ios_base::in | ios_base::binary);
	ifstream f(path, ios_base::in);
	// Grid grid;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			f.read(reinterpret_cast<char *>(&grid.grid[i][j]), sizeof(grid.grid[i][j]));
	// Game(int seed);
	// int seed;
	f.read(reinterpret_cast<char *>(&seed), sizeof(seed));
	// int id;		
	f.read(reinterpret_cast<char *>(&id), sizeof(id));
	// int score;
	f.read(reinterpret_cast<char *>(&score), sizeof(score));
	// bool gameover;
	// Block curblock;
	vector<position> title = curblock.getCells();
	for (auto i : title)
		f.read(reinterpret_cast<char *>(&i), sizeof(i));
	// Block nexblock;
	vector<position> title1 = nexblock.getCells();
	for (auto i : title)
		f.read(reinterpret_cast<char *>(&i), sizeof(i));
	// vector<Block> blockPool;
	for(auto i : blockPool)
	{
		vector<position> title2 = i.getCells();
		for (auto j : title2)
			f.read(reinterpret_cast<char *>(&j), sizeof(j));
	}
	f.close();
}