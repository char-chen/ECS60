// Author: Sean Davis 
// Created on July 11, 2015, 8:32 PM

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "CPUTimer.h"
#include "mynew.h"
#include "SearchRunner.h"
#include "SongSearch.h"
using namespace std;

extern int maxRAM;
extern int currentRAM;

int readSongFile(Song *songs)
{
  char s[2000];
  int count = 0;
  ifstream inf("songs.txt");

  while(inf.getline(s, 2000))
  {
    strcpy(songs[count].title, strtok(s, "@"));
    strcpy(songs[count].artist, strtok(NULL, "@"));
    strcpy(songs[count].ID, strtok(NULL, "@"));
    strcpy(songs[count++].album, strtok(NULL, "\n"));
  } // while inf
 
  inf.close();
  return count;
}  // readSongFile()


Request* readRequests(const Song *songs, Answer **answers, int *requestCount,
  const char *filename)
{
  char *s = new char[100000];
  ifstream inf(filename);
  inf >> *requestCount;
  Request *requests = new Request[*requestCount];
  *answers = new Answer[*requestCount];
  inf.ignore(1000, '\n');
  
  for(int i = 0; i < *requestCount; i++)
  {
    inf.getline(s, 100000);
    requests[i].type = atoi(strtok(s, ","));
    strcpy(requests[i].criteria, strtok(NULL, "@"));
    if(requests[i].type == 3)
      strcpy(requests[i].criteria2, strtok(NULL, "@"));
    (*answers)[i].count = atoi(strtok(NULL, ","));
    (*answers)[i].length = 0;
    
    for(int j = 0; j < (*answers)[i].count; j++)
    {
      int songNum = atoi(strtok(NULL, ","));
    
      (*answers)[i].length += strlen(songs[songNum].ID)
        + strlen(songs[songNum].album) + strlen(songs[songNum].artist)
        + strlen(songs[songNum].title);
    }
  }  // while more in file
  delete[] s;
  return requests;
}  // readRequests()

int main(int argc, char** argv) 
{
  int answerCount, requestCount;
  Song answer[2000], *songs = new Song[42553];
  Answer *answers;
  int songCount = readSongFile(songs);
  Request *requests = readRequests(songs, &answers, &requestCount, argv[1]);
  
  CPUTimer ct;
  initializeNew();
  maxRAM = currentRAM = 0;
  ct.reset();
  SongSearch *songSearch = new SongSearch(songs, songCount);
  int tempRAM = currentRAM;
  delete [] songs;
  maxRAM = currentRAM = tempRAM;
  
  for(int i = 0; i < requestCount; i++)
  {
    songSearch->query(requests[i], answer, &answerCount);
    
    if(answerCount != answers[i].count)
      cout << "Query #"  << i << " incorrect count. Yours: " << answerCount
        << " Correct: " << answers[i].count << endl;
    else  // correct number of songs matched
    {
      int length = 0; 
      for(int j = 0; j < answerCount; j++)
        length += strlen(answer[j].ID) + strlen(answer[j].album) 
          + strlen(answer[j].artist) + strlen(answer[j].title);
      
      if(length != answers[i].length)
        cout << "Query #"  << i << " incorrect length. Yours: " << length
        << " Correct: " << answers[i].length << endl;
    }  // else 
  }  // for each request

  cout << "CPU Time: " << ct.cur_CPUTime() <<  " RAM: " << maxRAM <<  endl; 
  return 0;
} // main())

