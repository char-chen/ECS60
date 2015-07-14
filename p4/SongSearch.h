#ifndef SONGSEARCH_H
#define	SONGSEARCH_H

#include "SearchRunner.h"

class SongSearch {
public:
  SongSearch(const Song *songs, int songCount);
  void query(const Request &request, Song answer[], int *answerCount);
private:

}; // class SongSearch 

#endif	// SONGSEARCH_H

