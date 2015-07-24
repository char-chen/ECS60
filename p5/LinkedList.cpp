#include "LinkedList.h"

template <class Object>
List<Object>::List( )
{
  header = new ListNode<Object>;
}

template <class Object>
List<Object>::~List( )
{
  makeEmpty( );
  delete header;
}

template <class Object>
bool List<Object>::isEmpty( ) const
{
  return header->next == NULL;
}

template <class Object>
void List<Object>::makeEmpty( )
{
  while( !isEmpty( ) )
    remove( first( ).retrieve( ) );
}

/**
 * Return an iterator representing the header node.
 */
template <class Object>
ListItr<Object> List<Object>::zeroth( ) const
{
    return ListItr<Object>( header );
}

/**
 * Return an iterator representing the first node in the list.
 * This operation is valid for empty lists.
 */
template <class Object>
ListItr<Object> List<Object>::first( ) const
{
    return ListItr<Object>( header->next );
}

/**
 * Insert item x after p.
 */
template <class Object>
void List<Object>::insert(const Object& x, const ListItr<Object>& p)
{
  if(p.current)
    p.current->next = new ListNode<Object>(x, p.current->next);
}

/**
 * Return iterator corresponding to the first node containing an item x.
 * Iterator isPastEnd if item is not found.
 */
template <class Object>
ListItr<Object> List<Object>::find( const Object & x ) const
{
    ListNode<Object> *itr = header->next;

    while( itr != NULL && itr->element != x )
        itr = itr->next;

    return ListItr<Object>( itr );
}

/**
 * Return iterator prior to the first node containing an item x.
 */
template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const
{
    ListNode<Object> *itr = header;

    while( itr->next != NULL && itr->next->element != x )
        itr = itr->next;

    return ListItr<Object>( itr );
}

/**
 * Remove the first occurrence of an item x.
 */
template <class Object>
void List<Object>::remove( const Object & x )
{
    ListItr<Object> p = findPrevious( x );

    if( p.current->next != NULL )
    {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;  // Bypass deleted node
        delete oldNode;
    }
}
