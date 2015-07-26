#ifndef _LinkedList_H
  #define _LinkedList_H

#include "dsexceptions.h"
#include <iostream>

using namespace std;

template <class Object>
class List;

template <class Object>
class ListItr;

template <class Object>
class ListNode
{
  public:
    ListNode(const Object& theElement = Object(), ListNode * n = NULL)
      : element(theElement), next(n) {}

    Object element;
    ListNode *next;
    
    friend class List<Object>;
    friend class ListItr<Object>;
};


template <class Object>
class List
{
  public:
    int count;
    ListNode<Object> *header;
    List();
    ~List();
    bool isEmpty( ) const;
    void makeEmpty( );
    ListItr<Object> zeroth( ) const;
    ListItr<Object> first( ) const;
    void insert(const Object& x, const ListItr<Object> & p);
    ListItr<Object> find(const Object& x ) const;
    ListItr<Object> findPrevious(const Object & x ) const;
    void remove(const Object & x);
};

template <class Object>
class ListItr
{
  public:
    ListItr() : current(NULL) {}
    
    bool isPastEnd( ) const 
    { 
      return current == NULL; 
    }
    
    void advance( ) 
    { 
      if( !isPastEnd( ) ) 
        current = current->next; 
    }
    
    const Object & retrieve( ) const
    { 
      if( isPastEnd() ) throw BadIterator( );
        return current->element; 
    }

  
    ListNode<Object> *current;    // Current position

    ListItr( ListNode<Object> *theNode )
      : current( theNode ) { }

    friend class List<Object>; // Grant access to constructor
};
#include "LinkedList.cpp"
#endif
