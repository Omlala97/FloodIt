#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "textdisplay.h"

static const int MAX_NEIGHBOURS = 4;
static const int NO_PREVIOUS = -1;


class Cell {
	static TextDisplay* display;
	bool inProgress;
	int state;
	int prevState;
	int numNeighbours;
	Cell* neighbours[MAX_NEIGHBOURS];
	int row, col;
	// Add other private members if necessary

	void notifyNeighbours();  	 // Tell all of my neighbours that I have been switched.
	void notifyDisplay();

public:
	Cell();  // Default constructor

	int getState();
	void setState(int change);       	  // Changes state to state
	void setCoords(int row, int col);

	void addNeighbour(Cell* neighbour);
	static void addDisplay(TextDisplay* display);
	void notify(int current, int previous = NO_PREVIOUS); 
};
#endif
