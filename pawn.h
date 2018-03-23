#include "piece.h"

class Pawn: public Piece {
	bool firstMove;
public: 
	bool isEmpty() override;
};
