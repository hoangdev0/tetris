#include "block.h"

Block::Block()
{
	cellSize = 30;
	rotation = 0;
	color = getcolor();
	rowOffset = colOffset = 0;
}

void Block::Draw(int x, int y)
{
	vector<position> title = getCells();
	for (auto i : title)
	{
		DrawRectangle(i.col * cellSize + x, i.row * cellSize + y, cellSize - 1, cellSize - 1, color[id]);
	}
}

void Block::Move(int rows, int cols)
{
	rowOffset += rows;
	colOffset += cols;
}

void Block::Rotate()
{
	rotation = (rotation + 1) % 4;
}

void Block::UnRotate()
{
	rotation = (rotation + 3) % 4;
}

vector<position> Block::getCells()
{
	vector<position> title = cells[rotation];
	vector<position> movedTitle;
	for (auto i : title)
	{
		position newPos = position(i.row + rowOffset, i.col + colOffset);
		movedTitle.push_back(newPos);
	}
	return movedTitle;
}