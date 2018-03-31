#ifndef ___COMP___
#define ___COMP___

#include <string>

#include "player.h"

class Comp: public Player {
	int level;
public:
	Comp(int level,bool white);
	std::string generateMove();
};

#endif
