#include <string>
#include "board.h"
#include "knight.h"

Knight::Knight(int pos, bool isWhite): Piece(pos, isWhite) {}

bool Knight::isEmpty() const{
	return false;
}

bool Knight::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	int begin_x = getPos(start) % 8;
	int begin_y = getPos(start) / 8;
	int fin_x = getPos(end) % 8;
	int fin_y = getPos(end) / 8;
	if (abs(begin_x - fin_x) == 1 && abs(begin_y - fin_y) == 2) {
		return true;
	}
	else if (abs(begin_x - fin_x) == 2 && abs(begin_y - fin_y) == 1) {
		return true;
	}
	else {
		return false;
	}
}

char Knight::Type() const {
	return isWhite() ? 'N' : 'n';
}
