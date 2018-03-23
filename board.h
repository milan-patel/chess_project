#include <map>
#include "scoreboard.h"
#include "player.h"


// Board objects 
class Board {
	Piece **Board; // an array of 64 Piece pointers
	bool isTurnWhite;
	bool inCheck;
	Scoreboard s;
	Player *p1;
	Player *p2;

public:
	void place(char piece, std::string cmd); // only used during setup mode 
	// 
	void move(std::string start, std::string end); 

	bool isCheck(bool isWhite); // returns whether 
	bool isCheckmate();
	bool isStalemate();
	std::string sendToDisplay();
};

int getPos(std:string cmd); // converts a coordinate in the form of a1 into the 
// corresponding place 