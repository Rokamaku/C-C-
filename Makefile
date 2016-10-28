Snake: board.o snake.o main.cpp
	g++ -o Snake main.cpp board.o snake.o -std=c++11 -lcurses
snake.o: snake.cpp snake.h
	g++ -c snake.cpp
board.o: board.cpp board.h
	g++ -c board.cpp -std=c++11
make clean:
	rm -rf *.o