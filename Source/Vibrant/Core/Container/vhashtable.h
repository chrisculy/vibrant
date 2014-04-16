/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vhashtable.h
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

#ifndef VIBRANT_HASHTABLE_H
#define VIBRANT_HASHTABLE_H

#include <map>

#include "vexception.h"
#include "vsystem.h"

#ifdef _DEBUG
#include "vlog.h"
#endif

namespace Vibrant
{
    
    /**
     * @brief Implements the hashtable data structure.
     * 
     * <p>
     * Note: This is currently implemented using a
     * map, so this is not technically a true hashtable
     * and may not be as optimized as a true hashtable.
     * </p>
     * 
     * @author Chris Culy
     */
    template< typename T, typename U > class Hashtable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Hashtable ();

            /**
             * @brief Destructor.
             */
            ~Hashtable ();

            /**
             * @brief Clears the hashtable.
             */
            void Clear ();

            /**
             * @brief Retrieves whether there is a value
             * associated with the given key.
             * 
             * @param key The key.
             * @return <code>true</code> if there is a value associated
             *      with the given key;<code>false</code> otherwise.
             */
            bool Contains ( const T& key ) const;

            /**
             * @brief Retrieves the value associated with the given key.
             * 
             * @param key The key.
             * @return A pointer to the value associated with the given key.
             * @throws IllegalArgumentException If the key does not exist.
             */
            const U& Get ( const T& key ) const;

            /**
             * @brief Retrieves the value associated with the given key.
             * 
             * @param key The key.
             * @return A pointer to the value associated with the given key.
             * @throws IllegalArgumentException If the key does not exist.
             */
            U& Get ( const T& key );

            /**
             * @brief Retrieves whether the hashtable is empty or not.
             * 
             * @return <code>true</code> if the hashtable is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Puts the key, value pair into the table.
             * 
             * @param key The key.
             * @param val The value.
             * @throws IllegalArgumentException If the key already
             *      exists in the table.
             */
            void Put ( const T& key, const U& val );

            /**
             * @brief Removes the element with the given key.
             * 
             * @param key The key of the element to remove.
             */
            void Remove ( const T& key );

            /**
             * @brief Returns the size of the hashtable (the number of elements).
             * 
             * @return The hashtable's size.
             */
            const int Size () const;

            /**
             * @brief Allows assignment of one hashtable to another.
             * 
             * @param hashtable The hashtable to assign to this one.
             * @return This hashtable after assignment has occurred.
             */
            Hashtable& operator= ( const Hashtable& hashtable );

            //************************ General Interface ***********************//
            

            //*********************** Iterator Interface ***********************//

            /**
             * @brief Defines the hashtable iterator type.
             * 
             * @author Chris Culy
             */
            template< typename V = T, typename W = U > class Iterator
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
                    
                    friend class Hashtable< V, W > ;

                    /**
                     * @brief Retrieves the key of the current (key, value) pair.
                     * 
                     * @return The key.
                     */
                    inline V GetKey ()
                    {
                        return this->iter->first;
                    }
                    
                    /**
                     * @brief Retreives the value of the current (key, value) pair.
                     * 
                     * @return The value.
                     */
                    inline W GetValue ()
                    {
                        return this->iter->second;
                    }
                    
                    /**
                     * @brief Moves to the next position.
                     */
                    inline void Next ()
                    {
                        this->iter++;
                    }
                    
                    /**
                     * @brief  Moves to the previous position.
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
                    typename std::map< V, W >::iterator iter;
            };

            /**
             * @brief Retrieves a new hashtable iterator
             * that points to the start of the hashtable.
             * 
             * @return A hashtable iterator that points to
             *      the start of the hashtable.
             */
            Iterator< T, U > StartIterator () const;

            /**
             * @brief Retrieves a new hashtable iterator
             * that points to the end of the hashtable.
             * 
             * @return A hashtable iterator that points to
             *      the end of the hashtable.
             */
            Iterator< T, U > EndIterator () const;

            //*********************** Iterator Interface ***********************//

        private:
            
            /** @brief Holds the map that is the internal representation of the hashtable. */
            std::map< T, U >* val;
    };

    template< typename T, typename U > Hashtable< T, U >::Hashtable ()
    {
        this->val = new std::map< T, U > ();
    }
    
    template< typename T, typename U > Hashtable< T, U >::~Hashtable ()
    {
        if ( this->val != null )
        {
            delete this->val;
            this->val = null;
        }
    }
    
    template< typename T, typename U > void Hashtable< T, U >::Clear ()
    {
        this->val->clear ();
    }
    
    template< typename T, typename U > bool Hashtable< T, U >::Contains ( const T& key ) const
    {
        if ( this->val->find ( key ) != this->val->end () )
        {
            return true;
        }
        return false;
    }
    
    template< typename T, typename U > const U& Hashtable< T, U >::Get ( const T& key ) const
    {
        // Make sure the key exists.
        if ( this->Contains ( key ) )
        {
            return (const U&) this->val->operator[] ( key );
        }
        else
        {
            throw IllegalArgumentException ( "Hashtable::Get - Key does not exist." );
        }
    }
    
    template< typename T, typename U > U& Hashtable< T, U >::Get ( const T& key )
    {
        // Make sure the key exists.
        if ( this->Contains ( key ) )
        {
            return this->val->operator[] ( key );
        }
        else
        {
            throw IllegalArgumentException ( "Hashtable::Get - Key does not exist." );
        }
    }
    
    template< typename T, typename U > bool Hashtable< T, U >::IsEmpty () const
    {
        return this->val->empty ();
    }
    
    template< typename T, typename U > void Hashtable< T, U >::Put ( const T& key, const U& val )
    {
        // Make sure the key is unique.
        if ( this->Contains ( key ) )
        {
            throw IllegalArgumentException ( "Hashtable::Put - Key must be unique." );
        }

        std::pair< GNU_TYPENAME std::map< T, U >::iterator, bool > result = this->val->insert ( std::make_pair ( key, val ) );
        // Check to see if the insert failed.
        if ( !result.second )
        {
            // If we are running in debug mode, vlog an error.
#ifdef _DEBUG
            //vlog << ERR << "Hashtable::put failed for an unknown reason.\n";
#endif
        }
    }
    
    template< typename T, typename U > void Hashtable< T, U >::Remove ( const T& key )
    {
        this->val->erase ( key );
    }
    
    template< typename T, typename U > const int Hashtable< T, U >::Size () const
    {
        return this->val->size ();
    }
    
    template< typename T, typename U > Hashtable< T, U >& Hashtable< T, U >::operator= ( const Hashtable& hashtable )
    {
        this->val = hashtable.val;
        return *this;
    }
    
    template< typename T, typename U > typename Hashtable< T, U >::GNU_TEMPLATE Iterator< > Hashtable< T, U >::StartIterator () const
    {
        GNU_TYPENAME Hashtable< T, U >::GNU_TEMPLATE Iterator< > iter;
        iter.iter = this->val->begin ();
        return iter;
    }
    
    template< typename T, typename U > typename Hashtable< T, U >::GNU_TEMPLATE Iterator< > Hashtable< T, U >::EndIterator () const
    {
        GNU_TYPENAME Hashtable< T, U >::GNU_TEMPLATE Iterator< > iter;
        iter.iter = this->val->end ();
        return iter;
    }

}

#endif
