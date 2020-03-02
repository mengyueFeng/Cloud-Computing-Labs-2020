OBJS = sudoku_solver.o main.o io.o thread_solver.o

sudoku: $(OBJS)
	g++ -Wall -g -std=c++0x -o $@ $(OBJS) -pthread

main.o: main.cpp main.h
	g++ -Wall -g -std=c++0x -c $^ -pthread

sudoku_solver.o: sudoku_solver.cpp sudoku_solver.h
	g++ -Wall -g -std=c++0x -c $^ -pthread

io.o: io.cpp io.h
	g++ -Wall -g -std=c++0x -c $^ -pthread

thread_solver.o: thread_solver.cpp thread_solver.h
	g++ -Wall -g -std=c++0x -c $^ -pthread

PHONY: clean

clean:
	rm *.o *.h.gch sudoku
	clear
