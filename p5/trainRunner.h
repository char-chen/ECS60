// Author: Sean Davis

#ifndef TRAINRUNNER_H
#define	TRAINRUNNER_H

class Station
{
  public:
  int adjacent[10];
  int adjCount;
  int distances[10];
  Station():adjCount(0){}
};

class Car
{
public:
  int destination;
  int source;
};

typedef enum {MOVE, PICKUP, DROPOFF} ActionType;

class Action
{
public:
  ActionType actionType;
  int stationOrCar;
};


#endif	/* TRAINRUNNER_H */

