CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Werror=vla
EXEC = chess
OBJECTS = main.o bishop.o board.o computer.o empty.o king.o knight.o pawn.o piece.o player.o queen.o rook.o scoreboard.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	        ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	        rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

