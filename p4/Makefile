SongSearch.out : mynew.o SearchRunner.o SongSearch.o  
	g++ -ansi -Wall -g -o SongSearch.out mynew.o SearchRunner.o SongSearch.o  

mynew.o : mynew.cpp mynew.h 
	g++ -ansi -Wall -g -c mynew.cpp

SearchRunner.o : SearchRunner.cpp CPUTimer.h mynew.h SearchRunner.h SongSearch.h 
	g++ -ansi -Wall -g -c SearchRunner.cpp

SongSearch.o : SongSearch.cpp SongSearch.h SearchRunner.h 
	g++ -ansi -Wall -g -c SongSearch.cpp

clean : 
	rm -f SongSearch.out mynew.o  SearchRunner.o  SongSearch.o   
