#include <string>
#include "piece.h"
#include "pawn.h"
#include "board.h"

Pawn::Pawn(int pos, bool isWhite): Piece{pos,isWhite}, firstMove{true} {}

bool Pawn::isEmpty() const{
	return false;
}

bool Pawn::first() const{
	return firstMove;
}

void Pawn::moved(){
	firstMove = false;
}

bool Pawn::canMove(const std::string &start,const std::string &end, const Piece ** &b) const{
	int begin = getPos(start);
	int fin = getPos(end);
	if(posn() != begin){
		return false;
	}
	if(isWhite()){
		if(onLeftEdge()){ // if the pawn is in column A 
			if((posn() - 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is white and end is empty
				return true;
			} else if((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is white, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() - 7) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is white and capturing another piece
				return true;
		} 
	} else if(onRightEdge()){ // if the pawn is in column H
		if((posn() - 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is white and end is empty
				return true;
			} else if((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is white, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() - 9) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is white and capturing another piece
				return true;
		}
	} else // if the pawn if in column B - G
		if((posn() - 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is white and end is empty
				return true;
			} else if((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is white, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() - 9) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is white and capturing another piece
				return true;
		} else if((posn() - 7) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is white and capturing another piece
				return true;
		} 
	} else { // the pawn is black
		if(onLeftEdge()){ // if the pawn is in column A 
			if((posn() + 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is black and end is empty
				return true;
			} else if((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is black, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() + 9) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is black and capturing another piece
				return true;
		} 
	} else if(onRightEdge()){ // if the pawn is in column H
		if((posn() + 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is black and end is empty
				return true;
			} else if((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is black, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() + 7) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is black and capturing another piece
				return true;
		}
	} else // if the pawn if in column B - G
		if((posn() + 8) == fin && b[fin]->isEmpty()){
				// move forward one space if the piece is black and end is empty
				return true;
			} else if((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove){
				// move forward two spaces if the piece is black, the path is clear and 
				// the pawn has not moved yet
				return true;
			} else if((posn() + 9) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is black and capturing another piece
				return true;
		} else if((posn() + 7) == fin && !(b[fin]->isEmpty())){
				// move diagonally if the piece is black and capturing another piece
				return true;
		}
	}
	return false;
}

char Pawn::Type() const{
	if(isWhite()){
		return 'P';
	} else {
		return 'p';
	}
}

