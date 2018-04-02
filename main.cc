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
		else if (cmd == "game") {
			string p1;
			string p2;
			int ip1;
			int ip2;

			cin >> p1 >> p2;

			// setup Board with humans or computers
			if (p1 == "human") {
				ip1 = 0;
			}

			else if (p1 != "human") {
				char temp = p1[p1.length()-2];
				ip1 = temp - '0';
			}

			if (p2 == "human") {
				ip2 = 0;
			}

			else if (p2 != "human") {
				char temp = p2[p2.length() - 2];
				ip2 = temp - '0';
			}

			if (ip1 != 0 && ip2 != 0) {
				b.newPlayers(ip1,ip2);	
			}
			
			if (config.empty()) {
				b.normalSetup();
			}
			// player moves
			while (cin >> cmd) {
				// move command
				if (cmd == "move") {
					cin >> start >> end;
					// insert move method
					b.move(start,end);
					if (b.canPawnPromote()) {
						char prom;
						cin >> prom;
						if (!b.getTurnStatus() && 
							('R' == prom || prom == 'N' || 'Q' == prom || 'B' == prom)) {
							b.place(prom, end);
						}
						else if ('r' == prom || prom == 'n' || 
							'q' == prom || 'b' == prom) {
							b.place(prom, end);
						}
						else {
							cout << "Invalid promotion" << endl;
						}
					}
					cout << b.sendToDisplay();
				}
				else if (cmd == "resign") {
					// insert resign method
					b.rsesignGame(!b.getTurnStatus());
					break;
				}
			}
		}
	}
	b.printScore();
}
