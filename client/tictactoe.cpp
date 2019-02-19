#include "tictactoe.h"

// board size is 3x3
#define BOARDSIZE 3

using namespace std;

// constructor, fills each index with "_" 
int TicTacToe::game(){
    for (int i = 0; i < BOARDSIZE; i++){
        board[i] = "___";
    }
    complete = false;
    return 0;
}

// adds X based on user input, checks for a win
int TicTacToe::addX(int x, int y){
    board[x][y] = 'X';
    if ((board[x][0] == 'X' && board[x][1] == 'X' && board[x][2] == 'X') 
    || (board[0][y] == 'X' && board[1][y] == 'X' && board[2][y] == 'X')
    || (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
    || (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')){
        complete = true;
    }
    return 0;
}

// adds O based on server input, checks for win
int TicTacToe::addO(int x, int y){
    board[x][y] = 'O';
    if ((board[x][0] == 'O' && board[x][1] == 'O' && board[x][2] == 'O') 
    || (board[0][y] == 'O' && board[1][y] == 'O' && board[2][y] == 'O')
    || (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
    || (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O')){
        complete = true;
    }
    return 0;
}

// returns true if game is over
bool TicTacToe::isGameOver(){
    return complete;
}

// returns true if move is valid
bool TicTacToe::isValidMove(int x, int y){
    char empty = '_';
    if((x < 0 || x > 2) || (y < 0 || y > 2)){
        return false;
    }
    if (board[x][y] != empty){
        return false;
    }
    return true;
}

// prints out current state of board
void TicTacToe::displayBoard(){
    for (int i = 0; i < GAMESIZE; i++){
        for (int j = 0; j < GAMESIZE; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << complete << endl;
    return;
}