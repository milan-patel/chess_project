#include "piece.h"

class Rook: public Piece {
	bool firstMove;
public:
	bool isEmpty() override;
};
