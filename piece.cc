#include "piece.h"

Piece::Piece(int pos, bool white): pos{pos}, white{white}{}

bool Piece::isWhite(){
	return white;
}

void Piece::changePos(int posn){
	pos = posn;
}

int Piece::posn(){
	return pos;
}

Piece::~Piece(){}

bool onRightEdge(){
	if(7 ==(posn() % 8)){
		return true;
	} 
	return false;
}

bool onLeftEdge(){
	if(0 ==(posn() % 8)){
		return true;
	} 
	return false;
}

bool onTopEdge(){
	if(0 <= posn() && posn() <= 7){
		return true;
	} 
	return false;
}

bool onBottomEdge(){
	if(56 <= posn() && posn() <= 63){
		return true;
	} 
	return false;
}

