/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vpointer.h
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

#ifndef VIBRANT_POINTER_H
#define VIBRANT_POINTER_H

#include "vexception.h"

namespace Vibrant
{
    
    /**
     * @brief Implements a smart pointer system.
     * 
     * <p>
     * Classes that want to use this system must implement:
     * <ul>
     *  <li><code>void AddReference ()</code></li>
     *  <li><code>void RemoveReference ()</code></li>
     *  <li><code>const int ReferenceCount ()</code></li>
     * </ul>
     * <br>
     * Alternatively, a class can derive from Pointable
     * which provides the above interface.
     * </p>
     * 
     * @author Chris Culy
     */
    template< typename T > class Pointer
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs a smart pointer from a normal pointer.
             * 
             * @param ptr The object to store a pointer to.
             */
            Pointer ( T* ptr = null );

            /**
             * @brief Constructs a smart pointer from another smart pointer.
             * 
             * @param ptr The pointer to copy.
             */
            Pointer ( const Pointer& ptr );

            /**
             * @brief Destructor.
             * 
             * <p>
             * Note: This is virtual to allow the smart pointer to continue
             * to function properly even if a class were to be
             * derived from Pointer. The destructor decrements the
             * number of references to the obj (potentially destroying
             * the actual object if the number of references reaches zero)
             * if the obj still exists. Thus, this function needs to be
             * virtual in order to make sure that the number of references
             * is handled properly even for derived classes.
             * </p>
             */
            virtual ~Pointer ();

            /**
             * @brief Retreives if the pointer is valid (i.e. non-null).
             * 
             * @return <code>true</code> if the pointer is
             *      valid;<code>false</code>otherwise.
             */
            bool IsValid ();

            //************************ General Interface ***********************//
            

            //*********************** Implicit Conversion **********************//

            /**
             * @brief Provides implicit conversion to a normal pointer.
             */
            operator T* () const
            {
                return obj;
            }
            
            /**
             * @brief Provides implicit conversion to a reference through
             * the normal pointer dereference operator.
             * 
             * @throws NullPointerException If <code>obj</code> is null.
             */
            T& operator* () const;

            /**
             * @brief Provides implicit conversion to a pointer accessing
             * a member through the normal pointer operator.
             * 
             * @throws NullPointerException If <code>obj</code> is null.
             */
            T* operator-> () const;

            //*********************** Implicit Conversion **********************//
            

            //*********************** Assignment Operators *********************//

            /**
             * @brief Allows assignment of a normal pointer to a smart pointer.
             * 
             * @param ptr The pointer to assign to this pointer.
             * @return The newly assigned smart pointer.
             */
            Pointer& operator= ( T* ptr );

            /**
             * @brief Allows assignment of a smart pointer to another smart pointer.
             * 
             * @param ptr The pointer to assign to this pointer.
             * @return The newly assigned smart pointer.
             */
            Pointer& operator= ( const Pointer& ptr );

            /**
             * @brief Allows assignment of a smart pointer from an int.
             * Note that this just assumes the int to be 0
             * and sets the pointer to null.
             * 
             * @param integer The given integer (assumed to be zero).
             */
            Pointer& operator= ( int integer );

            //*********************** Assignment Operators *********************//
            

            //********************* (In)Equality Operators *********************//

            /**
             * @brief Tests equality between a smart and normal pointer.
             * 
             * @returns <code>true</code> if they are equal; <code>false</code>
             *      otherwise.
             */
            bool operator== ( T* ptr ) const;

            /**
             * @brief Tests inequality between a smart and normal pointer.
             * 
             * @returns <code>true</code> if they are not equal; <code>false</code>
             *      otherwise.
             */
            bool operator!= ( T* ptr ) const;

            /**
             * @brief Tests equality between two smart pointers.
             * 
             * @returns <code>true</code> if they are equal; <code>false</code>
             *      otherwise.
             */
            bool operator== ( const Pointer& ptr ) const;

            /**
             * @brief Tests inequality between two smart pointers.
             * 
             * @returns <code>true</code> if they are not equal; <code>false</code>
             *      otherwise.
             */
            bool operator!= ( const Pointer& ptr ) const;

