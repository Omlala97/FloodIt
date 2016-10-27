#include "game.h"
#include "cell.h"
#include "textdisplay.h"
#include "PRNG.h"
#include <iostream>

extern PRNG prng;


/*********************Game::Game()*****************
Purpose: initialize a grid(matrix of Cell) as a constructor
********************************************************/
Game::Game(int size, int turns): gridSize(size) {
	display = new TextDisplay(size);					// create a new TextDisplay
	grid = new Cell *[size];							// create a new grid matrix
	for(int i = 0; i < size; i++){						// using double for loop
		grid[i] = new Cell[size];
		for(int j = 0; j < size; j++){
			grid[i][j].addDisplay(display);				// direct textDisplay of each Cell to one same textDisplay
			grid[i][j].setCoords(i, j);					// set coordinates of each Cell
			grid[i][j].setState(prng(4));	// 0-4			// set initialized random state of each Cell
			//grid[i][j].notify(grid[i][j].getState());		
		}
	}

	for(int i = 0; i < size; i++){						// use double for loop again to give neighbour cell to each Cell
		for(int j = 0; j < size; j++){
			if(i != size-1){
				grid[i][j].addNeighbour(&grid[i+1][j]);
			}
			if(i-1>= 0){
				grid[i][j].addNeighbour(&grid[i-1][j]);
			}
			if(j != size-1){
				grid[i][j].addNeighbour(&grid[i][j+1]);
			}
			if(j != 0){
				grid[i][j].addNeighbour(&grid[i][j-1]);
			}
		}
	}
	this->turns = turns;								// give input turns to turns
}


/*********************Game::~Game()*****************
Purpose: destructor
********************************************************/
Game::~Game(){
	for(int i = 0; i < gridSize; i++){					// use for loop to delete each line of grid
		delete[] grid[i];
	}
	delete[] grid;										// delete grid
//	delete display;										// delete textDisplay
}


/*********************Game::getTurns()*****************
Purpose: return the current remaining turns
********************************************************/
int Game::getTurns(){
	return turns;
}


/*********************Game::isWon()*****************
Purpose: call TextDisplay::filled() to get win/lose state
********************************************************/
bool Game::isWon(){
	return display->filled();
}


/*********************Game::change()*****************
Purpose: each time we change the state of origin, Game notify
		 this origin cell, and also notify its neighbours and textdisplay.
********************************************************/
void Game::change(int state){
	grid[0][0].notify(state);	// only notify origin
	turns--;
}


/*********************Game::print()*****************
Purpose: call TextDisplay::print() to print on screen and give 
		 corresponding move/moves left
********************************************************/
void Game::print(){
	if(turns == 1){										// difference between 1 and other moves left
		display->print();
		std::cout << turns << " move left" << std::endl;
	}else{
		display->print();
		std::cout << turns << " moves left" << std::endl;
	}
}
