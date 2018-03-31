#include <string>
#include "piece.h"
#include <sstream>

Piece::Piece(int pos, bool white): pos{pos}, white{white}{}

bool Piece::isWhite() const{
	return white;
}

void Piece::changePos(int posn){
	pos = posn;
}

int Piece::posn() const{
	return pos;
}

Piece::~Piece(){}

void Piece::moved(){}

bool Piece::first() const{return false;}

bool Piece::onRightEdge() const{ 
	if(7 ==(posn() % 8)){
		return true;
	} 
	return false;
}

bool Piece::onLeftEdge() const{
	if(0 ==(posn() % 8)){
		return true;
	} 
	return false;
}

bool Piece::onTopEdge() const{
	if(0 <= posn() && posn() <= 7){
		return true;
	} 
	return false;
}

bool Piece::onBottomEdge() const{
	if(56 <= posn() && posn() <= 63){
		return true;
	} 
	return false;
}

int getPos(const std::string &cmd){
	int col = (cmd[0] - 'a');
	int row = (cmd[1] - '1');
	row = 7 - row;
	int pos = 8*row+col; 
	return pos;
}

std::string getCor(int index){
	// inverse of getPos
	std::string s;
	std::ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}

