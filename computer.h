#ifndef ___COMP___
#define ___COMP___

#include <string>

#include "player.h"
class Board;

class Comp: public Player {
	int level;
public:
	Comp(int level,bool white);
	std::string generateMove(Board *b);
};

#endif
