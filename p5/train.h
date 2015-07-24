#ifndef TRAIN_H
  #define	TRAIN_H

#include <climits>
#include "trainRunner.h"
#include "Dijkstra.h"
#include "LinkedList.h"

class Train 
{
public:
  Graph network;
  Train(Station stations[], int numStations);
  void run(const Car cars[], int numCars, Action actions[], int *numActions);
}; //Train 
#endif
