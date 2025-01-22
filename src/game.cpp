#include "game.h"

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlock();
	curblock = GetRandBlock();
	nexblock = GetRandBlock();
	gameover = false;
	score = 0;
}

Block Game::GetRandBlock()
{
	if (blocks.empty())
		blocks = GetAllBlock();
	int index = rand() % blocks.size();
	Block block = blocks[index];
	blocks.erase(blocks.begin() + index);
	return block;
}
vector<Block> Game::GetAllBlock()
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
void Game::RotateBlock()
{
	if (!gameover)
	{
		curblock.Rotate();
		if (isBlockOut() || BlockFit() == false)
			curblock.UnRotate();
	}
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
