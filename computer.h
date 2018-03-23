#include "player.h"

class Comp: public Player {
	int level;
public:
	std::string generateMove();
};
