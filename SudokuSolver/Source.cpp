#include "SudokuBoard.h"
#include <iostream>

int main()
{
	int init[9][9] = {
		{ 0, 2, 0, 0, 8, 1, 9, 0, 0 },
		{ 0, 0, 0, 0, 9, 0, 0, 0, 0 },
		{ 9, 0, 0, 6, 5, 2, 8, 0, 0 },
		{ 0, 7, 4, 0, 0, 0, 0, 0, 0 },
		{ 0, 9, 5, 0, 2, 0, 6, 7, 0 },
		{ 0, 0, 0, 0, 0, 0, 5, 8, 0 },
		{ 0, 0, 8, 9, 4, 6, 0, 0, 5 },
		{ 0, 0, 0, 0, 3, 0, 0, 0, 0 },
		{ 0, 0, 7, 8, 1, 0, 0, 6, 0 }
	};

	SudokuBoard board(init);
	board.print(std::cout);
	std::cout << "Solved: " << board.solve() << std::endl;
	board.print(std::cout);

	return 0;
}