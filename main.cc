#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main () {
	string cmd;
	//string cur;
	//string dest;

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
				if (config[0] == "+") {
					cin >> piece >> coord;
					if (coord[0] >= 'a' && coord[0] <= 'z' && 
						coord[1] >= '1' && coord[1] <= '8') {
						// insert place method
						// print board
					}
				}

				// setting whose turn is next
				else if (config[0] == '=') {
					cin >> colour;
				}

				// removing a piece
				else if (config[0] == '-') {
					cin >> coord;
					if (coord[0] >= 'a' && coord[0] <= 'z' &&
						coord[1] >= '1' && coord[0] <= '8') {
						// insert remove method
					}
				}

				// complete setup mode
				else if (config == "done") {
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
					// insert move method
				}
				else if (cmd == "resign") {
					// insert resign method
					break;
				}
			}

		}
	}
}