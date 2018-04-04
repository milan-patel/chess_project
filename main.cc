#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
using namespace std;

bool requiresDefaultSetup = true;

void setup(Board *b){
	b->clearBoard();
	requiresDefaultSetup = false;
	GraphicsDisplay *g = new GraphicsDisplay();
	string action;
	char piece;
	string colour;
	string coord;
	while (cin >> action) {

		// placing a piece
		if (action[0] == '+') {
			cin >> piece >> coord;
			if (coord[0] >= 'a' && coord[0] <= 'h' && 
				coord[1] >= '1' && coord[1] <= '8') {
				b->place(piece, coord);
				cout << b->sendToDisplay();
			}
		}

		// setting whose turn is next
		else if (action[0] == '=') {
			cin >> colour;
			b->setTurn(colour);
		}

		// removing a piece
		else if (action[0] == '-') {
			cin >> coord;
			if (coord[0] >= 'a' && coord[0] <= 'h' &&
				coord[1] >= '1' && coord[1] <= '8') {
				// insert remove method
				b->place('e',coord);
				cout << b->sendToDisplay();
		}
	}

		// complete setup mode
		else if (action == "done" && b->validBoard()) {
			// check for valid board before exiting
			b->gameOn();	
			break;
		}
		else if (action == "done" && !b->validBoard()) {
			// check for valid board before exiting
			cout << "Invalid board. Continue placing pieces." << endl;
		}
	}
}

void game(Board *b){
	string action;
	string start;
	string end;
	if(requiresDefaultSetup){
		GraphicsDisplay *gd = new GraphicsDisplay();
		b->setgd(gd);
		b->normalSetup();
	}
	cout << b->sendToDisplay();
	while (cin >> action) {
		// move command
		if (action == "move") {
			cin >> start >> end;
			// insert move method
			if(start.length() != 2 || end.length() != 2){
				cout << "Invalid move. Try again." << endl;
				continue;
			}
			b->move(start,end);
			if (b->canPawnPromote()) { // requires input from the user in the case of pawn promotion
				char prom;
				cin >> prom;
				if (!b->getTurnStatus() && 
					('R' == prom || prom == 'N' || 'Q' == prom || 'B' == prom)) {
					b->place(prom, end);
				}
				else if ('r' == prom || prom == 'n' || 
					'q' == prom || 'b' == prom) {
					b->place(prom, end);
				}
				else {
					cout << "Invalid promotion" << endl;
				}
			}
			if(b->isGameOver()){
				break;
			}
			cout << b->sendToDisplay();
		}
		else if (action == "resign") {
			// insert resign method
			if(b->getTurnStatus()){
				b->endGame("white resigns");
			} else {
				b->endGame("black resigns");
			}
			break;
		}
	}
}

void players(Board *b){
	b->gameOn();
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
		b->newPlayers(ip1,ip2);	
	}
}

int main () {
	Board *b = new Board(0,0);
	string cmd;

	while (!cin.eof()) {
		cin >> cmd;

		// setup command
		if (cmd == "setup") {
			setup(b);
		}

		// game is now running
		else if (cmd == "game") {
			players(b);
			game(b);
		}
	}
	b->printScore();
	delete b;
}
