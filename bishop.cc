#include "board.h"
#include "bishop.h"
#include <string>

Bishop::Bishop(int pos, bool isWhite): Piece(pos, isWhite) {}

bool Bishop::isEmpty() const{
	return false;
}

bool Bishop::canMove(const std::string &start,const std::string &end, Piece ** b) const{
	int begin = getPos(start);
	int fin = getPos(end);
	if(!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin){
		while(true){
			if(begin == fin && !(isWhite() == b[begin]->isWhite())){
				return true;
			} else if(begin == fin && b[begin]->isEmpty()){
				return true;
			} else if(!b[begin]->isEmpty()){
				return false;
			} else {
				begin += 7;
			}
		} 
	} else if(!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin){
		while(true){
			if(begin == fin && !(isWhite() == b[begin]->isWhite())){
				return true;
			} else if(begin == fin && b[begin]->isEmpty()){
				return true;
			} else if(!b[begin]->isEmpty()){
				return false;
			} else {
				begin -= 7;
			}
		} 
	} else if (begin % 9 == fin % 9 && begin < fin){
		while(true){
			if(begin == fin && !(isWhite() == b[begin]->isWhite())){
				return true;
			} else if(begin == fin && b[begin]->isEmpty()){
				return true;
			} else if(!b[begin]->isEmpty()){
				return false;
			} else {
				begin += 9;
			}
		} 
	} else if (begin % 9 == fin % 9 && begin > fin){
		while(true){
			if(begin == fin && !(isWhite() == b[begin]->isWhite())){
				return true;
			} else if(begin == fin && b[begin]->isEmpty()){
				return true;
			} else if(!b[begin]->isEmpty()){
				return false;
			} else {
				begin -= 9;
			}
		} 
	} else {
		return false;
	}
}

char Bishop::Type() const{
	if(isWhite()){
		return 'B';
	} else {
		return 'b';
	}
}