#include <iostream>
#include "cell.h"
#include "textdisplay.h"


/*********************Cell::Cell()*****************
Purpose: initialize a Cell as constructor, no allocation for any field,
		 hence, no destructor
********************************************************/
TextDisplay *Cell::display = NULL;							// initialize the display of each Cell as NULL
Cell::Cell():inProgress(false), state(0), prevState(-1), numNeighbours(0), row(), col(){
	//display = display;
	for(int i = 0; i < MAX_NEIGHBOURS; i++){
		neighbours[i] = NULL;								// initialize each neighbour cell as NULL
	}
}


/*********************Cell::getState()*****************
Purpose: return the current state of this Cell
********************************************************/
int Cell::getState(){
	return state;
}


/*********************Cell::setState()*****************
Purpose: change the state of this Cell to new state, also notify 
		 display of this Cell to change its state on screen
********************************************************/
void Cell::setState(int change){
	prevState = state;
	state = change;
	notifyDisplay();
}


/*********************Cell::setCoords()*****************
Purpose: set coordinates of this Cell
********************************************************/
void Cell::setCoords(int row, int col){
	Cell::row = row;
	Cell::col = col;
}


/*********************Cell::addNeighbour()*****************
Purpose: addNeighbour to current Cell's neighbours list
********************************************************/
void Cell::addNeighbour(Cell* neighbour){
	neighbours[numNeighbours] = neighbour;
	numNeighbours++;
}


/*********************Cell::addDisplay()*****************
Purpose: direct this Cell's display to a same TextDisplay for all Cells
********************************************************/
void Cell::addDisplay(TextDisplay* display){
	Cell::display = display;
}


/*********************Cell::notifyNeighbours()*****************
Purpose: notify all neighbours of current Cell of changing state
********************************************************/
void Cell::notifyNeighbours(){
	//std::cout << "row, col: " << row << " " << col << " state: " << state << " prev: " << prevState << std::endl;
	for(int i = 0; i < numNeighbours; i++){
 		neighbours[i]->notify(state, prevState);
	}
	//notifyDisplay();
}


/*********************Cell::notifyDisplay()*****************
Purpose: tell TextDisplay that you are changing state
********************************************************/
void Cell::notifyDisplay(){
	display->notify(row, col, state + 48);
}


/***************Cell::notify(current, previous)*****************
Purpose: A. if the origin is changing state, setState, and then 
			notify all its neighbours
		 B. if any cells other than origin is changing state, 
		 	check if it satisfies the condition to change state, 
		 	and then notify all its neighbours
********************************************************/
void Cell::notify(int current, int previous){
	if(previous == NO_PREVIOUS){
		setState(current);
		notifyNeighbours();
	}
	else{
		if(state != current && state == previous){			// condition check
			setState(current);
			notifyNeighbours();	
		}
	}
} 
