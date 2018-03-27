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
	Board(int p1, int p2);
	~Board();
	void normalSetup(); // 
	void place(char piece, const std::string &cmd); // only used during setup mode 
	bool validBoard(); // only used during setup mode, checks if board is in a valid
	// setup 
	void move(const std::string &start, const std::string &end);
	bool isCheck(bool isWhite); //
	bool isCheckmate(); 
	bool isStalemate(); 
	std::string sendToDisplay(); 
	Piece *getPiece(const std::string &cmd); // returns a pointer to the piece stored at
	// cmd 
private:
	std::string findKing(bool isWhite);
	bool testMove(const std::string &start, const std::string &end);
};

int getPos(const std:string &cmd); // converts a coordinate in the form of letter-number
// into the corresponding index in Board

std::string getCor(int index); // converts an index from Board into the 
// corresponding coordinate in the form letter-number

