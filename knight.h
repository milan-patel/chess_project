#include "piece.h"

class Knight: public Piece {
public:
	bool isEmpty() override;
	bool canMove(std::string start, std::string end) override;
};
