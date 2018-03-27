class Board;


class Piece{
	int pos;
	bool white;
public:
	Piece(int pos, bool white);
	virtual bool canMove(const std::string &start, const std::string &end)=0;  
	bool isWhite();
	virtual bool isEmpty()=0;
	void changePos(int posn);
	Board *getBoard();
	virtual char Type()=0;
	virtual ~Piece()=0;
};

