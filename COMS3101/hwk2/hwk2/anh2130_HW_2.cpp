// Adam Hadar, anh2130
// COMS3101, hwk2
// Sudoku
// hwk2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>

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
        std::ifstream fp (fileName);
        if(fp.is_open())
        {
            for(int i = 0; !fp.eof() || i < 9; ++i)
                for(int j = 0; !fp.eof() || j < 9; ++j)
                    fp >> values[i][j];
            fp.close();
        }
        else
            std::cout << "Can't open file for reading" << std::endl;
        return;
	}
	bool isValid()
	{
        // row
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
                for(int k = j+1; k < 9; ++k)
                    if(values[i][j] != 0 && values[i][j] == values[i][k])
                        return false;
		// column
        for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
                for(int k = j+1; k < 9; ++k)
                    if(values[j][i] != 0 && values[j][i] == values[k][i])
                        return false;
        // squares
		for(int x = 0; x < 3; ++x)
        for(int y = 0; y < 3; ++y)
            for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                for(int k = 0; k < 3; ++k)
                for(int l = 0; l < 3; ++l)
                if((i != k && j != l) && values[x*3+i][y*3+j] != 0 && values[x*3+i][y*3+j] == values[x*3+k][y*3+l])
                    return false;
        return true;
	}
	bool isCorrect()
	{
        // no zeroes
        for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
                if(values[i][j] == 0)
                    return false;
        // row
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
                for(int k = j+1; k < 9; ++k)
                    if(values[i][j] == values[i][k])
                        return false;
		// column
        for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
                for(int k = j+1; k < 9; ++k)
                    if(values[j][i] == values[k][i])
                        return false;
        // squares
		for(int x = 0; x < 3; ++x)
        for(int y = 0; y < 3; ++y)
            for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                for(int k = 0; k < 3; ++k)
                for(int l = 0; l < 3; ++l)
                if((i != k && j != l) && values[x*3+i][y*3+j] == values[x*3+k][y*3+l])
                    return false;
		return true;
	}
	bool isOver()
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				if (!values[i][j])
					return false;
		return true;
	}
	void PrintGamePosition()
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
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
    sdk.PrintGamePosition();
    if(sdk.isOver()) std::cout << "it is over" << std::endl;
    else             std::cout << "it is not over" << std::endl;
    if(sdk.isValid()) std::cout << "it is valid" << std::endl;
    else              std::cout << "it is not valid" << std::endl;
    if(sdk.isCorrect()) std::cout << "it is correct" << std::endl;
    else                std::cout << "it is not correct" << std::endl;
    return 0;
}

