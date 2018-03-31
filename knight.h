#ifndef ___KNIGHT___
#define ___KNIGHT___

#include <string>
#include "piece.h"

class Knight: public Piece {
public:
	Knight(int pos, bool isWhite);
	bool isEmpty() const override;
	bool canMove(const std::string &start, const std::string &end, const Piece ** &b) const override;
	char Type() const override;
};

#endif
