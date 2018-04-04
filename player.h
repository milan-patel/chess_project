#ifndef ___PLAYER___
#define ___PLAYER___

#include <string>

class Player {
	bool isWhite;
public:
	Player(bool white);
	bool isPlayerWhite();
	virtual void move(std::string begin, std::string end);
};

#endif
