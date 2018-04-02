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
	bool gameOver;
	Scoreboard *s;
	Player *p1;
	Player *p2;

public:
	Board(int p1, int p2);
	~Board();
	void endGame(std::string cmd); // cmd is "black", "white", "white resigns",
	// "black resigns" or "draw";
	void clearBoard(); // clears all the current pieces from the board 
	void normalSetup(); // default configuration for a game
	void place(char piece, const std::string &cmd); // only used during setup mode 
	bool validBoard() const; // only used during setup mode, checks if board is in a valid
	// setup
	void newPlayers(int player1, int player2); // generate two new players
	void setTurn(std::string colour); //sets turn to colour
	bool move(const std::string &start, const std::string &end);
	bool isCheck(bool isWhite); //
	bool isCheckmate() const; 
	bool isStalemate() const; 
	std::string sendToDisplay() const; 
	Piece *getPiece(const std::string &cmd) const; // returns a pointer to the piece stored at
	// cmd
	Piece ** getBoard(); // provides a copy of the board
	// for other classes to reference
	bool canPawnPromote();
	bool getTurnStatus() const;
	void printScore() const;
	bool isGameOver(); 
	void gameOn(); // sets gameOver flag to false

private:
	std::string findKing(bool isWhite) const;
	bool testMove(const std::string &start, const std::string &end);
};


#endif
