#include <iostream>
#include <sstream>
#include "board.h"
#include "player.h"
#include "computer.h"
#include "scoreboard.h"
#include "piece.h"
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <string>

using namespace std;


Board::Board(int player1, int player2): board{new Piece*[64]}, isTurnWhite{true},
		inCheck{false}, gameOver{true}, s{new Scoreboard()}, p1{new Player(true)}, p2{new Player(false)}{
			clearBoard();
			if(player1 > 0){
				delete p1;
				p1 = new Comp(player1, true);
			} if(player2 > 0){
				delete p2;
				p1 = new Comp(player2, false);
			}
		}

void Board::clearBoard(){
	for(int i=0; i<64; ++i){
		delete board[i];
		board[i] = new Empty(i);
	}
}

void Board::normalSetup(){
	setTurn("white");
	gameOn();
	for(int i=0; i<64; ++i){
		delete board[i];
	}
	// setting up a new black team
	board[0] = new Rook(0,false); // back row
	board[1] = new Knight(1,false);
	board[2] = new Bishop(2,false);
	board[3] = new Queen(3,false);
	board[4] = new King(4,false);
	board[5] = new Bishop(5,false);
	board[6] = new Knight(6,false);
	board[7] = new Rook(7, false);
	for(int i=8; i < 16; ++i){
		board[i] = new Pawn(i,false); // row of pawns
	}
	for(int j=16; j < 48; ++j){
		board[j] = new Empty(j); // empty space
	}
	// setting up a new white team
	for(int k=48; k < 56; ++k){
		board[k] = new Pawn(k,true); // row of pawns
	}
	board[56] = new Rook(56,true); // back row
	board[57] = new Knight(57,true);
	board[58] = new Bishop(58,true);
	board[59] = new Queen(59,true);
	board[60] = new King(60,true);
	board[61] = new Bishop(61,true);
	board[62] = new Knight(62,true);
	board[63] = new Rook(63,true);
}

void Board::newPlayers(int player1, int player2){
	delete p1;
	delete p2;
	if(player1 == 0){
		p1 = new Player(true);
	} else if(player1 > 0){
		p1 = new Comp(player1, true);
	}
	if(player2 == 0){
		p2 = new Player(false);
	} else if(player2 > 0){
		p2 = new Comp(player2, true);
	}
}

void Board::place(char piece, const string &cmd){ 
	// calling this function with piece == 'E' or 'e' will leave that space empty
	int index = getPos(cmd);
	bool isWhite = ('A' < piece) && ('Z' > piece);
	if (!isWhite){
		piece = piece - 'a' + 'A';
	}
	if(piece == 'P'){
		delete board[index];
		board[index] = new Pawn(index, isWhite);
	} else if(piece == 'R'){
		delete board[index];
		board[index] = new Rook(index,isWhite);
	} else if(piece == 'Q'){
		delete board[index];
		board[index] = new Queen(index,isWhite);
	} else if(piece == 'B'){
		delete board[index];
		board[index] = new Bishop(index,isWhite);
	} else if(piece == 'N'){
		delete board[index];
		board[index] = new Knight(index,isWhite);
	} else if(piece == 'K'){
		delete board[index];
		board[index] = new King(index,isWhite);
	} else if(piece == 'E'){
		delete board[index];
		board[index] = new Empty(index);
	}
}



Board::~Board(){
	for(int i =0; i < 64;++i){ // deletes all piece pointers in the Board object
		delete board[i];
	}
	delete [] board;
	delete s;
	delete p1;
	delete p2;
}

bool Board::testMove(const string &start, const string &end){
	// tests out the move, mutates the board and assesses if the player is left in 
	// check. If the move is valid, the function returns true, else it returns
	// false. In either case, the board is mutated back to its original state
	Piece *p = getPiece(start);
	Piece *temp = getPiece(end);
	if(p->isWhite() != getTurnStatus()){
		return false;
	}
	if(p->canMove(start, end, getBoard())){
		board[getPos(end)] = p;
		board[getPos(start)] = new Empty(getPos(start));
		if(isCheck(isTurnWhite)){
			delete board[getPos(start)];
			board[getPos(start)] = p;
			board[getPos(end)] = temp;
			return false;
		}
		delete board[getPos(start)];
		board[getPos(start)] = p;
		board[getPos(end)] = temp;
		return true;
	}
	else {
		return false;
	}
}

bool Board::canPawnPromote(){
	for(int i = 0; i<8; ++i){
		if('P' == board[i]->Type()){
			return true;
		}
	}
	for(int j =56; j<64; ++j){
		if('p' == board[j]->Type()){
			return true;
		}
	}
	return false;
}

bool Board::getTurnStatus() const {
	return isTurnWhite;
}

