#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

class Song
{
public:
char title[68]; // max 67 + '\0';
char album[36]; // max 35 + '\0';
char artist[26]; // max 25 + '\0'
char ID[11]; // max 10 + '\0';
}; // class Song

class ID
{
public:
  char ID[11];
};

int IDCmp(const void *ptr1, const void *ptr2)
{
  return strcmp(((ID*)ptr1)->ID, ((ID*)ptr2)->ID);
}

int main()
{
  char s[256], filename[80];
  int numRequests, seed, count = 0, answers[23000], j;
  cout << "Seed>> ";
  cin >> seed;
  cout << "Number of requests>> ";
  cin >> numRequests;
  srand(seed);
  sprintf(filename, "Requests-%d-%d.txt",numRequests, seed);
  Song *songs = new Song[42553];
  ID *IDs = new ID[42553];
  ifstream inf("songs.txt");

  while(inf.getline(s, 256))
  {
    strcpy(songs[count].title, strtok(s, "@"));
    strcpy(songs[count].artist, strtok(NULL, "@"));
    strcpy(songs[count].ID, strtok(NULL, "@"));
    strcpy(IDs[count].ID, songs[count].ID);
    strcpy(songs[count++].album, strtok(NULL, "\n"));
  } // while inf

  inf.close();
  
  qsort(IDs, 42553, sizeof(ID), IDCmp);
  ofstream outf(filename);
  outf << numRequests << endl;

  for(int i = 0; i < numRequests; i++)
  { 
    int type = rand() % 15;
    int songNum = rand() % count;
    int count2 = 0;
    
    if(type < 5)
    {
      do
      {
        songNum = rand() % count;
        
        int pos = rand() % strlen(songs[songNum].title);
        while(pos > 0 && isalpha(songs[songNum].title[pos]))
          pos--;
        
        if(!isalpha(songs[songNum].title[pos]))
          pos++;
        
        for(j = 0; songs[songNum].title[pos] && songs[songNum].title[pos] != ' '; j++)
          s[j] = songs[songNum].title[pos++];
        
        s[j] = '\0';
        
        count2 = 0;
        
        for(j = 0; count2 < 1000 && j < count; j++)
          if(strstr(songs[j].title, s))
            answers[count2++] = j;
      }  while(count2 >= 1000 || count2 < 2);
      
      outf << "0," << s << '@';
    }
    else
      if(type < 9)
      {
        outf << "1," << songs[songNum].title << '@';

        for(int j = 0; j < count; j++)
          if(strcmp(songs[songNum].title, songs[j].title) == 0)
            answers[count2++] = j;
      }
      else
        if(type < 12)
        {
          outf << "2," << songs[songNum].artist << '@';

          for(int j = 0; j < count; j++)
            if(strcmp(songs[songNum].artist, songs[j].artist) == 0)
              answers[count2++] = j;
        }
        else
          if(type < 14)
          {
            songNum = rand() % 40000;
            int songNum2 = songNum + 5 + rand() % 1000;
            outf << "3," << IDs[songNum].ID << '@' << IDs[songNum2].ID << '@';

            for(int j = 0; j < count; j++)
              if(strcmp(IDs[songNum].ID, songs[j].ID) <= 0
                && strcmp(IDs[songNum2].ID, songs[j].ID) >= 0)
                answers[count2++] = j;
          }
          else  // type == 14
            {
              
              outf << "4," << songs[songNum].album << '@';

              for(int j = 0; j < count; j++)
                if(strcmp(songs[songNum].album, songs[j].album) == 0)
                  answers[count2++] = j;
            }

    outf << count2;
    
    for(int j = 0; j < count2; j++)
      outf << ',' << answers[j];
    
    outf << endl;

  } // for i

  return 0;
}
//---------------------------------------------------------------------------
