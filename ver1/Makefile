CXXFLAGS=-g -std=c++11

all: field.o const.o game.o main.o *.h
	g++ -o battle field.o const.o game.o main.o -std=c++11

test: field.o const.o game.o test.o *.h
	g++ -o test field.o const.o game.o test.o -std=c++11 -g

main.o: main.cpp *.h
	g++ -c main.cpp -std=c++11
	
test.o: test.cpp *.h
	g++ -c test.cpp -std=c++11
	
	
field.o: field.cpp *.h
	g++ -c field.cpp -std=c++11
	
game.o: game.cpp *.h
	g++ -c game.cpp -std=c++11

const.o: const.cpp *.h
	g++ -c const.cpp -std=c++11

