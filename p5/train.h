#ifndef TRAIN_H
#define	TRAIN_H
#include "trainRunner.h"

class Train {
  
public:
  Train(Station stations[], int numStations);
  void run(const Car cars[], int numCars, Action actions[], int *numActions);
}; // class train 

#endif	// TRAIN_H

