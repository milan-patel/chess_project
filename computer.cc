#include "computer.h"
#include <string>
#include "player.h"

Comp::Comp(int level, bool white): Player{white}, level{level} {}

std::string Comp::generateMove(Board *b){
	return '';
}
