This contains two files, one for the Server, one for the Client.
To compile the Server:
	g++ -o Server server.cpp tictactoe.cpp
To run the Server:
	./Server
To compile the Client:
	g++ -o Client client.cpp tictactoe.cpp
To run the Client:
	./Client
To change the port being used:
	in both the client.cpp and server.cpp change the PORT variable
To change the IP being used:
	in the client.cpp change the IP variable 
To enter a move:
	two integers (0, 1, or 2) with a space between them
Run the server before the client, good luck
