#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "CPUTimer.h"
#include "trainRunner.h"
#include "train.h"

using namespace std;

CPUTimer ct;

void readFile(ifstream &inf, Station stations[], int numStations, int numCars,
  Car cars[])
{
  int i, j;
  char line[256];
  inf.ignore(1000, '\n');

  for(i = 0; i < numStations; i++)
  {
    inf.getline(line, 256);
    strtok(line, ",");
    stations[i].adjCount = atoi(strtok(NULL, ","));
    
    for(j = 0; j < stations[i].adjCount; j++)
    {
      stations[i].adjacent[j] = atoi(strtok(NULL, ","));
      stations[i].distances[j] = atoi(strtok(NULL, ","));
    } // for j
  }  // for each station

  for(i = 0; i < numCars; i++)
  {
    inf.getline(line, 256);
    strtok(line, ",");
    cars[i].source = atoi(strtok(NULL, ","));
    cars[i].destination = atoi(strtok(NULL, ","));
  } // for each car 
}  // readFile()

int  checkActions(Action actions[], int numActions, 
  Station stations[], int numStations, Car cars[], int numCars)
{
  int j, totalDistance = 0, currentStation = 0, payload[100], payloadCount = 0;
  bool delivered[5000];
  memset(delivered, false, sizeof(delivered));
  
  for(int i = 0; i < numActions; i++)
  {
    switch(actions[i].actionType)
    {
      case MOVE:
        for(j = 0; j < stations[currentStation].adjCount; j++)
          if(stations[currentStation].adjacent[j] == actions[i].stationOrCar)
          {
            totalDistance += stations[currentStation].distances[j];
            break;
          }  // if found the move is to an adjacent station
        
        if(j == stations[currentStation].adjCount)
          cout << "Action #" << i << " moved from " << currentStation 
            << " to " << actions[i].stationOrCar << " which are not adjacent.\n";
            
        currentStation = actions[i].stationOrCar;  
        break;
      case PICKUP:
        if(cars[actions[i].stationOrCar].source != currentStation)
          cout << "Action #" << i << " picked up car #" 
            << actions[i].stationOrCar << " at station #" << currentStation
            << " which was not that car's source city.\n";
        
        if(payloadCount == 100)
           cout << "Action #" << i << " picked up car #" 
            << actions[i].stationOrCar << " at station #" << currentStation
            << " when the train already had 100 cars.\n";
        else
          payload[payloadCount++] = actions[i].stationOrCar;
        break;
      case DROPOFF:
         if(cars[actions[i].stationOrCar].destination != currentStation)
          cout << "Action #" << i << " dropped off car #" 
            << actions[i].stationOrCar << " at station #" << currentStation
            << " which was not that car's destination city.\n";
         
         for(j = 0; j < payloadCount; j++)
           if(payload[j] == actions[i].stationOrCar)
           {
             delivered[actions[i].stationOrCar] = true;
             payload[j] = payload[payloadCount - 1];
             break;
           }
         
         if(j == payloadCount)
          cout << "Action #" << i << " dropped off car #" 
            << actions[i].stationOrCar << " at station #" << currentStation
            << ", but that car was not on the train.\n";
         else
           payloadCount--;
    }  // switch
  }  // for each activity
  
  for(int i = 0; i < numCars; i++)
    if(!delivered[i])
      cout << "Car #" << i << " was never delivered.\n";
  
  return totalDistance;
} // checkActivities()

int main(int argc, char* argv[])
{
  char c;
  int numStations, numCars, numActions;
  Action *actions = new Action[1000000];
  ifstream inf(argv[1]);
  inf >> numStations >> c >> numCars;
  Station *stations = new Station[numStations];
  Station *stations2 = new Station[numStations];
  Car *cars = new Car[numCars];
  readFile(inf, stations, numStations, numCars, cars);
  memcpy(stations2, stations, sizeof(Station) * numStations);
  CPUTimer ct;
  Train *train = new Train(stations, numStations);
  delete [] stations;
  train->run((const Car*) cars, numCars, actions, &numActions);
  double time = ct.cur_CPUTime();
  int totalDistance = checkActions(actions, numActions, stations2, 
    numStations,cars, numCars);
  cout << "CPU time: " << time << " Total distance: " << totalDistance << endl;
  return 0;
}  // main()

