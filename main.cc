#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
using namespace std;

int main () {
	Board b = Board(0,0);
	string cmd;
	string start;
	string end;

	string config;

	while (!cin.eof()) {
		cin >> cmd;

		// setup command
		if (cmd == "setup") {
			char piece;
			string colour;
			string coord;
			while (cin >> config) {

				// placing a piece
				if (config[0] == '+') {
					cin >> piece >> coord;
					if (coord[0] >= 'a' && coord[0] <= 'z' && 
						coord[1] >= '1' && coord[1] <= '8') {
						b.place(piece, coord);
						cout << b.sendToDisplay();
					}
				}

				// setting whose turn is next
				else if (config[0] == '=') {
					cin >> colour;
					b.setTurn(colour);
				}

				// removing a piece
				else if (config[0] == '-') {
					cin >> coord;
					if (coord[0] >= 'a' && coord[0] <= 'z' &&
						coord[1] >= '1' && coord[0] <= '8') {
						// insert remove method
						b.place('e',coord);
					}
				}

				// complete setup mode
				else if (config == "done") {
					// check for valid board before exiting
					config = "complete";
					break;
				}
			}
		}

		// game is now running
		else if (cmd == "game" && config == "complete") {

			// player moves
			while (true) {
				cin >> cmd;
				// move command
				if (cmd == "move") {
					cin >> start >> end;
					// insert move method
					b.move(start,end);
					if(b->canPawnPromote(!b->isTurnWhite())){
						char prom;
						cin >> prom;
						if(!b->isTurnWhite() && ('R' == prom || prom == 'N' || 
							'Q' == prom || 'B' == prom)){
							b->place(prom, end);
						} else if ('r' == prom || prom == 'n' || 
							'q' == prom || 'b' == prom){
							b->place(prom, end);
						} else{
							cout << "Invalid promotion" << endl;
						}
					}
					cout << b.sendToDisplay();
				}
				else if (cmd == "resign") {
					// insert resign method
					break;
				}
			}

		}
	}
}