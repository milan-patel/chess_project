
class Piece{
	int row;
	int column;
	char type;
	bool white;
public:
	virtual bool canMove(std::string start, std::string end)=0;
	virtual bool isEmpty()=0;	
};