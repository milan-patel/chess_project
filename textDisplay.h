#ifndef ___TEXTDIS___
#define ___TEXTDIS___

#include <string>
#include "board.h"

class TextDisplay {
	std::string curr_board;
	Board *b;
public:
	void notify();
}; 


#endif
