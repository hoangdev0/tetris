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
		DrawRectangle(i.col * cellSize + x, i.row * cellSize + y, cellSize - 1, cellSize - 1, color[id]);
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

void Block::save(ofstream &f) const
{
	f.write(reinterpret_cast<const char *>(&id), sizeof(id));
	size_t mapSize = cells.size();
	f.write(reinterpret_cast<const char *>(&mapSize), sizeof(mapSize));
	for (const auto &pair : cells)
	{
		f.write(reinterpret_cast<const char *>(&pair.first), sizeof(pair.first));
		size_t vectorSize = pair.second.size();
		f.write(reinterpret_cast<const char *>(&vectorSize), sizeof(vectorSize));
		for (const auto &pos : pair.second)
		{
			f.write(reinterpret_cast<const char *>(&pos), sizeof(pos));
		}
	}
}

void Block::load(ifstream &f)
{
	f.read(reinterpret_cast<char *>(&id), sizeof(id));
	size_t mapSize;
	f.read(reinterpret_cast<char *>(&mapSize), sizeof(mapSize));
	for (size_t i = 0; i < mapSize; ++i)
	{
		int key;
		f.read(reinterpret_cast<char *>(&key), sizeof(key));
		size_t vectorSize;
		f.read(reinterpret_cast<char *>(&vectorSize), sizeof(vectorSize));
		vector<position> vec(vectorSize);
		for (auto &pos : vec)
		{
			f.read(reinterpret_cast<char *>(&pos), sizeof(pos));
		}
		cells[key] = vec;
	}
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