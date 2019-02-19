#include <iostream>
#include <string>

#define GAMESIZE 3 

using namespace std;

class TicTacToe{
    public:
        //constructor
        int game();
        //add an x
        int addX(int x, int y);
        //add an o
        int addO(int x, int y);
        //game is over
        bool isGameOver();
        //is move valid
        bool isValidMove(int x, int y);
        //display the game board;
        void displayBoard();


    private:
        bool complete;
        string board[GAMESIZE];
};