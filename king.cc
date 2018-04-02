#include <string>
#include "piece.h"
#include "king.h"

using namespace std;

King::King(int index, bool white): Piece{index, white}, firstMove{true} {}

King::~King(){}

void King::moved(){
	firstMove = false;
}

bool King::canMove(const string &start, const string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);
	if (!b[fin]->isEmpty() && (isWhite() == b[fin]->isWhite())) {
		//check if space is occupied by same team's piece
		return false;
	}
	else if (isWhite() && first() && 2 == abs(begin-fin)) {
		// white castling
		if (b[61]->isEmpty() && b[62]->isEmpty() && // short, or King-side, castling
			b[63]->Type() == 'R' && fin == 62 &&
			begin == 60) {
				return true;
		}
		else if (b[59]->isEmpty() && b[58]->isEmpty() && // long, or Queen-side, castling
			b[57]->isEmpty() && b[56]->Type() == 'R' 
			&& fin == 58 && begin == 60) {
				return true;
		}
		else {
			return false;
		}
	}
	else if (!isWhite() && first() && 2 == abs(begin-fin)) {
		// black castling
		if (b[5]->isEmpty() && b[6]->isEmpty() && // short, or King-side, castling
			b[7]->Type() == 'R' && fin == 6 &&
			begin == 4) {
				return true;
		}
		else if (b[1]->isEmpty() && b[2]->isEmpty() && // long, or Queen-side, castling
			b[3]->isEmpty() && b[0]->Type() == 'R' 
			&& fin == 2 && begin == 4) {
				return true;
		}
		else {
			return false;
		}
	}
	else if (0 == begin) {
	// if the King is on A8
		return (fin == 1 || fin == 9 || fin == 8) ? true : false;
	}
	else if (7 == begin) { // if the King is on H8
		return (fin == 6 || fin == 14 || fin == 15) ? true : false;
	}
	else if (56 == begin) { // if the King is on H8
		return (fin == 48 || fin == 49 || fin == 57) ? true : false;
	}
	else if (63 == begin) { // if the King is on H1
		return (fin == 62 || fin == 55 || fin == 54) ? true : false;
	}
	else if (onBottomEdge()) {// King is on B1-G1
		return (fin == (begin-8) || fin == (begin-1) || 
				fin == (begin+1) || fin == (begin-7) ||
				fin == (begin-9)) 
				? true : false;
	}
	else if (onTopEdge()) { // King is on B8-G8
		return (fin == (begin+8) || fin == (begin-1) || 
				fin == (begin+1) || fin == (begin+7) ||
				fin == (begin+9))
				? true : false;
	}
	else if (onRightEdge()) { // King is on H2-H7
		return (fin == (begin-1) || fin == (begin-8) || 
				fin == (begin+8) || fin == (begin+7) ||
				fin == (begin-9))
				? true : false;
	}
	else if (onLeftEdge()) {// King is on A2-A7
		return (fin == (begin-1) || fin == (begin-8) || 
				fin == (begin+8) || fin == (begin+7) ||
				fin == (begin-9))
				? true : false; 
	} // King is anywhere else on the board
	return (fin == (begin-1) || fin == (begin+1) || 
			fin == (begin-8) || fin == (begin+8) ||
			fin == (begin-7) || fin == (begin+7) || 
			fin == (begin-9) || fin == (begin+9))
			? true : false;
}

bool King::first() const {
	return firstMove;
}

bool King::isEmpty() const {
	return false;
}

char King::Type() const {
	return isWhite() ? 'K' : 'k';
}
