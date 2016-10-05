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
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				values[i][j] = 0;
	}
	Sudoku(int v[9][9])
	{
		numberOfPlayers = 1;
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				values[i][j] = v[i][j];
	}
	void readDataFromFile(char *fileName)
	{
		FILE *fp = NULL;
		//if ((fp = fopen(fileName, "r")) == NULL)
		if ((fopen_s(&fp,fileName, "r")) != 0)
		{
			std::cout << "Can't open file for reading" << std::endl;
			return;
		}
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				//fscanf(fp, "%d", &values[i][j]);
		        fscanf_s(fp, "%d", &values[i][j]);
		fclose(fp);
	}
	bool isValid()
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				if (values[i][j] > 9 || values[i][j] < 0)
					return false;
		return true;
	}
	bool isCorrect()
	{
		if (values[0][0] == values[1][1])
			std::cout << "oops" << std::endl;
		return true;
	}
	bool isOver()
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				if (values[i][j] <= 0)
					return false;
		return true;
	}
	void PrintGamePosition()
	{
		for (int i = 0; i < 9; ++i)
			std::cout << values[0][i] << std::endl;
		return;
	}
};

int main()
{
	Sudoku sdk;
	Sudoku s1 = Sudoku();
	sdk.readDataFromFile("file.txt");
	sdk.PrintGamePosition();
	if (sdk.isOver())
		std::cout << "it is over" << std::endl;
	else
		std::cout << "it is not over" << std::endl;
	if (sdk.isValid())
		std::cout << "it is valid" << std::endl;
	else
		std::cout << "it is not valid" << std::endl;
	sdk.isCorrect();
	s1.PrintGamePosition();
	/*
	if (sdk.isCorrect())
		std::cout << "it is correct" << std::endl;
	else
		std::cout << "it is not correct" << std::endl;
	*/
    return 0;
}

