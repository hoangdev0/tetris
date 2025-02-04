#include "grid.h"
Grid::Grid()
{
	row = 20;
	col = 10;
	cellSize = 30;
	khoitao();
	color = getcolor();
	
}

void Grid::khoitao()
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			grid[i][j] = 0;
}

void Grid::print()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << grid[i][j] << " ";
		cout << '\n';
	}
}

void Grid::draw(int start)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int cell = grid[i][j];
			DrawRectangle(start+j * cellSize + 11,i * cellSize + 11, cellSize - 1, cellSize - 1, color[cell]);
		}
	}
}

bool Grid::IsCellOut(int rowc, int colc)
{
	return (rowc >= 0 && rowc < row && colc >= 0 && colc < col) == false;
}


bool Grid::IsCellEmpt(int row, int col)
{
	return (grid[row][col] == 0);
}

int Grid::ClearFullRow()
{
	int comp = 0;
	for (int i = row - 1; i >= 0; i--)
		if (IsRowFull(i))
			ClearRow(i), comp++;
		else if (comp > 0)
			MoveRowDown(i, comp);
	return comp;
}

bool Grid::IsRowFull(int row)
{
	for (int i = 0; i < col; i++)
		if (grid[row][i] == 0)
			return false;
	return true;
}

void Grid::ClearRow(int row)
{
	for (int i = 0; i < col; i++)
		grid[row][i] = 0;
}

void Grid::MoveRowDown(int row, int num)
{
	for (int i = 0; i < col; i++)
	{
		grid[row + num][i] = grid[row][i];
		grid[row][i] = 0;
	}
}
