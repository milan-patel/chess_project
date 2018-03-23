#include "piece.h"

class Empty: public Piece {
public:
	bool isEmpty() override;
};