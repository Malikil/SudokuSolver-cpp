#pragma once

#include <iostream>
#include "Number.h"

class SudokuBoard
{
private:
	// Represent the board with a 2D array of Numbers
	Number board[9][9];

public:
	SudokuBoard();
	SudokuBoard(const SudokuBoard&);
	SudokuBoard(const int[][9]);

	bool solve();

	bool solved() const;
	void print(std::ostream&) const;

private:
	void copyBoard(const SudokuBoard&);
	bool knownCell(int, int) const;
	bool filterNumbers();
	int firstUnknownCell() const;
	bool operator==(const SudokuBoard&) const;
	bool operator!=(const SudokuBoard&) const;
};

