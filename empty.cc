#include "empty.h"
#include "piece.h"
#include <string>


static int isWhiteSquare(int pos){
	pos = pos % 16;
	if(pos < 8 && (pos % 2) == 0){
		return true;
	} else if(pos > 7 && (pos % 2) == 1){
		return true;
	}
	return false;
}

Empty::Empty(int index): Piece{index, true}{}

Empty::~Empty(){};

bool Empty::canMove(const std::string &start, const std::string &end, const Piece ** &b) const{
	return false;
}

bool Empty::isEmpty() const{ return true; }

char Empty::Type() const{
	if (isWhiteSquare(posn())){
		return ' ';
	} else {
		return '_';
	}
}

