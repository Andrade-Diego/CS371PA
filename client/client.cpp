/*
Diego Andrade
CS371 Fall 2018
Client side C++ program based on the GeeksForGeeks article:
https://www.geeksforgeeks.org/socket-programming-cc/
*/

#include <unistd.h> 
#include <cerrno>
#include <cstdio> 
#include <sys/socket.h> 
#include <cstdlib> 
#include <netinet/in.h> 
#include <cstring> 
#include <iostream>
#include <cmath>
#include <string>
#include <sys/types.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include "tictactoe.h"

#define PORT 8080       // port being used
#define IP "127.0.0.1"  // IP address being used
#define MOVESIZE 2      // size of move

using namespace std;

int main(int argc, char const *argv[]){

    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    int Player1[MOVESIZE], Player2[MOVESIZE];

    // creation of socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        cout << "\n Socket creation error \n"; 
        return -1; 
    } 
      
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr)<=0){ 
        cout << "\nInvalid address/ Address not supported \n"; 
        return -1; 
    } 
   
    // attempts connection
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        cout << "\nConnection Failed \n"; 
        return -1; 
    } 

    
    while (true){

        // construct game object
        TicTacToe Game;
        Game.game();
        Game.displayBoard();
        
        // loop while game isn't over
        while (!Game.isGameOver()){

            // ask user for input
            cout << "Make move: (x,y): ";
            cin >> Player1[0] >> Player1[1];
            cout << endl;

            // restarts loop if move is invalid
            if(Game.isValidMove(Player1[0], Player1[1])){
                
                // adds a valid move to the board and sends to server
                Game.addX(Player1[0], Player1[1]);
                write(sock, &Player1[0], sizeof(int));
                write(sock, &Player1[1], sizeof(int));
                Game.displayBoard();
                cout << endl;

                // reads move from server, adds to game
                read(sock, &Player2[0], sizeof(int));
                read(sock, &Player2[1], sizeof(int));
                cout << "Server made the move (" << Player2[0] << ", " << Player2[1] << ")" << endl;
                Game.addO(Player2[0], Player2[1]);
                Game.displayBoard();
            }
            else{
                cout << "please enter valid move" << endl;
            }
        }
        
        cout << "game done" << endl;
        break;
    }

    //closes socket
    close(sock);
    return 0;
}