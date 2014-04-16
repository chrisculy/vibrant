/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: varray.h
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

#ifndef VIBRANT_ARRAY_H
#define VIBRANT_ARRAY_H

#include "vsystem.h"

// Log warnings for invalid indices in debug mode.
#ifdef _DEBUG
#include "vlog.h"
#endif

#include "vexception.h"
#include "vpointable.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the array (or "smart array"/vector) data structure.
     * 
     * @see Pointable
     * @author Chris Culy
     */
    template< typename T > class Array : public Pointable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs an array from an array of type T.
             * 
             * <p>
             * Note: If elements is <code>null</code>, then
             * an array of size elementCount is constructed
             * using the default constructor for type T.
             * </p>
             * 
             * <p>
             * <b>Note:</b> If <code>elementCount</code> is not
             * correct, this may cause: 1) only part of the <code>elements</code>
             * to be copied, or 2) illegal memory access beyond the
             * actual end of <code>elements</code>.
             * </p>
             * 
             * @param elementCount The number of elements in the array.
             * @param elements The elements of the array.
             * @throws IllegalArgumentException If elementCount is zero.
             */
            Array ( int elementCount = 0, T* elements = null );

            /**
             * @brief Copy constructor.
             * 
             * <p>
             * Performs a true copy (element-by-element).
             * </p>
             * 
             * <p>
             * Note that this does not throw a NullPointerException
             * as it is valid to set an array to null.
             * </p>
             * 
             * @param varray The array to copy/point to.
             */
            Array ( const Array& varray );

            /**
             * @brief Destructor.
             */
            ~Array ();

            /**
             * @brief Retrieves the element at the given index.
             * 
             * @param index The index of the desired item.
             * @return The specified item.
             */
            const T& At ( const int index ) const;

            /**
             * @brief Retrieves the element at the given index.
             * 
             * @param index The index of the desired item.
             * @return The specified item.
             */
            T& At ( const int index );

            /**
             * @brief Retreives the capacity of the array
             * (number of elements the array could hold).
             * 
             * @return The capacity of the array.
             */
            const int Capacity () const;

            /**
             * @brief Clears the array.
             */
            void Clear ();

            /**
             * @brief Inserts the given element into the array at the given index.
             * 
             * @param element The element to insert.
             * @param index The index to insert at.
             * @throw IndexOutOfBoundsException If <code>index</code> &lt; 0 or
             *      <code>index</code> &gt; Size ().
             */
            void Insert ( const T& element, const int index );

            /**
             * @brief Retrieves whether the array is empty or not.
             * 
             * @return <code>true</code> if the array is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Pushes the given element onto the
             * end of the array list.
             * 
             * @param element The element to push.
             */
            void Push ( const T& element );

            /**
             * @brief Pops the last element off the array list
             * and stores it in the given element.
             * 
             * @param element The element to store the
             *      popped element in.
             * @throws EmptyContainerException If the array is empty.
             */
            void Pop ( T& element );

            /**
             * @brief Removes the element at the given index.
             * 
             * @param index The index of the element to remove.
             */
            void Remove ( const int index );

            /**
             * @brief Retreives the size of the array
             * (number of elements in the array).
             * 
             * @return The size of the array (i.e. the number of elements).
             */
            const int Size () const;

            //************************ General Interface ***********************//
            

            //**************************** Operators ***************************//

            /**
             * @brief Accessor operator (checked).
             * 
             * <p>
             * This allows an Array to be used like a normal array,
             * except that the index is clamped to the valid
             * range (i.e. if it is past the last index, we
             * return the last item; if it is before the first
             * index (< 0), we return the first item.)
             * </p>
             * 
             * @param index The index of the desired item.
             * @return The specified item.
             */
            T& operator[] ( int index );

            /**
             * @brief Accessor operator (checked).
             * 
             * <p>
             * This allows an Array to be used like a normal array,
             * except that the index is clamped to the valid
             * range (i.e. if it is past the last index, we
             * return the last item; if it is before the first
             * index (< 0), we return the first item.)
             * </p>
             * 
             * @param index The index of the desired item.
             * @return The specified item.
             */
            const T& operator[] ( int index ) const;

            /**
             * @brief Implicit conversion to a normal array.
             */
            operator T* ();

            /**
             * @brief Implicit conversion to a normal array.
             */
            operator const T* () const;

            /**
             * @brief Assignment operator.
             * 
             * @param varray The array to copy/point to.
             */
            Array& operator= ( const Array& varray );

            //**************************** Operators ***************************//

        private:
            
            /** @brief Holds the default number of elements to add
             * to the array when reallocating memory. */
            static const int DEFAULT_ALLOCATION_SIZE = 16;

            /** @brief Holds the number of elements in the array. */
            int elementCount;

            /** @brief Holds the capacity of the array. */
            int elementCapacity;

            /** @brief Holds the actual elements of the array. */
            T* elements;
    };

    template< typename T > Array< T >::Array ( int elementCount, T* elements )
    {
        this->elementCount = elementCount;
        this->elementCapacity = elementCount;
        this->elements = new T[ elementCount ];
        if ( elements != null )
        {
            for ( int i = 0; i < this->elementCount; i++ )
            {
                this->elements[ i ] = elements[ i ];
            }
        }
    }
    
    template< typename T > Array< T >::Array ( const Array& varray )
    {
        this->elementCount = varray.Size ();
        this->elementCapacity = this->elementCount;
        this->elements = new T[ this->elementCount ];
        for ( int i = 0; i < this->elementCount; i++ )
        {
            this->elements[ i ] = varray[ i ];
        }
    }
    
    template< typename T > Array< T >::~Array ()
    {
        if ( this->elements != null )
        {
            delete[] this->elements;
            this->elements = null;
        }
    }
    
    template< typename T > const T& Array< T >::At ( const int index ) const
    {
        return this->operator[] ( index );
    }
    
    template< typename T > T& Array< T >::At ( const int index )
    {
        return this->operator[] ( index );
    }
    
    template< typename T > const int Array< T >::Capacity () const
    {
        return this->elementCapacity;
    }
    
    template< typename T > void Array< T >::Clear ()
    {
        this->elementCount = 0;
        this->elementCapacity = 0;
        if ( this->elements != null )
        {
            delete[] this->elements;
            this->elements = null;
        }
        this->elements = new T[ this->elementCount ];
    }
    
    template< typename T > void Array< T >::Insert ( const T& element, const int index )
    {
        // Make sure the index is valid.
        if ( index > this->elementCount )
        {
            throw IndexOutOfBoundsException ( "Array::Insert - The index must be in the range from 0 to the size of the array (inclusive)." );
        }
        
        // Check if we are inserting at the beginning of the array.
        if ( index == 0 )
        {
            this->elementCount++;
            
            // Resize the array if needed.
            if ( this->elementCount > this->elementCapacity )
            {
                this->elementCapacity += DEFAULT_ALLOCATION_SIZE;
                T* newElements = new T[ this->elementCapacity ];
                
                // Insert the element into the array.
                newElements[ 0 ] = element;
                
                // Copy in the rest of the elements.
#ifdef _MSC_VER
                memcpy_s ( &newElements[ 1 ], this->elementCount * sizeof ( T ), this->elements, this->elementCount * sizeof ( T ) );
#else
                memcpy ( &newElements[ 1 ], this->elements, this->elementCount * sizeof(T) );
#endif
                
                // Clean up the old array of elements.
                if ( this->elements != null )
                {
                    delete[] this->elements;
                    this->elements = null;
                }
                this->elements = newElements;
            }
        }
        // Check if we are inserting at the end of the array.
        else if ( index == this->elementCount )
        {
            this->Push ( element );
        }
        else
        {
            this->elementCount++;
            
            // Resize the array if needed.
            if ( this->elementCount > this->elementCapacity )
            {
                this->elementCapacity += DEFAULT_ALLOCATION_SIZE;
                T* newElements = new T[ this->elementCapacity ];
                
                // Fill in the new array.
#ifdef _MSC_VER
                memcpy_s ( newElements, index * sizeof ( T ), this->elements, index * sizeof ( T ) );
                newElements[ index ] = element;
                memcpy_s ( &newElements[ index + 1], ( this->elementCount - ( index + 1 ) ) * sizeof ( T ),
                    &this->elements[ index ], ( this->elementCount - ( index + 1 ) ) * sizeof ( T ) );
#else
                memcpy ( newElements, this->elements, index * sizeof(T) );
                newElements[ index ] = element;
                memcpy ( &newElements[ index + 1 ], &this->elements[ index ], ( this->elementCount - ( index + 1 ) ) * sizeof(T) );
#endif
                
                // Clean up the old array of elements.
                if ( this->elements != null )
                {
                    delete[] this->elements;
                    this->elements = null;
                }
                this->elements = newElements;
            }
            else
            {
                for ( int i = this->elementCount; i > index; i++ )
                {
                    if ( i == index )
                    {
                        // Insert the element into the array.
                        this->elements[ i ] = element;
                    }
                    else
                    {
                        this->elements[ i ] = this->elements[ i - 1 ];
                    }
                }
            }
        }
    }
    
    template< typename T > bool Array< T >::IsEmpty () const
    {
        return ( this->Size () == 0 );
    }
    
    template< typename T > void Array< T >::Push ( const T& element )
    {
        this->elementCount++;
        
        // Resize the array if needed.
        if ( this->elementCount > this->elementCapacity )
        {
            this->elementCapacity += DEFAULT_ALLOCATION_SIZE;
            T* newElements = new T[ this->elementCapacity ];
#ifdef _MSC_VER
            memcpy_s ( newElements, ( this->elementCount - 1 ) * sizeof ( T ), this->elements,
                ( this->elementCount - 1 ) * sizeof ( T ) );
#else
            memcpy ( newElements, this->elements, ( this->elementCount - 1 ) * sizeof(T) );
#endif
            
            // Clean up the old array of elements.
            if ( this->elements != null )
            {
                delete[] this->elements;
                this->elements = null;
            }
            this->elements = newElements;
        }
        
        // Put the element in its proper place in the array.
        this->elements[ this->elementCount - 1 ] = element;
    }
    
    template< typename T > void Array< T >::Pop ( T& element )
    {
        // Make sure the array has something in it.
        if ( !this->IsEmpty () )
        {
            // This will disallow the element from being accessed again,
            // but we don't actually remove it from memory.
            this->elementCount--;
            
            // Resize the array if needed.
            if ( this->elementCount < ( this->elementCapacity - ( 2 * DEFAULT_ALLOCATION_SIZE ) ) )
            {
                this->elementCapacity -= DEFAULT_ALLOCATION_SIZE;
                T* newElements = new T[ this->elementCapacity ];
#ifdef _MSC_VER
                memcpy_s ( newElements, this->elementCount * sizeof ( T ), this->elements, this->elementCount * sizeof ( T ) );
#else
                memcpy_s ( newElements, this->elements, this->elementCount * sizeof(T) );
#endif
                for ( int i = 0; i < this->elementCount; i++ )
                {
                    newElements[ i ] = this->elements[ i ];
                }

                // Clean up the old array of elements.
                if ( this->elements != null )
                {
                    delete[] this->elements;
                    this->elements = null;
                }
                this->elements = newElements;
            }
            
            // Return the popped element.
            element = this->elements[ this->elementCount ];
        }
        // The array is empty.
        else
        {
            throw EmptyContainerException ( "Array::Pop - Cannot pop elements from an empty array." );
        }
    }
    
    template< typename T > void Array< T >::Remove ( const int index )
    {
        // Check if the index is valid.
        if ( index < this->elementCount )
        {
            this->elementCount--;
            for ( int i = index; i < this->elementCount; i++ )
            {
                this->elements[ i ] = this->elements[ i + 1 ];
            }
        }
    }
    
    template< typename T > const int Array< T >::Size () const
    {
        return this->elementCount;
    }
    
    template< typename T > T& Array< T >::operator[] ( int index )
    {
        // Clamp the index to valid values.
        if ( index < 0 )
        {
            index = 0;
            
#ifdef _DEBUG
            //vlog << WARN << "Attempting to access a negative index in an Array object.\n";
#endif
        }
        else if ( index > this->elementCount - 1 )
        {
            index = elementCount - 1;
            
#ifdef _DEBUG
            //vlog << WARN << "Attempting to access a index past the end of an Array object.\n";
#endif
        }
        
        return this->elements[ index ];
    }
    
    template< typename T > const T& Array< T >::operator[] ( int index ) const
    {
        // Clamp the index to valid values.
        if ( index < 0 )
        {
            index = 0;
            
#ifdef _DEBUG
            //vlog << WARN << "Attempting to access a negative index in an Array object.\n";
#endif
        }
        else if ( index > this->elementCount - 1 )
        {
            index = elementCount - 1;
            
#ifdef _DEBUG
            //vlog << WARN << "Attempting to access a index past the end of an Array object.\n";
#endif
        }
        
        return this->elements[ index ];
    }
    
    template< typename T > Array< T >::operator T* ()
    {
        return elements;
    }
    
    template< typename T > Array< T >::operator const T* () const
    {
        return elements;
    }
    
    template< typename T > Array< T >& Array< T >::operator= ( const Array& varray )
    {
        // Clean up the old array of elements.
        if ( this->elements != null )
        {
            delete[] this->elements;
            this->elements = null;
        }

        this->elementCount = varray.Size ();
        this->elementCapacity = this->elementCount;
        this->elements = new T[ elementCount ];
        for ( int i = 0; i < this->elementCount; i++ )
        {
            this->elements[ i ] = varray[ i ];
        }
        
        return *this;
    }

}

#endif 
