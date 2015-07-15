#ifndef SONGSEARCH_H
#define	SONGSEARCH_H

#include "SearchRunner.h"
#include "LinkedList.h"

class SongSearch 
{
private:
  List<Song> *list; 
public:
  SongSearch(const Song *songs, int songCount);
  void query(const Request &request, Song answer[], int *answerCount);
  ~SongSearch();
}; // class SongSearch 

#endif	// SONGSEARCH_H

