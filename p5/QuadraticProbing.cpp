#include "QuadraticProbing.h"


/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
template <class HashedObj>
bool QuadraticHashTable<HashedObj>::isPrime( int n ) const
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
template <class HashedObj>
int QuadraticHashTable<HashedObj>::nextPrime( int n ) const
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

/**
 * Construct the hash table.
 */
template <class HashedObj>
QuadraticHashTable<HashedObj>::QuadraticHashTable( const HashedObj & notFound, int size )
  : array( nextPrime( size ) ), currentSize(0), count(0), ITEM_NOT_FOUND( notFound )
{
    makeEmpty( );
}

/**
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */
template <class HashedObj>
void QuadraticHashTable<HashedObj>::insert( const HashedObj & x )
{
    count++;
        // Insert x as active
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        return;
    array[ currentPos ] = HashEntry( x, ACTIVE );
        // Rehash; see Section 5.5
    //if( ++currentSize > array.size( ) / 2 )
        //rehash( );
}

/**
 * Expand the hash table.
 */
template <class HashedObj>
void QuadraticHashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;
    count--;
        // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for( int j = 0; j < array.size( ); j++ )
        array[ j ].info = EMPTY;

        // Copy table over
    currentSize = 0;
    for( int i = 0; i < oldArray.size( ); i++ )
        if( oldArray[ i ].info == ACTIVE )
            insert( oldArray[ i ].element );
}

/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int QuadraticHashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int collisionNum = 0;
    int currentPos = hash( x, array.size( ) );

    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
        if( currentPos >= array.size( ) )
            currentPos -= array.size( );
    }

    return currentPos;
}


/**
 * Remove item x from the hash table.
 */
template <class HashedObj>
void QuadraticHashTable<HashedObj>::remove( const HashedObj & x )
{
  count--;
  currentSize--;
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        array[ currentPos ].info = DELETED;
}

/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
template <class HashedObj>
const HashedObj & QuadraticHashTable<HashedObj>::find( const HashedObj & x ) const
{
    int currentPos = findPos( x );
    return isActive( currentPos ) ? array[ currentPos ].element : ITEM_NOT_FOUND;
}

/**
 * Make the hash table logically empty.
 */
template <class HashedObj>
void QuadraticHashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < array.size( ); i++ )
        array[ i ].info = EMPTY;
}

/**
 * Return true if currentPos exists and is active.
 */
template <class HashedObj>
bool QuadraticHashTable<HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}

/**
 * A hash routine for ints.
 */
 template <class HashedObj>
int QuadraticHashTable<HashedObj>::hash( int key, int tableSize ) const
{
    if( key < 0 ) key = -key;
    return key % tableSize;
}
