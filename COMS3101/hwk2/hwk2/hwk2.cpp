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
	virtual bool isValid() { return true; }
	virtual bool isOver() { return false; }
	virtual void PrintGamePosition() { return; };
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
		numberOfPlayers = 1;
		for (int i = 8; i > -1; --i)
			for (int j = 8; j > -1; --j)
				values[i][j] = v[i][j];
	}
	void readDataFromFile(char *fileName)
	{
		FILE *fp = NULL;
		if ((fp = fopen(fileName, "r")) == NULL)
		{
			std::cout << "Can't open file for reading" << std::endl;
			return;
		}
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				fscanf(fp, "%d", &values[i][j]);
		fclose(fp);
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
			for(j = 9; j >= 0; --j)
				present[j] = false;
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
			for (j = 9; j >= 0; --j)
				present[j] = false;
			for (j = 8; i > -1; --i)
			{
				if (present[values[j][i]] == true)
					return false;
				if (present[values[j][i]] == false)
					present[values[j][i]] = true;
			}
		}
		// squares
		/*for (i = 0; i < 3; i++)
		{
			for (j = 9; j >= 0; --j)
				present[j] = false;
			for (j = 0; i > -1; --i)
			{
				if (present[values[j][i]] == true)
					return false;
				if (present[values[j][i]] == false)
					present[values[j][i]] = true;
			}
			i++;
		}*/
		return true;
	}
	bool isOver()
	{
		for (int i = 8; i > -1; --i)
			for (int j = 8; j > -1; --j)
				if (values[i][j] < 0)
					return false;
		return true;
	}
	void PrintGamePosition()
	{
		for (int i = 8; i > -1; --i)
		{
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
	
    return 0;
}

