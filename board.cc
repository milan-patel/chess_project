

Board::Board(int player1, int player2): Board{new Piece*[63]}, isTurnWhite{true},
		inCheck{false}, Scoreboard{Scoreboard()}, p1{new Player()}, p2{new Player()}{
			if(player1 > 0){
				delete p1;
				p1 = new Comp(player1);
			} if(player2 > 0){
				delete p2;
				p1 = new Comp(player2);
			}
		}


Board::~Board(){
	for(int i =0; i<64;++i){
		delete Board[i];
	}
	delete [] Board;
	delete p1;
	delete p2;
}

