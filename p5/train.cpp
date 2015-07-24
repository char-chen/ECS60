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
  QuadraticHashTable<int> delivering(-1, 100);
  
  for (int i = 0; i < numCars; ++i)
    undelivered.insert(i, undelivered.zeroth());
  
  while (true)
  {
    int nearestCar = -1, minDistance = INT_MAX, destStation = -1;
    network.dijkstra(currStation);
    
    while (currStation != destStation)
    {
      for (ListNode<int> *prev = undelivered.header, *ptr = undelivered.header->next; ptr; ptr = ptr->next)
      {
        if (cars[ptr->element].source == currStation)
        {
          action.actionType = PICKUP;
          action.stationOrCar = ptr->element;
          actions[(*numActions)++] = action;
          delivering.insert(ptr->element);
          undelivered.remove(ptr->element);
          ptr = prev;
        } //Pick up car
        else if (cars[ptr->element].destination == currStation && delivering.find(ptr->element) != -1)
        {
          action.actionType = DROPOFF;
          action.stationOrCar = ptr->element;
          actions[(*numActions)++] = action;
          delivering.remove(ptr->element);
          continue;
        } //Drop off car
        
        if (undelivered.isEmpty())
          return;
        
        if (network.dist[cars[ptr->element].source] < minDistance)
        {
          minDistance = network.dist[cars[ptr->element].source];
          nearestCar = ptr->element;
        } //
        
        prev = ptr;
      }
      
      for (int nextStation = destStation = cars[nearestCar].source; nextStation != currStation; nextStation = network.paths[nextStation])
        currStation = action.stationOrCar = nextStation;
      
      action.actionType = MOVE;
      actions[(*numActions)++] = action;
    }
  }
} //run