            //********************* (In)Equality Operators *********************//

        protected:
            
            /** @brief Holds the actual normal pointer. */
            T* obj;
    };
    
    template< typename T > Pointer< T >::Pointer ( T* ptr )
    {
        // Increment the number of references to the
        // specified object and set this pointer to
        // point to it.
        if ( ptr != null )
        {
            ptr->AddReference ();
        }
        this->obj = ptr;
    }
    
    template< typename T > Pointer< T >::Pointer ( const Pointer< T >& ptr )
    {
        // Increment the number of references to the
        // specified object and set this pointer to
        // point to it.
        if ( ptr.obj != null )
        {
            ptr.obj->AddReference ();
        }
        this->obj = ptr.obj;
    }
    
    template< typename T > Pointer< T >::~Pointer ()
    {
        // Decrement the number of references
        // to the object this pointer is
        // currently pointing to and delete
        // if no one else is using it.
        if ( obj != null )
        {
            obj->RemoveReference ();
            if ( obj->ReferenceCount () == 0 )
            {
                delete obj;
                obj = null;
            }
        }
    }
    
    template< typename T > bool Pointer< T >::IsValid ()
    {
        return obj != null;
    }
    
    template< typename T > T& Pointer< T >::operator* () const
    {
        if ( obj == null )
        {
            throw NullPointerException ( "Pointer::operator* - Attempting to dereference a null object." );
        }
        return *( this->obj );
    }
    
    template< typename T > T* Pointer< T >::operator-> () const
    {
        if ( obj == null )
        {
            throw NullPointerException ( "Pointer::operator-> - Attempting to access a member of a null object." );
        }
        return this->obj;
    }
    
    template< typename T > Pointer< T >& Pointer< T >::operator= ( T* ptr )
    {
        // Decrement the number of references
        // to the object this pointer is
        // currently pointing to and delete
        // if no one else is using it.
        if ( obj != null )
        {
            obj->RemoveReference ();
            if ( obj->ReferenceCount () == 0 )
            {
                delete obj;
                obj = null;
            }
        }

        // Increment the number of references to the
        // specified object and set this pointer to
        // point to it.
        if ( ptr != null )
        {
            ptr->AddReference ();
        }
        this->obj = ptr;
        
        return *this;
    }
    
    template< typename T > Pointer< T >& Pointer< T >::operator= ( const Pointer< T >& ptr )
    {
        // Decrement the number of references
        // to the object this pointer is
        // currently pointing to and delete
        // if no one else is using it.
        if ( obj != null )
        {
            obj->RemoveReference ();
            if ( obj->ReferenceCount () == 0 )
            {
                delete obj;
                obj = null;
            }
        }

        // Increment the number of references to the
        // specified object and set this pointer to
        // point to it.
        if ( ptr.obj != null )
        {
            ptr.obj->AddReference ();
        }
        this->obj = ptr.obj;
        
        return *this;
    }
    
    template< typename T > Pointer< T >& Pointer< T >::operator= ( int integer )
    {
        integer = 0;
        
        // Decrement the number of references
        // to the object this pointer is
        // currently pointing to and delete
        // if no one else is using it.
        if ( obj != null )
        {
            obj->RemoveReference ();
            if ( obj->ReferenceCount () == 0 )
            {
                delete obj;
                obj = null;
            }
        }

        this->obj = null;
        
        return *this;
    }
    
    template< typename T > bool Pointer< T >::operator== ( T* ptr ) const
    {
        return this->obj == ptr;
    }
    
    template< typename T > bool Pointer< T >::operator!= ( T* ptr ) const
    {
        return this->obj != ptr;
    }
    
    template< typename T > bool Pointer< T >::operator== ( const Pointer< T >& ptr ) const
    {
        return this->obj == ptr.obj;
    }
    
    template< typename T > bool Pointer< T >::operator!= ( const Pointer< T >& ptr ) const
    {
        return this->obj != ptr.obj;
    }

}

#endif
