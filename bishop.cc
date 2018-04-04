#include "board.h"
#include "bishop.h"
#include <string>

// 2 Parameter ctor
Bishop::Bishop(int pos, bool isWhite) : Piece(pos, isWhite) {}

// returns if the Piece is empty or not
bool Bishop::isEmpty() const{
	return false;
}

// determines whether a Bishop can move to the end coordinates
bool Bishop::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);

	// moving down on the right diagonal
	if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin) {
		while (true) {
			begin += 7;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin += 7;
			}
		}
	}

	// moving up on the right diagonal
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin) {
		while (true) {
			begin -= 7;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if(!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin -= 7;
			}
		} 
	}

	// moving down on the left diagonal
	else if (begin % 9 == fin % 9 && begin < fin) {
		while (true) {
			begin += 9;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin += 9;
			}
		} 
	}

	// moving up on the left diagonal
	else if (begin % 9 == fin % 9 && begin > fin) {
		while (true) {
			begin -= 9;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin -= 9;
			}
		} 
	}
	else {
		return false;
	}
}

// returns uppercase or lowercase b, depending on which Player's turn it is
char Bishop::Type() const {
	return isWhite() ? 'B' : 'b';
}