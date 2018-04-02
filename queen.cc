#include <string>
#include "piece.h"
#include "queen.h"

Queen::Queen(int pos, bool isWhite): Piece(pos,isWhite){}

bool Queen::canMove(const std::string &start, const std::string &end, Piece ** b) const{
	int begin = getPos(start);
	int fin = getPos(end);
	if ((begin % 8 == fin % 8) && begin > fin) { // the Queen is moving up
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
	else if ((begin % 8 == fin % 8) && begin < fin) {// the Queen is moving down
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
	else if ((begin / 8) == (fin / 8) && (begin > fin)) {// the Queen is moving right
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
	else if ((begin / 8) == (fin / 8) && (begin < fin)) {// the Queen is moving left
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
	else if (begin % 9 == fin % 9 && begin < fin) { // the Queen is moving diagonally
		while (true) {
			if (begin == fin && !(isWhite() == b[begin]->isWhite())) {
				return true;
			}
			else if(begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if(!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin += 9;
			}
		}
	}
	else if (begin % 9 == fin % 9 && begin > fin) {
		while (true) {
			if (begin == fin && !(isWhite() == b[begin]->isWhite())) {
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
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin) {
		while (true) {
			if (begin == fin && !(isWhite() == b[begin]->isWhite())) {
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
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin) {
		while (true) {
			if (begin == fin && !(isWhite() == b[begin]->isWhite())) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else {
				begin -= 7;
			}
		}
	}
	else {
		return false;
	}
}

char Queen::Type() const {
	return isWhite() ? 'Q' : 'q';
}

bool Queen::isEmpty() const {
	return false;
}
