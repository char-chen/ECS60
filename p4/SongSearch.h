#ifndef SONGSEARCH_H
#define	SONGSEARCH_H

#include "SearchRunner.h"
#include "LinkedList.h"
#include <cstring>

class SongSearch 
{
private:
  List<Song> *list; 
public:
  SongSearch(const Song *songs, int songCount);
  inline void query(const Request &request, Song answer[], int *answerCount)
 { 
  *answerCount = 0;
  /*req = request.type;
  Song *temp = new Song; 
 
  if (request.type == 0)
    strcpy(temp->title, request.criteria);
  else if (request.type == 1)
    strcpy(temp->title, request.criteria);
  else if (request.type == 2)
    strcpy(temp->artist, request.criteria);
  else if (request.type == 3)
    strcpy(temp->ID, request.criteria);
  */
  
  for (ListNode<Song> *itr = list->header->next; itr != NULL; itr = itr->next)
  {
    switch (request.type)
    {
      case 0 :
        if (strstr(itr->element.title, request.criteria))
          answer[(*answerCount)++] = itr->element;
        break;
      case 1 :
        if (strcmp(itr->element.title, request.criteria) == 0)
          answer[(*answerCount)++] = itr->element;
        break;
      case 2 :
        if (strcmp(itr->element.artist, request.criteria) == 0)
          answer[(*answerCount)++] = itr->element;
        break;
      case 3 :
        if (strcmp(itr->element.ID, request.criteria) >= 0 && strcmp(itr->element.ID, request.criteria2) <= 0)
          answer[(*answerCount)++] = itr->element;
        break;
      case 4 :
        if (strcmp(itr->element.album, request.criteria) == 0)
          answer[(*answerCount)++] = itr->element;
        break;
      default :
        cout << "error" << endl;
    }
  }
  
  //delete temp;
  }
  ~SongSearch();
}; // class SongSearch 

#endif	// SONGSEARCH_H