void Board::move(const string &start, const string &end){
	// makes the move, if valid, and checks if the opposing player is now in check
	// changes whose turn it is 
	Piece *p = getPiece(start);
	if(testMove(start,end)){
		delete board[getPos(end)];
		board[getPos(end)] = p;
		p->changePos(getPos(end));
		p->moved();
		board[getPos(start)] = new Empty(getPos(start));
		isTurnWhite = (! isTurnWhite);
		inCheck = isCheck(isTurnWhite);
		if(isCheck(true)){
			s->check(true);
		} else if(isCheck(false)){
			s->check(false);
		} else {

		}
		if (inCheck && isCheckmate()){
			string winner;
			if(isTurnWhite){
				winner = "black";
			} else { 
				winner = "white";
			}
			endGame(winner);
			return; 
		} else if(isStalemate()){
			endGame("draw");
			return;
		}
	}
}

bool Board::isCheck(bool isWhite){
	string king = findKing(isWhite);
	bool flag = false; // flag will change to true if an opposing piece can move
	// to the space of the King 
	for(int i=0; i<64; ++i){
		if(board[i]->canMove(getCor(i),king, getBoard())){
			flag = true;
		}
	}
	return flag;
}

void Board::endGame(string cmd){
	gameOver = true;
	if(cmd == "black"){
		s->win(false);
	} else if (cmd == "white"){
		s->win(true);
	} else if (cmd == "white resigns"){
		s->resign(true);
	} else if (cmd == "black resigns"){
		s->resign(false);
	} else if (cmd == "draw"){
		s->tie();
	} else {
		return;
	}
	normalSetup();
}

bool Board::isGameOver(){
	return gameOver;
}

void Board::gameOn(){
	gameOver = false;
}

bool Board::validBoard() const{
	int numBlackKings = 0;
	int numWhiteKings = 0;
	for(int i=0; i<8;++i){
		if(board[i]->Type() =='P' || board[i]->Type() =='p'){
			return false;
		} else if(board[i]->Type() == 'K'){
			++numWhiteKings;
		} else if(board[i]->Type() == 'k'){
			++numBlackKings;
		}
	}
	for(int j=8; j<56;++j){
		if(board[j]->Type() == 'K'){
			++numWhiteKings;
		} else if(board[j]->Type() == 'k'){
			++numBlackKings;
		}
	}
	for(int k=56; k<64;++k){
		if(board[k]->Type() =='P' || board[k]->Type() =='p'){
			return false;
		} else if(board[k]->Type() == 'K'){
			++numWhiteKings;
		} else if(board[k]->Type() == 'k'){
			++numBlackKings;
		}
	}
	if ( numBlackKings != 1 || numWhiteKings != 1){
		return false;
	} else {
		return true;
	}
}

bool Board::isCheckmate() {
	int king = getPos(findKing(isTurnWhite));
	if(isTurnWhite){
		for(int i=0;i<64; ++i){
			char type = board[i]->Type();
			if(isTurnWhite == board[i]->isWhite() && 'P' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))){
				return false;
			} else if(isTurnWhite == board[i]->isWhite()){
				for(int j=0; j<64;++j){
					if(j==i){
						continue;
					} else if(testMove(getCor(i), getCor(j))){
						return false;
					}
				}
			} else{
				continue;
			}
		}
	} else{
		for(int i=0;i<64; ++i){
			char type = board[i]->Type();
			if(isTurnWhite == board[i]->isWhite() && 'p' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))){
				return false;
			} else if(isTurnWhite == board[i]->isWhite()){
				for(int j=0; j<64;++j){
					if(j==i){
						continue;
					} else if(testMove(getCor(i), getCor(j))){
						return false;
					}
				}
			} else {
				continue;
			}
		}
	}
	return true;
}

bool Board::isStalemate(){
	for(int i=0;i<64; ++i){
			char type = board[i]->Type();
			if(isTurnWhite == board[i]->isWhite() && 'P' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))){
				return false;
			} else if(isTurnWhite == board[i]->isWhite()){
				for(int j=0; j<64;++j){
					if(j==i){
						continue;
					} else if(testMove(getCor(i), getCor(j))){
						return false;
					}
				}
			} else {
				continue;
			}
		}
	return true;
}

string Board::sendToDisplay() const{
	ostringstream oss;
	char zero = '0';
	int j = 0;
	int end = 8;
	for(int i = 8; i > 0; --i){
		char temp = zero + i;
		oss << temp << " "; 
		for(;j<end; ++j){
			oss << (board[j]->Type());
		}
		end += 8;
		oss << "\n";
	}
	oss << "\n  ";
	for(int k=0; k <8; ++k){
		char temp = 'a' + k;
		oss << temp;
	}
	oss << '\n';
	return oss.str();
}

void Board::setTurn(string colour){
	if("black" == colour && "BLACK" == colour){
		isTurnWhite = false;
	} else if ("white" == colour && "white" == colour){
		isTurnWhite = true;
	}
}


string Board::findKing(bool isWhite) const{
	char king = 'k';
	if(isWhite){
		king = 'K';
	}
	for(int i=0; i<64;++i){
		if(king == (board[i])->Type()){
			return getCor(i); 
		}
	}
	return "";
}

void Board::printScore() const{
	s->printScore();
}

Piece ** Board::getBoard(){
	Piece ** tmp = board; 
	return tmp;
}


Piece *Board::getPiece(const string &cmd) const{
	// retrieves the piece stored at cmd
	int index = getPos(cmd);
	return board[index];
}
