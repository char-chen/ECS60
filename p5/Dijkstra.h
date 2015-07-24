#ifndef DIJKSTRA_H
  #define DIJKSTRA_H

#include <cstdlib>
#include <climits>
#include "trainRunner.h"

class AdjListNode
{
public:
	int destination;
	int weight;
	AdjListNode* next;
  AdjListNode(int d, int w) : destination(d), weight(w), next(NULL) {}
};

class AdjList
{
public:
	AdjListNode *head; // pointer to head node of list
  AdjList() : head(NULL) {}
};

class Graph
{
public:
	int V;
  int *dist;
  int *paths;
	AdjList* array; 
  Graph(int v);
  ~Graph();
  void addEdge(int source, int destination, int weight);
  void dijkstra(int src);
  void printArr();
};

class MinHeapNode
{
public:
	int v;
	int distance;
  MinHeapNode(int vert, int dist) : v(vert), distance(dist) {}
};

class MinHeap
{
public:
	int size;	 // Number of heap nodes present currently
	int capacity; // Capacity of min heap
	int *pos;	 // For decreaseKey()
	MinHeapNode **array;
  MinHeap(int cap);
  ~MinHeap();
  void minHeapify(int index);
  bool isInMinHeap(int v);
  MinHeapNode* extractMin();
  void decreaseKey(int v, int dist);
};
#endif
