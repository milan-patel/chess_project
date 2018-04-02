#include "scoreboard.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std; 

Scoreboard::Scoreboard():whiteScore{0}, blackScore{0}{}

void Scoreboard::printScore(){
	ostringstream oss;
	oss << "Final score:" << endl;
	oss << "White: " << whiteScore << endl;
	oss << "Black: " << blackScore << endl;
	cout << oss.str();
}

void Scoreboard::check(bool isWhiteInCheck){
	string s;
	if(isWhiteInCheck){
		s = "White";
	} else {
		s = "Black";
	}
	cout << s << " is in check." << endl;
}

void Scoreboard::tie(){
	whiteScore += 0.5;
	blackScore += 0.5;
	cout << "Stalemate!" <<endl;
}

void Scoreboard::win(bool isWhite){
	if(isWhite){
		whiteScore += 1.0;
		cout << "Checkmate! White wins!" << endl;
	} else{
		blackScore += 1.0;
		cout << "Checkmate! Black wins!" << endl;
	}
}

void Scoreboard::resign(bool isWhite){
	if(!isWhite){
		whiteScore += 1.0;
		cout << "White wins!" << endl;
	} else{
		blackScore += 1.0;
		cout << "Black wins!" << endl;
	}
}
