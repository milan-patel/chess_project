#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "board.h"

std::string getCo(int index) {
        // inverse of getPos
        std::string s;
        std::ostringstream oss;
        char row = '0' + (8 - (index / 8)); 
        char col = 'a' + (index % 8);
        oss << col;
        oss << row;
        s = oss.str();
        return s;
}

int main () {
        std::string s;
        Board b = Board(0,0);
        b.gameOn();
        b.setTurn("white");
        b.place('K',"a8");
        b.place('k' , "h1");
        b.place('b', "b5");
        std::cout << b.sendToDisplay();
        // b.move("b5", "c6");
        for(int i=0; i < 64; ++i){
                s = getCo(i);
                if(b.testMove("b5",s)){
                        std::cout << s << std::endl;
                }
        }
}
