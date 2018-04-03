#include "window.h"
#include <string>
#ifndef _GRP_H
#define _GRP_H
class GraphicsDisplay{
	int windowsize = 500;
	Xwindow xw;
	int colourPositive = Xwindow::Brown;
	int colourNegative = Xwindow::Orange;
	int flipRow(int row);
	public:
	//ctor
	GraphicsDisplay();
	//constants
	const int gridsize = 8;
	const int cellsize = windowsize/gridsize; 
	const int yPadding = cellsize/2;
	//methods
	int findRectangleColour(int col, int row);
	int findPieceColour(char piece);
	void setPiece(char piece, const std::string &start);
	void updateMove(char piece,const std::string &start,const std::string &end);
	void clearBoard();
	void defaultDisplay();
};
#endif
