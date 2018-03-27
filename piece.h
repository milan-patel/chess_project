class Board;


class Piece{
	int pos;
	bool white;
public:
	Piece(int pos, bool white);
	virtual bool canMove(const std::string &start, const std::string &end, const Piece ** &b)=0;  
	bool isWhite();
	virtual bool isEmpty()=0;
	int posn();
	void changePos(int posn);
	virtual char Type()=0;
	virtual ~Piece()=0;
};

bool onRightEdge();
bool onLeftEdge();
bool onTopEdge();
bool onBottomEdge();


