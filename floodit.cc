#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include "cell.h"
#include "game.h"
#include "PRNG.h"
#include "textdisplay.h"

using namespace std;

PRNG prng;
extern PRNG prng;


// usage message
void usage(char *argv[]) {
	cerr << "Usage: " << argv[0];
	cerr << " [ -size N (width and height of game ) >= 2 ] ";
	cerr << "| [ -moves M (number of moves until game is over) >= 1) ] ";
	cerr << "| [ -seed S (seed for random-number generator (1..INT_MAX)) ]" << endl;
	exit(EXIT_FAILURE);
}

/*****************main(argc, argv[])*****************
Purpose: read in parameters to initialize a gric, also
		 read in instructions from player during game,
		 after game terminates, give appropriate game info.
********************************************************/
int main(int argc, char* argv[]){
	int m = 0, n = 0, val = 0;						// declare parameters
	if(argc%2 == 1){								// valid when argc is odd number
		int i = 1;
		while (i < argc) {							// loop till the last command-line argument
			int value = 0;							
			string arg = argv[i];					
			stringstream iss(argv[i+1]);			// initialize a stringstream with argument after string arg

			//int argu = *argv[i + 1] - '0';					
			if (arg == "-size") {					// condition check
				if(iss >> value){					// seperate each word into value
					n = value;
					if (n < 2) {						// valid range check
						usage(argv);
					}
				}else{								// if read-in is not an int, show usage msg
					usage(argv);
				}
			}
			else if(arg == "-moves") {
				if(iss >> value){
					m = value;		
					if (m < 1) {						// range check
						usage(argv);
					}
				}else{
					usage(argv);
				}
			}
			else if(arg == "-seed"){
				if(iss >> value){
					val = value;
					if (val < 1) {						// range check
						usage(argv);
					}
				}else{
					usage(argv);
				}
			}
			else {									// valid type check
				usage(argv);
			}
			i += 2;									// loop every two arguments
		}
	}
	else {											// when argument no. is even
		usage(argv);
	}

	if (n == 0) {								// when no value for n, m, val is specified
		n = 10;									// give default value to them
	}
	if (m == 0) {
		m = 20;
	}
	if (val == 0) {
		val = ::getpid();
	}


	prng.seed(val);								// generate random number with prng
	Game *game = new Game(n, m);				// allocate on heap for a Game
	game->print();								// print the first initialized grid
	for(int i = 0; i < m; i++){					// loop till the last round

		if(cin.eof()) break;					// when we reach the end of input

		string input;
		int change;

		if(cin >> input){
			if(cin.eof()) break;				// read in to input
			stringstream ss(input);				// initialize stringsteam ss with input
			if(ss >> change){					// read in each int instruction
				game->change(change);			// call Game::change(change)
				game->print();					// print the grid after changing once
				if(game->isWon()){				// check if the player has won
					cout << "Won" << endl;
					delete game;				// delete allocated memory
					return 0;
				}
			}else{
				cout << "Invalid move" << endl;	// if change is not an int
			}
		}

		if(i == m-1){							// if we already looped till the last round
			if(!game->isWon()){					// check player win/lose
				cout << "Lost" << endl;
			}
		}
	}
	//cout << "Lost" << endl;
	delete game;								// delete allocated memory
	return 0;									// int main()
}
