train.out : train.o trainRunner.o Dijkstra.o
	g++ -ansi -Wall -g -o train.out train.o trainRunner.o Dijkstra.o

train.o : train.cpp trainRunner.h train.h Dijkstra.h QuadraticProbing.h LinkedList.h
	g++ -ansi -Wall -g -c train.cpp

trainRunner.o : trainRunner.cpp CPUTimer.h trainRunner.h train.h 
	g++ -ansi -Wall -g -c trainRunner.cpp

Dijkstra.o: Dijkstra.cpp Dijkstra.h
	g++ -ansi -Wall -g -c Dijkstra.cpp

clean : 
	rm -f train.out train.o trainRunner.o Dijkstra.o core 
