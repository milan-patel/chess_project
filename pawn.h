#include "piece.h"

class Pawn: public Piece {
	bool firstMove;
public: 
	Pawn(int pos, bool isWhite);
	bool canMove(const std::string &start,const std::string &end, const Piece ** &b) override;
	bool isEmpty() override;
	char Type() override;
};
