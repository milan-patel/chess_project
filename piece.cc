#include "piece.h"

Piece::Piece(int pos, bool white): pos{pos}, white{white}{}

bool Piece::isWhite(){
	return white;
}

Board *Piece::getBoard(){
	return b;
}

void Piece::changePos(int posn){
	pos = posn;
}

Piece::~Piece(){}


