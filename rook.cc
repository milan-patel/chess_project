#include <string>
#include "piece.h"
#include "rook.h"

Rook::Rook(int pos, bool isWhite) : Piece{pos, isWhite}, firstMove{true} {}

bool Rook::canMove(const std::string &start, const std::string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);
	if ((begin % 8 == fin % 8) && begin > fin) { // the Rook is moving up
		begin -= 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin -=8;
		}
		if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		return true;
	}
	else if ((begin % 8 == fin % 8) && begin < fin) {// the Rook is moving down
		begin += 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin +=8;
		}
		if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		return true;
	}
	else if ((begin / 8) == (fin / 8) && (begin > fin)) {// the Rook is moving right
		begin--;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin--;
		}
		if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		return true;	
	}
	else if ((begin / 8) == (fin / 8) && (begin < fin)) {// the Rook is moving left
		begin++;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin++;
		}
		if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		return true;	
	}
	else {
		return false;
	}
}


char Rook::Type() const {
	return isWhite() ? 'R' : 'r';
}

bool Rook::isEmpty() const {
	return false;
}

void Rook::moved() {
	firstMove = false;
}

bool Rook::first() const {
	return firstMove;
}