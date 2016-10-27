#include <iostream>
#include "textdisplay.h"


/*****************TextDisplay::TextDisplay()*****************
Purpose: initialize a matrix of char as a constructor
********************************************************/
char **theDisplay = NULL;								// first initialize as NULL
TextDisplay::TextDisplay(int n):gridSize(n) {
	theDisplay = new char *[n];							// double for loop for creating
	for(int i = 0; i < n; i++){
		theDisplay[i] = new char[n];
		for(int j = 0; j < n; j++){
			theDisplay[i][j] = '0';						// initialize with char '0'
		}
	} 

	for(int i = 0; i < 5; i++){							// initialize colour with 0
		colours[i] = 0;
	}
}


/*****************TextDisplay::~TextDisplay()*****************
Purpose: destructor
********************************************************/
TextDisplay::~TextDisplay(){
	for(unsigned int i = 0; i < gridSize; i++){			// delete each line of theDisplay
		delete[] theDisplay[i];
	}
	delete[] theDisplay;
}


/*****************TextDisplay::notify(r, c, ch)*****************
Purpose: notify the display of each cell that it changes state
********************************************************/
void TextDisplay::notify(int r, int c, char ch){
	theDisplay[r][c] = ch;
}


/*****************TextDisplay::filled()*****************
Purpose: check if all Cell in a grid have the same state
		 return true if yes, false otherwise.
********************************************************/
bool TextDisplay::filled(){
	char state = theDisplay[0][0];						// store the state of origin
	for(unsigned int i = 0; i < gridSize; i++){
		for(unsigned int j = 0; j < gridSize; j++){
			if(theDisplay[i][j] != state) return false;
		}
	}
	return true;
}


/*****************TextDisplay::print()*****************
Purpose: print the grid out on the screen
********************************************************/
void TextDisplay::print(){
	for(unsigned int i = 0; i < gridSize; i++){
		for(unsigned int j = 0; j < gridSize; j++){
			std::cout << theDisplay[i][j];
		}
		std::cout << std::endl;							// start a new line
	}
}
