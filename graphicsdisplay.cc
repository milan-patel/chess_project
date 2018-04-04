#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(){
	for (int i = 0; i < gridsize; ++i){
		for(int j = 0; j < gridsize; ++j){
			if((i % 2 == 0 && j % 2 == 0) || (i % 2 ==1 && j % 2 == 1)){
				xw.fillRectangle(i*cellsize, j*cellsize, cellsize,cellsize, colourPositive);
			}
			else{
				xw.fillRectangle(i*cellsize, j*cellsize, cellsize, cellsize, colourNegative);
			}
		}
	}
}

void GraphicsDisplay::clearBoard(){
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
	for(int i = 0; i < gridsize; ++i){
		if(i == 0 || i == 7){
			s = "Rook";
		}
		else if(i == 1|| i == 6){
			s = "Knight";
		}
		else if(i == 2 || i == 5){
			s = "Bishop";
		}
		else if(i == 3){
			s = "Queen";
		}
		else{
			s = "King";
		}
		xw.drawString(i*cellsize+10, yPadding, s, Xwindow::Black);
	}
	// fill in black pawns
	for(int i =0; i< gridsize; ++i){
		xw.drawString(i*cellsize+10, cellsize + yPadding, "Pawn", Xwindow::Black);
	}
	// fill in white pieces
	for(int i = 0; i < gridsize; ++i){
		if(i == 0 || i == 7){
			s = "Rook";
		}
		else if(i == 1|| i == 6){
			s = "Knight";
		}
		else if(i == 2 || i == 5){
			s = "Bishop";
		}
		else if(i == 3){
			s = "Queen";
		}
		else{
			s = "King";
		}
		xw.drawString(i*cellsize+10, cellsize*7 +yPadding, s, Xwindow::White);
	}
// fill in white pawns
	for(int i =0; i< gridsize; ++i){
		xw.drawString(i*cellsize+10, 6*cellsize + yPadding, "Pawn", Xwindow::White);
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
	int col = start[0] - 'a';
	int row = flipRow(start[1] - '1');
	string s = pieceToString(piece);
	int pieceColour = findPieceColour(piece);	
	int rectFillColour = findRectangleColour(col,row);
	xw.fillRectangle(col*cellsize,row*cellsize,cellsize,cellsize,rectFillColour);
	xw.drawString(col*cellsize + 10, row*cellsize + yPadding, s, pieceColour);
	
}

int GraphicsDisplay::flipRow(int row){
	if(row == 0){
		return 7;
	}
	else if(row == 1){
		return 6;
	}
	else if(row == 2){
		return 5;
	}
	else if(row == 3){
		return 4;
	}
	else if(row ==4){
		return 3;
	}
	else if(row == 5){
		return 2;
	}
	else if(row == 6){
		return 1;
	}
	else{
		return 0;
	}
}

void GraphicsDisplay::updateMove(char piece,const string &start, const string &end){
	//gets starting coordinates for cells. string information for piece, and the Colour of the piece on the board.
	int rowStart = flipRow(start[1] - '1');
	int colStart = start[0] - 'a';
	int rowEnd = flipRow(end[1] - '1');
	int colEnd = end[0] - 'a';
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

	xw.drawString(colEnd * cellsize + 10, (rowEnd)*cellsize + yPadding , s, pieceColour);
}
