#include "computer.h"
#include <string>
#include "player.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

Comp::Comp(int level, bool white): Player{white}, level{level} {}



std::string Comp::generateMove(Board *b, std::string &first, std::string &last){
	std::vector <Piece *> myTeam; 
	for(int i=0; i<64; ++i){
		if(b->getBoard()[i]->isWhite == isPlayerWhite()){
			myTeam.push_back(b->getBoard()[i]); //adds 
		}
	}
	std::srand(std::time(nullptr)); // use current time as seed
	int start = std::rand()/((RAND_MAX + 1u)/myTeam.size());
	int end = -1;
	if(isPlayerWhite()){
		while(end == -1){	
			for(int j=0; j<64; ++j){
				if(b->testMove(convert(start),convert(j))){
					end = j;
					break; 
				}
			}
			start = std::rand()/((RAND_MAX + 1u)/myTeam.size())
		}
	} else{
		while(end == -1){	
			for(int k=0; k<64; ++k){
				if(b->testMove(convert(start),convert(k))){
					end = j;
					break; 
				}
			}
			start = std::rand()/((RAND_MAX + 1u)/myTeam.size())
		}
	}
	first = convert(start);
	last = convert(end);
	return;
}

static std::string convert(int index){
	std::string s;
	std::ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}
