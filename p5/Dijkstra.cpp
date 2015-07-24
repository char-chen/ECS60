#include "Dijkstra.h"

Graph::Graph(int v) : V(v)
{
	array = new AdjList[V];
  dist = new int[V];
  paths = new int[V];
}

Graph::~Graph()
{
  delete [] array;
  delete [] dist;
  delete [] paths;
}

void Graph::addEdge(int src, int dest, int weight)
{
	// Add an edge from src to dest. A new node is added to the adjacency
	// list of src. The node is added at the begining
	AdjListNode* newNode = new AdjListNode(dest, weight);
	newNode->next = array[src].head;
	array[src].head = newNode;

	// Aadd an edge from dest to src if graph is undirected
	//newNode = new AdjListNode(src, weight);
	//newNode->next = array[dest].head;
	//array[dest].head = newNode;
}

MinHeap::MinHeap(int cap) : size(0), capacity(cap)
{
	pos = new int[capacity];
	array = new MinHeapNode*[capacity];
}

MinHeap::~MinHeap()
{
  delete [] pos;
  
  for (int i = 0; i < capacity; ++i)
    delete [] array[i];

  delete [] array;
}
  
// A utility function to swap two nodes of min heap. Needed for min heapify
inline void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void MinHeap::minHeapify(int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < size && array[left]->distance < array[smallest]->distance)
	  smallest = left;

	if (right < size && array[right]->distance < array[smallest]->distance )
	  smallest = right;

	if (smallest != idx)
	{
		// The nodes to be swapped in min heap
		MinHeapNode *smallestNode = array[smallest];
		MinHeapNode *idxNode = array[idx];

		// Swap positions
		pos[smallestNode->v] = idx;
		pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&array[smallest], &array[idx]);
		minHeapify(smallest);
	}
}

// Standard function to extract minimum node from heap
MinHeapNode* MinHeap::extractMin()
{
	if (!size)
		return NULL;

	// Store the root node
	MinHeapNode* root = array[0];

	// Replace root node with last node
	MinHeapNode* lastNode = array[size - 1];
	array[0] = lastNode;

	// Update position of last node
	pos[root->v] = size-1;
	pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--size;
	minHeapify(0);

	return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void MinHeap::decreaseKey(int v, int dist)
{
	// Get the index of v in heap array
	int i = pos[v];

	// Get the node and update its dist value
	array[i]->distance = dist;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && array[i]->distance < array[(i - 1) / 2]->distance)
	{
		// Swap this node with its parent
		pos[array[i]->v] = (i-1)/2;
		pos[array[(i-1)/2]->v] = i;
		swapMinHeapNode(&array[i], &array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex 'v' is in min heap or not
bool MinHeap::isInMinHeap(int v)
{
  if (pos[v] < size)
	  return true;
  
  return false;
}

// The main function that calulates distances of shortest paths from src to all vertices.
// It is O(ELogV).
void Graph::dijkstra(int src)
{
	// minHeap represents set E
	MinHeap* minHeap = new MinHeap(V);

	// Initialize min heap with all vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v)
	{
    paths[v] = -1;
		dist[v] = INT_MAX;
		minHeap->array[v] = new MinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	// Make dist value of src vertex as 0 so that it is extracted first
	minHeap->array[src] = new MinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	minHeap->decreaseKey(src, dist[src]);

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the following loop, min heap contains all nodes
	// whose shortest distance is not yet finalized.
	while (minHeap->size)
	{
		// Extract the vertex with minimum distance value
		MinHeapNode* minHeapNode = minHeap->extractMin();
		int u = minHeapNode->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their distance values
		AdjListNode* pCrawl = array[u].head;
		
    while (pCrawl != NULL)
		{
			int v = pCrawl->destination;

			// If shortest distance to v is not finalized yet, and distance to v
			// through u is less than its previously calculated distance
			if (minHeap->isInMinHeap(v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
			{
        paths[v] = u;
				dist[v] = dist[u] + pCrawl->weight;

				// update distance value in min heap also
				minHeap->decreaseKey(v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}
}
