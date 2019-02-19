/*
Diego Andrade
CS371 Fall 2018
Server side C++ program based on the GeeksForGeeks article:
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
#include "tictactoe.h"


#define PORT 8080       // port being used
#define RAND_HELPER 3   // used to limit cardinality of random numbers to 0, 1, or 2

using namespace std;

// helper function to create random moves
int randomNumGenerator(){
    return rand() % RAND_HELPER;
}

int main(int argc, char const *argv[]) 
{ 
    int userx, usery, x, y;


    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
       
    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_fd < 0) { 
        cout << "Could not create socket" << endl;
        return -1;
    } 

    // initiallized address to zero   
    bzero((char *) &address, sizeof(address));

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address)) < (0)) { 
        cout << "Bind failed" << endl;
    } 

    // This part loops so Server can continue to run after the game ends
    while (1){

        // Listening on socket for contact from Client
        cout << "listening..." << endl;
        if (listen(server_fd, 3) < 0) { 
            cout << "Listen failed" << endl;
        } 

        // Blocks process until Client connects
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){ 
            cout << "accept failed" << endl;
        } 
        cout << "connected" << endl;

        // Creates game object
        TicTacToe Game;
        Game.game();

        // seed timer
        srand(time(NULL));

        // Begin loop for the game
        while(!Game.isGameOver()){
            
            // reads the move from the user and add to the game object
            read(new_socket, &userx, sizeof(userx));
            read(new_socket, &usery, sizeof(usery));
            Game.addX(userx, usery);
            cout << "Client made the move: (" << userx << ", " << usery << ")\n";
            Game.displayBoard();

            // makes sure user didn't have a winning move
            if(!Game.isGameOver()){

                // generates random moves until one is valid, adds to game object
                do{
                    x = randomNumGenerator();
                    y = randomNumGenerator();
                } while(!Game.isValidMove(x, y));
                Game.addO(x, y);
                cout << "Server made the move: (" << x << ", " << y << ")\n";
                Game.displayBoard();

                // sends randomly generated move to client
                write(new_socket, &x, sizeof(x));
                write(new_socket, &y, sizeof(y));
            }
        }
        
        //closes connection with client
        close(new_socket);
    }
    
    return 0; 
} 