#ifndef ___BOARD___
#define ___BOARD___

#include <string>
#include "scoreboard.h"
#include "player.h"

class Piece;


// Board objects 
class Board {
	Piece **board; // an array of 64 Piece pointers
	bool isTurnWhite;
	bool inCheck;
	Scoreboard *s;
	Player *p1;
	Player *p2;

public:
	Board(int p1, int p2);
	~Board();
	void clearBoard(); // clears all the current pieces from the board 
	void normalSetup(); // default configuration for a game
	void place(char piece, const std::string &cmd); // only used during setup mode 
	bool validBoard() const; // only used during setup mode, checks if board is in a valid
	// setup
	void setTurn(std::string colour); //sets turn to colour
	void move(const std::string &start, const std::string &end);
	bool isCheck(bool isWhite); //
	bool isCheckmate() const; 
	bool isStalemate() const; 
	std::string sendToDisplay() const; 
	Piece *getPiece(const std::string &cmd) const; // returns a pointer to the piece stored at
	// cmd
	Piece ** getBoard(); // provides a copy of the board
	// for other classes to reference
private:
	std::string findKing(bool isWhite) const;
	bool testMove(const std::string &start, const std::string &end);
};


#endif
