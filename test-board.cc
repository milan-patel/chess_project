#include <string>
#include <iostream>
#include <sstream>
#include "player.h"
#include "scoreboard.h"
#include "piece.h"
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

using namespace std;


Board::Board(int player1, int player2): Board{new Piece*[64]}, isTurnWhite{true},
		inCheck{false}, Scoreboard{Scoreboard()}, p1{new Player()}, p2{new Player()}{
			normalSetup();
			if(player1 > 0){
				delete p1;
				p1 = new Comp(player1);
			} if(player2 > 0){
				delete p2;
				p1 = new Comp(player2);
			}
		}

void Board::normalSetup(){
	// setting up a new black team
	Board[0] = new Rook(0,false); // back row
	Board[1] = new Knight(1,false);
	Board[2] = new Bishop(2,false);
	Board[3] = new Queen(3,false);
	Board[4] = new King(4,false);
	Board[5] = new Bishop(5,false);
	Board[6] = new Knight(6,false);
	Board[7] = new Rook(7, false);
	for(int i=8; i < 16; ++i){
		Board[i] = new Pawn(i,false); // row of pawns
	}
	for(int j=16; j < 48; ++j){
		Board[j] = new Empty(j); // empty space
	}
	// setting up a new white team
	for(int k=48; k < 56; ++k){
		Board[k] = new Pawn(k,true); // row of pawns
	}
	Board[56] = new Rook(56,true); // back row
	Board[57] = new Knight(57,true);
	Board[58] = new Bishop(58,true);
	Board[59] = new Queen(59,true);
	Board[60] = new King(60,true);
	Board[61] = new Bishop(61,true);
	Board[62] = new Knight(62,true);
	Board[63] = new Rook(63,true);
}

void Board::place(char piece, const string &cmd){ 
	// calling this function with piece == 'E' or 'e' will leave that space empty
	int index = getPos(cmd);
	bool isWhite = ('A' < piece) && ('Z' > piece);
	if (!isWhite){
		piece = piece - 'a' + 'A';
	}
	if(piece = 'P'){
		delete Board[index];
		Board[index] = new Pawn(index, isWhite);
	} else if(piece = 'R'){
		delete Board[index];
		Board[index] = new Rook(index,isWhite);
	} else if(piece = 'Q'){
		delete Board[index];
		Board[index] = new Queen(index,isWhite);
	} else if(piece = 'B'){
		delete Board[index];
		Board[index] = new Bishop(index,isWhite);
	} else if(piece = 'N'){
		delete Board[index];
		Board[index] = new Knight(index,isWhite);
	} else if(piece = 'K'){
		delete Board[index];
		Board[index] = new King(index,isWhite);
	} else if(piece = 'E'){
		delete Board[index];
		Board[index] = new Empty(index);
	}
}



Board::~Board(){
	for(int i =0; i < 64;++i){ // deletes all piece pointers in the Board object
		delete Board[i];
	}
	delete [] Board;
	delete p1;
	delete p2;
}

bool Board::testMove(const string &start, const string &end){
	// tests out the move, mutates the board and assesses if the player is left in 
	// check. If the move is valid, the function returns true, else it returns
	// false. In either case, the board is mutated back to its original state
	Piece *p = getPiece(start);
	Piece *temp = getPiece(end);
	if(p->canMove(start, end, getBoard())){
		Board[getPos(end)] = p;
		Board[getPos(start)] = new Empty(getPos(start));
		if(isCheck(isTurnWhite)){
			return false;
		}
		delete Board[getPos(start)];
		Board[getPos(start)] = p;
		Board[getPos(end)] = temp;
		return true;
	}
	else {
		return false;
	}
}


void Board::move(const string &start, const string &end){
	// makes the move, if valid, and checks if the opposing player is now in check
	// changes whose turn it is 
	Piece *p = getPiece(start);
	if(testMove(start,end)){
		delete Board[getPos(end)];
		Board[getPos(end)] = p;
		Board[getPos(start)] = new Empty(getPos(start));
		isTurnWhite = (! isTurnWhite);
		inCheck = isCheck(isTurnWhite);
		if (isCheckmate()){
			// do something in case Checkmate is reached
		} else if(isStalemate()){
			// do something in case Stalemate is reached
		}
	}
}

bool Board::isCheck(bool isWhite){
	string king = findKing(isWhite);
	bool flag = false; // flag will change to true if an opposing piece can move
	// to the space of the King 
	for(int i=0; i<64; ++i){
		if(Board[i]->canMove(getCor(i),King, getBoard())){
			flag = true;
		}
	}
	return flag;
}

bool Board::isCheckmate(){
	return false;
}

bool Board::isStalemate(){
	return false;
}

string Board::sendToDisplay(){
	ostringstream oss;
	char tmp = '0';
	int j = 0;
	int end = 8;
	for(int i = 8; i > 0; --i){
		oss << (tmp + i) << " "; 
		for(;j<end; ++j){
			oss << (Board[j]->Type());
		}
		end += 8;
		oss << "\n"
	}
	return oss.str();
}


string Board::findKing(bool isWhite){
	char king = 'k';
	if(isWhite){
		king = 'K';
	}
	for(int i=0; i<64;++i){
		if(king == (Board[i])->Type()){
			return getCor(i); 
		}
	}
	return "";
}

const Piece ** &Board::getBoard(){
	return Board;
}


Piece *Board::getPiece(const string &cmd){
	// retrieves the piece stored at cmd
	int index = getPos(cmd);
	return Board[index];
}

int getPos(const string &cmd){
	int col = (cmd[0] - 'a');
	int row = (cmd[1] - '1');
	row = 7 - row;
	int pos = 8*row+col; 
	return pos;
}

string getCor(int index){
	// inverse of getPos
	string s;
	ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}