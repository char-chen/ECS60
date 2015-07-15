#include "SongSearch.h"
#include "SearchRunner.h"
#include "mynew.h"
#include <cstring>
#include <iostream>
using namespace std;

//int req = -1;

SongSearch::SongSearch(const Song *songs, int songCount) 
{
 /* Song *notFound = new Song;
  notFound->title[0] = 0;
  notFound->artist[0] = 0;
  notFound->ID[0] = 0;
  notFound->album[0] = 0;
  */
  
  list = new List<Song>();
  ListItr <Song> listItr = list->zeroth();
  
  for (int i = 0; i < songCount; i++)
    list->insert(songs[i], listItr);
  
} //SongSearch

SongSearch::~SongSearch()
{
  delete list;
}

void SongSearch::query(const Request &request, Song answer[], int *answerCount)
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
} //query

bool operator<(const Song& lhs, const Song& rhs)
{
  return strcmp(lhs.title, rhs.title) < 0;
} //operator <

bool operator!=(const Song& lhs, const Song& rhs)
{
  /*if (req == 0)
    return strstr(lhs.title, rhs.title);
  else if (req == 1)
    return strcmp(lhs.title, rhs.title) != 0; 
  else if (req == 2)
    return strcmp(lhs.artist, rhs.artist) != 0;
  else if (req == 3)
    return strcmp(lhs.ID, rhs.ID) != 0; 
  else if (req == 4)
    return strcmp(lhs.album, rhs.album) != 0;
  */
  cout << "error" << endl;
  return false;
} //operator !=
