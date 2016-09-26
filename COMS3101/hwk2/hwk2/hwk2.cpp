// hwk2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Game
{
protected:
	int numberOfPlayers;
public:
	Game() { numberOfPlayers = 1; }
	Game(int n) { numberOfPlayers = n; }
	bool isValid() { return true; }
	bool isOver() { return false; }
	void PrintGamePosition();
};

class Sudoku : public Game
{
private:
	int values[9][9];
public:
	Sudoku()
	{
		numberOfPlayers = 1;
		for (int i = 8; i > -1; --i)
			for (int j = 8; j > -1; --j)
				values[i][j] = 0;
	}
	Sudoku(int v[9][9])
	{
		for (int i = 8; i > -1; --i)
			for (int j = 8; j > -1; --j)
				values[i][j] = v[i][j];
	}
	void readDataFromFile(char *fileName)
	{
		return;
	}
	bool isValid()
	{
		for (int i = 8; i > -1; --i)
			for (int j = 8; j > -1; --j)
				if (values[i][j] > 9 || values[i][j] < 0)
					return false;
		return true;
	}
	bool isCorrect()
	{
		bool present[9] = {false,false,false,false,false,false,false,false,false};
		int i, j;
		// rows
		for (i = 8; i > -1; --i)
		{
			present = { false,false,false,false,false,false,false,false,false };
			for (j = 8; i > -1; --i)
			{
				if (present[values[i][j]] == true)
					return false;
				if (present[values[i][j]] == false)
					present[values[i][j]] = true;
			}
		}
		// columns
		for (i = 8; i > -1; --i)
		{
			present = { false,false,false,false,false,false,false,false,false };
			for (j = 8; i > -1; --i)
			{
				if (present[values[j][i]] == true)
					return false;
				if (present[values[j][i]] == false)
					present[values[j][i]] = true;
			}
		}
		// squares
		for (i = 0; i < 9; ++i)
		{
			present = { false,false,false,false,false,false,false,false,false };
			for (j = 8; i > -1; --i)
			{
				if (present[values[j][i]] == true)
					return false;
				if (present[values[j][i]] == false)
					present[values[j][i]] = true;
			}
		}
		return true;
	}
	bool isOver()
	{
		return false;
	}
	void PrintGamePosition()
	{
		for (int i = 8; i > -1; --i) {
			for (int j = 8; j > -1; --j)
				std::cout << values[i][j];
			std::cout << std::endl;
		}
		return;
	}
};

int main()
{
	Sudoku sdk;
	sdk.readDataFromFile("file.txt");
	do {
		sdk.PrintGamePosition();
	} while (sdk.isOver());
    return 0;
}

