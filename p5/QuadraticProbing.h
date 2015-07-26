#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include "vector.h"

template <class HashedObj>
class QuadraticHashTable
{
public:
  explicit QuadraticHashTable( const HashedObj & notFound, int size = 101);
  const HashedObj& find( const HashedObj & x ) const;

  void makeEmpty( );
  void insert( const HashedObj& x );
  void remove( const HashedObj & x );

  const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

  enum EntryType { ACTIVE, EMPTY, DELETED };
  
  struct HashEntry
  {
    HashedObj element;
    EntryType info;

    HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
      : element( e ), info( i ) { }
  };
  
  vector<HashEntry> array;
  int currentSize;
  int count;
  const HashedObj ITEM_NOT_FOUND;
  bool isPrime( int n ) const;
  int nextPrime( int n ) const;
  bool isActive( int currentPos ) const;
  int findPos( const HashedObj & x ) const;
  int hash( int key, int tableSize ) const;
  void rehash( );
};
#include "QuadraticProbing.cpp"
#endif
