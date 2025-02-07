#pragma once

class position
{
public:
	int row, col;
	position() : row(0), col(0) {} // Constructor mặc định
	position(int row, int col)
	{
		this->row = row;
		this->col = col;
	};
};