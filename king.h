#include "piece.h"

class King: public Piece {
	bool firstMove;
public:
	bool isEmpty() override;
};

