/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vlinkedlist.h
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#ifndef VIBRANT_LINKEDLIST_H
#define VIBRANT_LINKEDLIST_H

#include <list>

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the linked list data structure.
     * 
     * @author Chris Culy
     */
    template< typename T > class LinkedList
    {
        public:
            
            //*********************** Iterator Interface ***********************//

            /**
             * @brief Defines the linked list iterator type.
             * 
             * @author Chris Culy
             */
            template< typename V = T > class Iterator
            {
                public:
                    
                    /**
                     * @brief Constructor.
                     */
                    Iterator ()
                    {
                        /* stub function */
                    }
                    
                    /**
                     * @brief Destructor.
                     */
                    ~Iterator ()
                    {
                        /* stub fuynction */
                    }
                    
                    friend class LinkedList< T > ;

                    /**
                     * @brief Retreives the current linked list node object.
                     * 
                     * @return The object.
                     */
                    inline V GetObject ()
                    {
                        return *( this->iter );
                    }
                    
                    /**
                     * @brief Moves to the next position.
                     */
                    inline void Next ()
                    {
                        this->iter++;
                    }
                    
                    /**
                     * @brief Moves to the previous position.
                     */
                    inline void Previous ()
                    {
                        this->iter--;
                    }
                    
                    /**
                     * @brief Tests equality with another iterator.
                     * 
                     * @param iterator The iterator to compare with.
                     * @return <code>true</code> if the iterators point
                     *      to the same position;<code>false</code> otherwise.
                     */
                    inline bool operator== ( MSC_TYPENAME Iterator iterator )
                    {
                        return this->iter == iterator.iter;
                    }
                    
                    /**
                     * @brief Tests inequality with another iterator.
                     * 
                     * @param iterator The iterator to compare with.
                     * @return <code>true</code> if the iterators don't point
                     *      to the same position;<code>false</code> otherwise.
                     */
                    inline bool operator!= ( MSC_TYPENAME Iterator iterator )
                    {
                        return this->iter != iterator.iter;
                    }
                    
                private:
                    
                    /** @brief Holds the internal representation of the iterator. */
                    typename std::list< T >::iterator iter;
            };

            /**
             * @brief Retrieves a new linked list iterator
             * that points to the start of the linked list.
             * 
             * @return A linked list iterator that points to
             *      the start of the linked list.
             */
            Iterator< T > StartIterator () const;

            /**
             * @brief Retrieves a new linked list iterator
             * that points to one past the end of the linked list.
             * 
             * @return A linked list iterator that points to
             *      one past the end of the linked list.
             */
            Iterator< T > EndIterator () const;

            //*********************** Iterator Interface ***********************//
            

            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            LinkedList ();

            /**
             * @brief Destructor.
             */
            ~LinkedList ();

            /**
             * @brief Retrieves the back element of the linked list.
             * 
             * @return The back element of the linked list.
             */
            T& Back () const;

            /**
             * @brief Clears the linked list.
             */
            void Clear ();

            /**
             * @brief Retrieves the front element of the linked list.
             * 
             * @return The front element of the linked list.
             */
            T& Front () const;

            /**
             * @brief Inserts the given element at the given index.
             * 
             * @param element The element to insert.
             * @param index The index to insert at.
             */
            void Insert ( const T& element, const int index );

            /**
             * @brief Retrieves whether the linked list is empty or not.
             * 
             * @return <code>true</code> if the linked list is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Pushes the given element onto the
             * back of the linked list.
             * 
             * @param element The element to push.
             */
            void PushBack ( const T& element );

            /**
             * @brief Pops (removes and stores) the last
             * element of the linked list.
             * 
             * @param element The element used to store the popped element in.
             * @throws EmptyContainerException If the linked list is empty.
             */
            void PopBack ( T& element );

            /**
             * @brief Pushes the given element onto the
             * front of the linked list.
             * 
             * @param element The element to push.
             */
            void PushFront ( const T& element );

            /**
             * @brief Pops (removes and stores) the first
             * element of the linked list.
             * 
             * @param element The element used to store the popped element in.
             * @throws EmptyContainerException If the linked list is empty.
             */
            void PopFront ( T& element );

            /**
             * @brief Removes the element at the given index.
             * 
             * @param element The element to remove.
             */
            void Remove ( const T& element );

            /**
             * @brief Removes the element which the given iterator points to.
             * 
             * @param iter The iterator.
             */
            void Remove ( typename LinkedList::GNU_TEMPLATE Iterator< T > iter );

            /**
             * @brief Retreives the size of the linked list
             * (number of elements in the linked list).
             * 
             * @return The size of the linked list.
             */
            const int Size () const;

            //************************ General Interface ***********************//
            

            //**************************** Operators ***************************//

            /**
             * @brief Retrieves whether the list is equal to the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if the two lists are
             *      equal;<code>false</code> otherwise.
             */
            bool operator== ( const LinkedList& list ) const;

            /**
             * @brief Retrieves whether the list is not equal to the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if the two lists are
             *      not equal;<code>false</code> otherwise.
             */
            bool operator!= ( const LinkedList& list ) const;

            /**
             * @brief Retrieves whether the list is less
             * than or equal to the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if this list is less than
             *      or equal to the given list;<code>false</code> otherwise.
             */
            bool operator<= ( const LinkedList& list ) const;

            /**
             * @brief Retrieves whether the list is greater
             * than or equal to the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if this list is greater than
             *      or equal to the given list;<code>false</code> otherwise.
             */
            bool operator>= ( const LinkedList& list ) const;

            /**
             * @brief Retrieves whether the list is less than the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if this list is less than
             *      the given list;<code>false</code> otherwise.
             */
            bool operator< ( const LinkedList& list ) const;

            /**
             * @brief Retrieves whether the list is greater than the given list.
             * 
             * @param list The list to compare to.
             * @return <code>true</code> if this list is greater than
             *      the given list;<code>false</code> otherwise.
             */
            bool operator> ( const LinkedList& list ) const;

            /**
             * @brief Assigns the given list to this list.
             * 
             * @param list The list to assign to this list.
             * @return This list after it has been assigned to the given list.
             */
            LinkedList& operator= ( const LinkedList& list );

            //**************************** Operators ***************************//

        private:
            
            /** @brief Holds the internal representation of the linked list. */
            std::list< T >* val;
    };

    template< typename T > LinkedList< T >::LinkedList ()
    {
        this->val = new std::list< T > ();
    }
    
    template< typename T > LinkedList< T >::~LinkedList ()
    {
        if ( this->val != null )
        {
            delete this->val;
            this->val = null;
        }
    }
    
    template< typename T > T& LinkedList< T >::Back () const
    {
        return this->val->back ();
    }
    
    template< typename T > void LinkedList< T >::Clear ()
    {
        this->val->clear ();
    }
    
    template< typename T > T& LinkedList< T >::Front () const
    {
        return this->val->front;
    }
    
    template< typename T > void LinkedList< T >::Insert ( const T& element, const int index )
    {
        GNU_TYPENAME std::list< T >::iterator iter = this->val->begin ();
        for ( int i = 0; i < index; i++ )
        {
            iter++;
        }
        this->val->insert ( iter, element );
    }
    
    template< typename T > bool LinkedList< T >::IsEmpty () const
    {
        return this->val->empty ();
    }
    
    template< typename T > void LinkedList< T >::PushBack ( const T& element )
    {
        this->val->push_back ( element );
    }
    
    template< typename T > void LinkedList< T >::PopBack ( T& element )
    {
        element = this->back ();
        this->val->pop_back ();
    }
    
    template< typename T > void LinkedList< T >::PushFront ( const T& element )
    {
        this->val->push_front ( element );
    }
    
    template< typename T > void LinkedList< T >::PopFront ( T& element )
    {
        element = this->front ();
        this->val->pop_front ();
    }
    
    template< typename T > void LinkedList< T >::Remove ( const T& element )
    {
        this->val->remove ( element );
    }
    
    template< typename T > void LinkedList< T >::Remove ( typename LinkedList::GNU_TEMPLATE Iterator< T > iter )
    {
        this->val->erase ( iter.iter );
    }
    
    template< typename T > const int LinkedList< T >::Size () const
    {
        return this->val->size ();
    }
    
    template< typename T > bool LinkedList< T >::operator== ( const LinkedList& list ) const
    {
        return this->val == list.val;
    }
    
    template< typename T > bool LinkedList< T >::operator!= ( const LinkedList& list ) const
    {
        return this->val != list.val;
    }
    
    template< typename T > bool LinkedList< T >::operator<= ( const LinkedList& list ) const
    {
        return this->val <= list.val;
    }
    
    template< typename T > bool LinkedList< T >::operator>= ( const LinkedList& list ) const
    {
        return this->val >= list.val;
    }
    
    template< typename T > bool LinkedList< T >::operator< ( const LinkedList& list ) const
    {
        return this->val < list.val;
    }
    
    template< typename T > bool LinkedList< T >::operator> ( const LinkedList& list ) const
    {
        return this->val > list.val;
    }
    
    template< typename T > LinkedList< T >& LinkedList< T >::operator= ( const LinkedList& list )
    {
        this->val = list.val;
        return *this;
    }
    
    template< typename T > typename LinkedList< T >::GNU_TEMPLATE Iterator< > LinkedList< T >::StartIterator () const
    {
        GNU_TYPENAME LinkedList< T >::GNU_TEMPLATE Iterator< > iter;
        iter.iter = this->val->begin ();
        return iter;
    }
    
    template< typename T > typename LinkedList< T >::GNU_TEMPLATE Iterator< > LinkedList< T >::EndIterator () const
    {
        GNU_TYPENAME LinkedList< T >::GNU_TEMPLATE Iterator< > iter;
        iter.iter = this->val->end ();
        return iter;
    }

}

#endif
