/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vqueue.h
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

#ifndef VIBRANT_QUEUE_H
#define VIBRANT_QUEUE_H

#include <queue>

namespace Vibrant
{
    
    /**
     * @brief Implements the queue data structure.
     * 
     * @author Chris Culy
     */
    template< typename T > class Queue
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Queue ();

            /**
             * @brief Destructor.
             */
            ~Queue ();

            /**
             * @brief Retrieves the back element of the queue.
             * 
             * @return The back element of the queue.
             */
            T& Back () const;

            /**
             * @brief Retrieves the front element of the queue.
             * 
             * @return The front element of the queue.
             */
            T& Front () const;

            /**
             * @brief Retrieves whether the queue is empty.
             * 
             * @return <code>true</code> if the queue is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Pops the front element off the queue
             * and stores it in the given element.
             * 
             * @param element The element to store the
             *      popped element in.
             * @throws EmptyContainerException If the queue is empty.
             */
            void Pop ( T& element );

            /**
             * @brief Pushs a new element on the back of the queue.
             * 
             * @param element The element to push onto the queue.
             */
            void Push ( const T& element );

            /**
             * @brief Retrieves the size of the queue (the number of elements).
             * 
             * @return The size of the queue.
             */
            const int Size () const;

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the internal representation of the queue. */
            std::queue< T >* val;
    };
    
    template< typename T > Queue< T >::Queue ()
    {
        this->val = new std::queue< T > ();
    }
    
    template< typename T > Queue< T >::~Queue ()
    {
        if ( this->val != null )
        {
            delete this->val;
        }
    }
    
    template< typename T > T& Queue< T >::Back () const
    {
        return this->back ();
    }
    
    template< typename T > T& Queue< T >::Front () const
    {
        return this->front ();
    }
    
    template< typename T > bool Queue< T >::IsEmpty () const
    {
        return this->val->empty ();
    }
    
    template< typename T > void Queue< T >::Pop ( T& element )
    {
        // Make sure the queue is not empty.
        if ( this->IsEmpty () )
        {
            throw EmptyContainerException ( "Queue::Pop - Cannot pop from an empty queue." );
        }
        element = this->front ();
        this->val->pop ();
    }
    
    template< typename T > void Queue< T >::Push ( const T& element )
    {
        this->val->push ( element );
    }
    
    template< typename T > const int Queue< T >::Size () const
    {
        return this->val->size ();
    }

}

#endif
