/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vstack.h
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

#ifndef VIBRANT_STACK_H
#define VIBRANT_STACK_H

#include <stack>

#include "vexception.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the stack data structure.
     * 
     * @author Chris Culy
     */
    template< typename T > class Stack
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Stack ();

            /**
             * @brief Destructor.
             */
            ~Stack ();

            /**
             * @brief Retrieves whether the stack is empty or not.
             * 
             * @return <code>true</code> if the stack is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Pushes the given element onto the top of the stack.
             * 
             * @param element The element to push.
             */
            void Push ( const T& element );

            /**
             * @brief Pops the top element off the stack
             * and stores it in the given element.
             * 
             * @param element The element to store the
             *      popped element in.
             * @throws EmptyContainerException If the stack is empty.
             */
            void Pop ( T& element );

            /**
             * @brief Pops the top element off the stack
             * and throws it away.
             * 
             * @throws EmptyContainerException If the stack is empty.
             */
            void Pop ();

            /**
             * @brief Retreives the size of the stack
             * (number of elements in the stack).
             * 
             * @return The size of the stack (i.e. the number of elements).
             */
            const int Size () const;

            /**
             * @brief Retrieves the top element of the
             * stack without removing it.
             * 
             * @return The top element of the stack.
             */
            T& Top () const;

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the internal representation of the stack. */
            std::stack< T >* val;
    };

    template< typename T > Stack< T >::Stack ()
    {
        this->val = new std::stack< T > ();
    }
    
    template< typename T > Stack< T >::~Stack ()
    {
        if ( this->val != null )
        {
            delete this->val;
            this->val = null;
        }
    }
    
    template< typename T > bool Stack< T >::IsEmpty () const
    {
        return this->val->empty ();
    }
    
    template< typename T > void Stack< T >::Push ( const T& element )
    {
        this->val->push ( element );
    }
    
    template< typename T > void Stack< T >::Pop ( T& element )
    {
        // Make sure the stack is not empty.
        if ( this->IsEmpty () )
        {
            throw EmptyContainerException ( "Stack::Pop - Cannot pop from an empty stack." );
        }
        element = this->top ();
        this->val->pop ();
    }
    
    template< typename T > void Stack< T >::Pop ()
    {
        // Make sure the stack is not empty.
        if ( this->IsEmpty () )
        {
            throw EmptyContainerException ( "Stack::Pop - Cannot pop from an empty stack." );
        }
        this->val->pop ();
    }
    
    template< typename T > const int Stack< T >::Size () const
    {
        return this->val->size ();
    }
    
    template< typename T > T& Stack< T >::Top () const
    {
        // Make sure the stack is not empty.
        if ( this->IsEmpty () )
        {
            throw EmptyContainerException ( "Stack::Top - Cannot get the top element from an empty stack." );
        }
        return this->val->top ();
    }

}

#endif
