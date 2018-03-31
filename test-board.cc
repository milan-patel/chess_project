#include <string>
#include <iostream>
#include "board.h"

int main () {
	std::string start, end;
	Board b = Board(0,0);
	b.normalSetup();
	std::cout << b.sendToDisplay();
	std::cin >> start >> end;
	b.move(start,end);
	std::cout << b.sendToDisplay();
}