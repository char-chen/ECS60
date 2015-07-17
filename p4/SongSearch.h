#ifndef SONGSEARCH_H
#define	SONGSEARCH_H

#include "SearchRunner.h"
#include "LinkedList.h"
#include "SkipList.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SplayTree.h"
#include "BinaryHeap.h"
#include <cstring>

class SongSearch 
{
private:
  List<Song> *list;
  SkipList<Song> *skip;
  BinarySearchTree<Song> *bst;
  AvlTree<Song> *avl;
  SplayTree<Song> *splay;
  BinaryHeap<Song> *heap;
public:
  SongSearch(const Song *songs, int songCount);
  void query(const Request &request, Song answer[], int *answerCount);
  ~SongSearch();
}; // class SongSearch 
#endif	// SONGSEARCH_H
