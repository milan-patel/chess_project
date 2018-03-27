#include "piece.h"
#include "pawn.h"

Pawn::Pawn(int pos, bool isWhite): Piece{pos,isWhite}, firstMove{true} {}

bool Pawn::isEmpty(){
	return false;
}

char Pawn::Type(){
	if(white){
		return 'P';
	} else {
		return 'p';
	}
}
