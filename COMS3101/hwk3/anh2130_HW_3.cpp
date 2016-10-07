/*
 *  Filename:   anh2130_HW_3.cpp
 *  Author:     Adam Hadar, anh2130
 *  Purpose:    A simple chess implementation.
 *  Edited:     2016-10-07
 */

#include <iostream>
#include <stdio.h>

class Game
{
    private:
	int numberOfPlayers;
    public:
	Game() { numberOfPlayers = 1; }
	Game(int n) { numberOfPlayers = n; }
	virtual bool isValid(void) =0;
	virtual bool isOver(void) =0;
	virtual void PrintGamePosition(void) =0;
        int getNumPlayers(void) { return numberOfPlayers; }
        void setNumPlayers(int n) { numberOfPlayers = n; return; }
};

/*
 * i) It is aggravating that one does not know the intrinsic locations of other pieces
 *        immediately - I tried to implement isOver(), but it requires many checks in
 *        neighbor (and neighbor of neighbor) squares. Either you can write up a 'Piece'
 *        class and makes several child classes called 'King' and 'Pawn' (and this would
 *        help to extend the game to more pieces later), or you could use a couple arrays
 *        to keep track of counts and positions. To jump ahead to (iii), you could keep a
 *        simple boolean 'is_white_turn' to know where to implement the move.
 *
 * ii) It would be helpful to implement a 'getMove()' function. It would have to attempt
 *        depending on how smart we want it to be, we could make lots of checks - if the
 *        king is in check then the submitted moved has to be a king move away from check.
 *        
 *        A 'isUnderAttackBy(bool,int,int)' function that checks if a specific square
 *        on the board is under attack by pieces from given team
 *
 *        More importantly, it would be ideal to have a 'run()' function inside the class.
 *        If the game runs itself, you could keep track of any of the user I/O issues that
 *        arise easily not have to have a main that keeps track of those vagaries.
 *
 *        These two are the important ones - of course there could be many other helper
 *        functions to reduce redundancy, but nothing else is needed to implement the game.
 *
 * iv) Deciding if the game is over is simply a matter of implementing bool isOver as follows:
 *        for each king k:
 *            // .adjacent_squares here hides that you need to check if the king is next
 *            // to a border, and not check those squares
 *            for each k.adjacent_squares s:
 *                if isUnderAttackBy(enemy,s) == false:
 *                    return true;
 *            return false;
 *                
 */
class Chess: public Game
{
    private:
        // the read function kept including LFs, so I increased by 1
        char board[8][9];
        /*
        Pawn p_white[8], p_black[8];
        King k_white, k_black;
        int p_white_ct = 8;
        int p_black_ct = 8;
        bool is_white_turn = true;
        */ 
    public:
        Chess()
        {
            setNumPlayers(2);
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                    board[i][j] = '0';
        }
        void readDataFromFile(char *fileName)
        {
            FILE *fp = NULL;
            if((fp = fopen(fileName, "r")) == NULL)
            {
                std::cout << "Can't open file for reading" << std::endl;
                return;
            }
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 9; j++)
                    fscanf(fp, "%c", &board[i][j]);
            fclose(fp);
            return;
        }
        void PrintGamePosition(void)
        {
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 9; j++)
                    std::cout << (board[i][j] == '0'? ' ': board[i][j]);
            return;
        }
        bool isValid(void)
        {
            bool white_king = false;
            bool black_king = false;
            int white_pawn_ct = 0;
            int black_pawn_ct = 0;
            int diff_kings_x = 0;
            int diff_kings_y = 0;
            int i, j;

            for(i = 0; i < 8; i++)
                if(board[0][i] == 'P' || board[7][i] == 'p')
                    return false;

            for(i = 0; i < 8; i++)
                for(j = 0; j < 8; j++)
                {
                    switch (board[i][j])
                    {
                        case 'K':{
                            if(white_king)
                                return false;
                            else
                            {
                                white_king = true;
                                diff_kings_x += i;
                                diff_kings_y += j;
                            }
                            break;}
                        case 'k':{
                           if(black_king)
                                return false;
                            else
                            {
                                black_king = true;
                                diff_kings_x -= i;
                                diff_kings_y -= j;
                            }
                            break;}
                        case 'P':{
                            white_pawn_ct++;
                            break;}
                        case 'p':{
                            black_pawn_ct++;
                            break;
                        }
                        default:
                             break;
                    }
                }
            if (white_pawn_ct > 8 || black_pawn_ct > 8)
                return false;
            if(diff_kings_x >= -1 && diff_kings_x <= 1 &&
                    diff_kings_y >= -1 && diff_kings_y <= 1)
                return false;
            return true;
        }
        bool isOver(void)
        {
            return false;
        }
};

int main(void)
{
    Chess cs = Chess();
    cs.readDataFromFile("game.txt");
    cs.PrintGamePosition();
    std::cout << (cs.isValid()? "": "not ") << "valid" << std::endl;
    std::cout << (cs.isOver()? "": "not ") << "over" << std::endl;
    return 0;
}
