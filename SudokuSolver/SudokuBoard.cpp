#include "SudokuBoard.h"
#include "Number.h"
#include <iostream>

SudokuBoard::SudokuBoard()
{
	// Initialize board
	// On an empty board, every cell can be any number
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			board[r][c] = Number::All;
}

SudokuBoard::SudokuBoard(const SudokuBoard& init)
{
	copyBoard(init);
}

SudokuBoard::SudokuBoard(const int init[][9])
{
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (init[r][c] < 1 || init[r][c] > 9)
				board[r][c] = Number::All;
			else
			{
				int val = 1;
				for (int n = init[r][c]; n > 1; n--)
					val <<= 1;
				board[r][c] = static_cast<Number>(val);
			}
}

bool SudokuBoard::solve()
{
	// Filter numbers down until no changes are made
	while (filterNumbers())
	{
		print(std::cout); // DEBUG
		std::cout << std::endl;
	}
	// If the puzzle isn't solved yet, fill in a random number and solve it again
	if (!solved())
	{
		// Find the first unsolved cell
		int cell = firstUnknownCell();
		// If there aren't any unknown cells then the board is invalid
		if (cell < 0)
			return false;
		int r = cell / 9;
		int c = cell % 9;
		Number available = board[r][c];
		// Assign a value to this cell
		for (Number current = Number::One; current < available; current <<= 1)
			if ((current & available) != Number::None)
			{
				// Make a copy
				SudokuBoard next(*this);
				// Set the value
				next.board[r][c] = current;
				next.print(std::cout); // DEBUG
				std::cout << std::endl;
				// Try to solve from here
				if (next.solve())
				{
					// Set the current board to the solved board and return true
					copyBoard(next);
					return true;
				}
			}
		// All available numbers have been attempted, this board state is invalid
		return false;
	}
	else
		return true;
}

bool SudokuBoard::solved() const
{
	auto checkRow = [&](int r)
	{
		Number found = Number::None;
		for (int c = 0; c < 9; c++)
		{
			// This row is only solved if all numbers are known
			if (!knownCell(r, c))
				return false;
			// The row fails if the same number appears more than once
			else if ((found & board[r][c]) != Number::None)
				return false;
			else
				found |= board[r][c];
		}
		return found == Number::All;
	};
	auto checkCol = [&](int c)
	{
		Number found = Number::None;
		for (int r = 0; r < 9; r++)
		{
			if (!knownCell(r, c))
				return false;
			else if ((found & board[r][c]) != Number::None)
				return false;
			else
				found |= board[r][c];
		}
		return found == Number::All;
	};
	auto checkRegion = [&](int r, int c)
	{
		Number found = Number::None;
		for (int i = 0; i < 9; i++)
		{
			int cellr = (r * 3) + (i / 3);
			int cellc = (c * 3) + (i % 3);
			if (!knownCell(cellr, cellc))
				return false;
			else if ((found & board[cellr][cellc]) != Number::None)
				return false;
			else
				found |= board[cellr][cellc];
		}
		return found == Number::All;
	};
	for (int i = 0; i < 9; i++)
		if (!checkRow(i) || !checkCol(i) || !checkRegion(i / 3, i % 3))
			return false;
	return true;
}

void SudokuBoard::print(std::ostream& out) const
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
			out << board[r][c];
		out << std::endl;
	}
}

void SudokuBoard::copyBoard(const SudokuBoard& init)
{
	// Initialize the board with the given state
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			board[r][c] = init.board[r][c];
}

bool SudokuBoard::knownCell(int r, int c) const
{
	int v = static_cast<int>(board[r][c]);
	// A known cell isn't empty
	return board[r][c] != Number::None &&
		// If exactly one flag is active, then subtracting 1 will set that flag to
		// 0 and all lower flags to 1. If more than one is active the highest flag
		// will still match, thus the expression won't be 0
		((v - 1) & v) == 0;
}

// Updates board state to remove known numbers from unknown cells
// Returns whether any changes were made
bool SudokuBoard::filterNumbers()
{
	SudokuBoard old(*this);
	// For each known cell, remove that number from the rest of the row/column/subsquare
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (knownCell(r, c))
				// Remove this value from other cells
				for (int i = 0; i < 9; i++)
				{
					// From row
					if (i != c)
						board[r][i] -= board[r][c];
					// From column
					if (i != r)
						board[i][c] -= board[r][c];
					// From subsquare
					int subr = (r / 3) * 3;
					int subc = (c / 3) * 3;
					int rmr = subr + (i / 3);
					int rmc = subc + (i % 3);
					if (rmr != r || rmc != c)
						board[rmr][rmc] -= board[r][c];
				}
	return old != *this;
}

int SudokuBoard::firstUnknownCell() const
{
	for (int i = 0; i < 9 * 9; i++)
		if (!knownCell(i / 9, i % 9))
			return i;
	return -1;
}

bool SudokuBoard::operator==(const SudokuBoard& other) const
{
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (board[r][c] != other.board[r][c])
				return false;
	return true;
}
bool SudokuBoard::operator!=(const SudokuBoard& other) const
{
	return !(*this == other);
}

