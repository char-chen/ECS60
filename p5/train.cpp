#include <stdio.h>
#include "trainRunner.h"
#include "train.h"
#include "QuadraticProbing.h"
 
void printArr(int dist[], int n);

Train::Train(Station stations[], int numStations) : network(numStations) 
{
  for (int i = 0; i < numStations; ++i)
    for (int j = 0; j < stations[i].adjCount; ++j)
      network.addEdge(i, stations[i].adjacent[j], stations[i].distances[j]);
  //network.dijkstra(2);
  //network.printArr();
} //Train

void Graph::printArr()
{
  printf("Vertex Distance from Source\n");
  for (int i = 0; i < V; ++i)
    printf("%d   %d   %d\n", i, dist[i], paths[i]);
}

void Train::run(const Car cars[], int numCars, Action actions[], int *numActions)
{
  *numActions = 0;
  int currStation = 0;
  Action action;
  List<int> undelivered;
  QuadraticHashTable<int> delivering(-1, 200);
  
  for (int i = 0; i < numCars; ++i)
    undelivered.insert(i, undelivered.zeroth());
 
  while (!undelivered.isEmpty())
  {
    int nextStation = -1, minDistance = INT_MAX, destStation = -1;
    network.dijkstra(currStation);
    
    while (currStation != destStation)
    {
      for (ListNode<int> *prev = undelivered.header, *ptr = undelivered.header->next; ptr; prev = ptr, ptr = ptr->next)
      {
        int carID = ptr->element;
         
        if (cars[carID].source == currStation && delivering.find(carID) == -1 && delivering.count < 100)
        {
          action.actionType = PICKUP;
          action.stationOrCar = carID;
          actions[(*numActions)++] = action;
          delivering.insert(carID);
          cout << "Pick " << carID << " " << delivering.count << " " << undelivered.count << endl;
        } //Pick up car
        else if (cars[carID].destination == currStation && delivering.find(carID) != -1)
        {
          ptr = prev;
          action.actionType = DROPOFF;
          action.stationOrCar = carID;
          actions[(*numActions)++] = action;
          delivering.remove(carID);
          undelivered.remove(carID);
          cout << "Drop " << carID << " "<< delivering.count <<" " << undelivered.count << endl;
          continue;
        } //Drop off car
        
        if (destStation == -1)
        {
          if (delivering.find(carID) == -1 && cars[carID].source != currStation && network.dist[cars[carID].source] < minDistance)
          {
            nextStation = cars[carID].source;
            minDistance = network.dist[nextStation];
          }
          else if (delivering.find(carID) != -1 && network.dist[cars[carID].destination] < minDistance)
          {
            nextStation = cars[carID].destination;
            minDistance = network.dist[nextStation];
          }
        } //
        else
          {nextStation = destStation;}
      }
      
      //return; 
      if (nextStation != -1) 
      {
        for (destStation = nextStation; nextStation != currStation; nextStation = network.paths[nextStation])
         action.stationOrCar = nextStation;
        
        action.actionType = MOVE;
        actions[(*numActions)++] = action;
        currStation = action.stationOrCar; 
      }
      else
        break;
        cout << currStation << " " << destStation << " " << minDistance << endl;     
    }
  }
} //run
