#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(){
xw = newXwindow(windowsize,windowsize);
	//creates the checkerboard pattern
	clearboard();
	//Creates a border around the chess board
	for(int i = 0; i < 5 ++i){
	xw->drawLine(62-i, 58, 62-i, 562);
	xw->drawLine(62,62-i,562,62-i);
	xw->drawLine(558+i, 62, 558+i, 562);
	xw->drawLine(62,558+i, 562, 558+i);
	}
	//Creates coordinates on the edges of the window.
	for(int i = 0; i < gridsize -2; ++i){
 	string s = to_string(flipRow(i));
	xw->drawBigString(xPadding, (i+1)*cellsize +yPadding +xPadding, s, Xwindow::Black);
	s = 'a'+ i;
	xw->drawBigString((i+1)*cellsize+xPadding, 9*cellsize+yPadding+xPadding, s, Xwindow::Black);
	}
}
GraphicsDisplay::~GraphicsDisplay(){
delete xw;
}


void GraphicsDisplay::clearBoard(){
	//Creates the checkerboard pattern, if there's any text in that arae, it will be filled with the pattern - as if the board were cleared.
	for (int i = 0; i < gridsize; ++i){
		for (int j = 0; j< gridsize; ++j){
			if((i % 2 == 0 && j % 2 ==  0) || (i % 2 == 1 && j % 2 == 1)){
				xw.fillRectangle(i*cellsize, j*cellsize, cellsize, cellsize, colourPositive);
			}
			else{
				xw.fillRectangle(i*cellsize, j*cellsize, cellsize, cellsize, colourNegative);
			}
		}
	}
}

void GraphicsDisplay::defaultDisplay(){
	string s; 
	//fill in black pieces at the top
	for(int i = 1; i < gridsize-1; ++i){
		if(i == 1 || i == 8){
			s = "Rook";
		}
		else if(i == 2|| i == 7){
			s = "Knight";
		}
		else if(i == 3 || i == 6){
			s = "Bishop";
		}
		else if(i == 4){
			s = "Queen";
		}
		else{
			s = "King";
		}
		xw.drawString(i*cellsize+xPadding, cellsize + yPadding, s, Xwindow::Black);
	}
	// fill in black pawns
	for(int i =1; i< gridsize-1; ++i){
		xw.drawString(i*cellsize+xPadding, 2*cellsize + yPadding, "Pawn", Xwindow::Black);
	}
	// fill in white pieces
	for(int i = 1; i < gridsize-1; ++i){
		if(i == 1 || i == 8){
			s = "Rook";
		}
		else if(i == 2|| i == 7){
			s = "Knight";
		}
		else if(i == 3 || i == 6){
			s = "Bishop";
		}
		else if(i == 4){
			s = "Queen";
		}
		else{
			s = "King";
		}
		xw.drawString(i*cellsize+xPadding, 8*cellsize +yPadding, s, Xwindow::White);
	}
// fill in white pawns
	for(int i =1; i< gridsize-1; ++i){
		xw.drawString(i*cellsize+xPadding, 7*cellsize + yPadding, "Pawn", Xwindow::White);
	}
}


string pieceToString (char piece){
	if(piece == 'k' || piece == 'K'){//king
		return "King";
	}
	else if(piece == 'b' || piece == 'B'){//bishop
		return "Bishop";
	}
	else if(piece == 'r' || piece == 'R'){//rook
		return "Rook";
	}
	else if(piece == 'n' || piece == 'N'){//knight
		return "Knight";
	}
	else if(piece == 'q' || piece == 'Q'){//Queen
		return "Queen";
	}
	else if(piece == 'p' || piece == 'P'){//Pawn
		return "Pawn";
	}
	return "";

}

int GraphicsDisplay::findPieceColour(char piece){
	return (piece >= 'a' && piece <= 'z')? Xwindow::Black : Xwindow::White;
}

int GraphicsDisplay::findRectangleColour(int col, int row){
	if ((row % 2 == 0  && col % 2 == 0) || (row % 2 == 1 && col % 2 == 1)){
		return colourPositive;
	}
	else{
		return colourNegative;
	}
}

void GraphicsDisplay::setPiece(char piece, const string &start){
	int col = start[0] - 'a' + 1;
	int row = flipRow(start[1] - '1');
	string s = pieceToString(piece);
	int pieceColour = findPieceColour(piece);	
	int rectFillColour = findRectangleColour(col,row);
	xw.fillRectangle(col*cellsize,row*cellsize,cellsize,cellsize,rectFillColour);
	xw.drawString(col*cellsize + xPadding, row*cellsize + yPadding, s, pieceColour);
	
}

int GraphicsDisplay::flipRow(int row){
	if(row == 0){
		return 8;
	}
	else if(row == 1){
		return 7;
	}
	else if(row == 2){
		return 6;
	}
	else if(row == 3){
		return 5;
	}
	else if(row ==4){
		return 4;
	}
	else if(row == 5){
		return 3;
	}
	else if(row == 6){
		return 2;
	}
	else{
		return 1;
	}
}

void GraphicsDisplay::updateMove(char piece,const string &start, const string &end){
	//gets starting coordinates for cells. string information for piece, and the Colour of the piece on the board.
	int rowStart = flipRow(start[1] - '1');
	int colStart = start[0] - 'a' + 1;
	int rowEnd = flipRow(end[1] - '1');
	int colEnd = end[0] - 'a' + 1;
	string s = pieceToString(piece);
	int pieceColour = findPieceColour(piece);
	int rectFillColourStart = findRectangleColour(colStart,rowStart);
	int rectFillColourEnd = findRectangleColour(colEnd,rowEnd);
	//first fill rectangle of start position
	xw.fillRectangle(colStart * cellsize, rowStart * cellsize, cellsize, cellsize, rectFillColourStart);
// void fillRectangle(int x, int y, int width, int height, int colour=Black);
	//Then fills rectangle of end position(this takes out any existing piece string on the space)
	xw.fillRectangle(colEnd * cellsize, rowEnd * cellsize, cellsize, cellsize, rectFillColourEnd);


	//Then Writes in the string name of the piece. 
//        void drawString(int x, int y, std::string msg, int colour = Black);

	xw.drawString(colEnd * cellsize + xPadding, (rowEnd)*cellsize + yPadding , s, pieceColour);
}
