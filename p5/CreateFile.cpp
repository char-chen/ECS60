// Author: Sean Davis 
// Created on July 18, 2015, 11:19 AM

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

class Station {
public:
  int x;
  int y;
  int adjacent[10];
  int adjCount;
  int distances[10];
  Station():adjCount(0){}
};

bool makeConnected(Station stations[], int numStations, int mapWidth)
{
  int sets[20000], setCount = numStations, maxDistance = 2, count = 0;
  for(int i = 0; i < numStations; i++)
    sets[i] = i;
  
  while(setCount > 1)
  {
    int station1 = rand() % numStations;
    int station2 = rand() % numStations;
    
    if(sets[station1] != sets[station2] && stations[station1].adjCount < 10
      && stations[station2].adjCount < 10  && station1 != station2 
      && abs(stations[station1].x - stations[station2].x) + abs(stations[station1].y - stations[station2].y) < maxDistance)
    {
      stations[station1].adjacent[stations[station1].adjCount++] = station2;
      stations[station2].adjacent[stations[station2].adjCount++] = station1;
      setCount--;
      int oldSet = sets[station1];
      
      for(int k = 0; k < numStations; k++)
        if(sets[k] == oldSet)
          sets[k] = sets[station2];
    } // if different sets and room
    else
      if(count++ == 3 * numStations)
      {
        maxDistance++;
        count = 0;
      }
  }
  
  for(int i = 1; i < numStations; i++)
    if(sets[i] != sets[0])
    {
      cout << "Found disconnected set\n";
      exit(1);
    }
  
  return true;
}
void createStations(Station stations[], int numStations)
{
  int mapWidth;
  for(mapWidth = 5; mapWidth * mapWidth < 25 * numStations; mapWidth *= 2);
  short map[mapWidth][mapWidth];
  
  int x, y, connectedCount = 0, connections;
  bool OK;

  for(int i = 0; i < mapWidth; i++)
    for(int j = 0; j < mapWidth; j++)
      map[i][j] = -1;
  
  for(int i = 0; i < numStations; i++)
  {
    do
    {
      x = rand() % mapWidth;
      y = rand() % mapWidth;
    }  while(map[x][y] != -1);
    
    map[x][y] = i;
    stations[i].x = x;
    stations[i].y = y;
  }  // for each station
  
  makeConnected(stations, numStations, mapWidth);
  
  for(connections = 1; connections < 5; connections++)
  {
    connectedCount = 0;
    
    for(int i = 0; i < numStations; i++)
      if(stations[i].adjCount >= connections)
        connectedCount++;
    
    for(int radius = 1; connectedCount < numStations - 1; radius++)
    {
      //cout << "Connections: " << connections << " Radius: "  << radius << " connected: " << connectedCount << endl;

      for(int i = 0; i < numStations; i++)
      {
        if(stations[i].adjCount < connections)
        {
          int startx = max(0, stations[i].x - radius);
          int starty = max(0, stations[i].y - radius);
          int endx = min(mapWidth - 1, stations[i].x + radius);
          int endy = min(mapWidth - 1, stations[i].y + radius);

          for(x = startx; x < endx && stations[i].adjCount < connections; x++)
            if(map[x][starty] != -1 && stations[map[x][starty]].adjCount < connections)
            {
              OK = true;
              for(int j = 0; j < stations[map[x][starty]].adjCount; j++)
                if(stations[map[x][starty]].adjacent[j] == i)
                  OK = false;

              if(OK)
              {
                connectedCount += 2;
                stations[map[x][starty]].adjacent[stations[map[x][starty]].adjCount++] = i;
                stations[i].adjacent[stations[i].adjCount++] = map[x][starty];
              }
            }

          for(x = startx; x < endx && stations[i].adjCount < connections; x++)
            if(map[x][endy] != -1 && stations[map[x][endy]].adjCount < connections)
            {
              OK = true;
              for(int j = 0; j < stations[map[x][endy]].adjCount; j++)
                if(stations[map[x][endy]].adjacent[j] == i)
                  OK = false;

              if(OK)
              {  
                connectedCount += 2;
                stations[map[x][endy]].adjacent[stations[map[x][endy]].adjCount++] = i;
                stations[i].adjacent[stations[i].adjCount++] = map[x][endy];
              }  // if OK
            }  

           for(y = starty; y < endy && stations[i].adjCount < connections; y++)
            if(map[startx][y] != -1 && stations[map[startx][y]].adjCount < connections)
            {
              OK = true;
              for(int j = 0; j < stations[map[startx][y]].adjCount; j++)
                if(stations[map[startx][y]].adjacent[j] == i)
                  OK = false;

              if(OK)
              {
                connectedCount += 2;
                stations[map[startx][y]].adjacent[stations[map[startx][y]].adjCount++] = i;
                stations[i].adjacent[stations[i].adjCount++] = map[startx][y];
              } // if OK
            }

           for(y = starty; y < endy && stations[i].adjCount < connections; y++)
            if(map[endx][y] != -1 && stations[map[endx][y]].adjCount < connections)
            {
              OK = true;
              for(int j = 0; j < stations[map[endx][y]].adjCount; j++)
                if(stations[map[endx][y]].adjacent[j] == i)
                  OK = false;

              if(OK)
              {  
                connectedCount += 2;
                stations[map[endx][y]].adjacent[stations[map[endx][y]].adjCount++] = i;
                stations[i].adjacent[stations[i].adjCount++] = map[endx][y];
              }  // if OK
            }
        } // if not adjCount yet
      }  // for each station
    } // for each radius  
  } // for connections  
}

void saveConnections(Station *stations, int numStations, ofstream &outf)
{
  
  for(int i = 0; i < numStations; i++)
  {
    outf << i << "," << stations[i].adjCount;
    for(int j = 0; j < stations[i].adjCount; j++)
    {
      outf << "," << stations[i].adjacent[j] << ','
      << (int) sqrt((10 * stations[i].x - 10 * stations[stations[i].adjacent[j]].x)
        * (10 * stations[i].x - 10 * stations[stations[i].adjacent[j]].x)
        + (10 * stations[i].y - 10 * stations[stations[i].adjacent[j]].y)
        * (10 * stations[i].y - 10 * stations[stations[i].adjacent[j]].y));
    }
    outf << endl;
  }  // for each station
} // saveConnections


void saveCars(int numStations, ofstream &outf, int cars)
{
  for(int i = 0; i < cars; i++)
  {
    int dest, start = rand() % numStations;

    while((dest = rand() % numStations) == start);

    outf << i << "," << start << "," << dest << endl;
  } // for each car
} // saveCars()

int main(int argc, char** argv) 
{
  int cars, seed, numStations;
  char filename[80];
  cout << "stations (must be even and greater than 5): ";
  cin >> numStations;
  numStations &= 0xFFFFFE;  // ensures even
  cout << "cars: ";
  cin >> cars;
  cout << "seed: ";
  cin >> seed;

  
  sprintf(filename,"net-%d-%d-%d.csv",numStations, cars, seed);
  srand(seed);
  Station *stations = new Station[numStations + 1];  
  createStations(stations, numStations); 
  ofstream outf(filename);
  outf << numStations << ',' << cars << endl;
  saveConnections(stations, numStations, outf);
  saveCars(numStations, outf, cars);
  outf.close();
  cout << "Done\n";
  return 0;
} // main())

