/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsingleton.h
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

#ifndef VIBRANT_SINGLETON_H
#define VIBRANT_SINGLETON_H

#include "vexception.h"

namespace Vibrant
{
    
    /**
     * @brief Implementation of a class that can only be instantiated once.
     * 
     * <p>
     * Example usage:
     * <pre>
     *  class CustomSingleton : Singleton<CustomSingleton>
     *  {
     *      // Class code goes here.
     *  };
     * 
     *  // Initialize the singleton in the appropriate location.
     *  // Note: This must be done before GetInstance() is called
     *  // or GetInstance() will throw an exception.
     *  CustomSingleton* singleton = new CustomSingleton ( &lt;constructor parameters&gt; );
     *  
     *  ...
     *  
     *  // Somewhere else in the application.
     *  CustomSingleton* customSingleton = CustomSingleton::GetInstance ();
     *  customSingleton->DoSomeStuff ();
     *  
     *  ...
     *  
     *  // Clean up the singleton in the appropriate location.
     *  delete singleton;
     *  singleton = null;
     * </pre>
     * </p>
     * 
     * @author Chris Culy
     */
    template< typename T > class Singleton
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Destructor.
             */
            virtual ~Singleton ();

            /**
             * @brief Retrieves the static instance of the class.
             * 
             * @return A pointer to the static instance.
             * @throws NullPointerException If the singleton object
             *      has not been initialized prior to calling this function.
             */
            static T* GetInstance ();

            /**
             * @brief Allows casting the singleton object to a pointer.
             * 
             * @return The single instantiation (as a pointer).
             */
            inline T* operator * () const;

            /**
             * @brief Allows casting the singleton object to a reference.
             * 
             * @return The single instantiation (as a reference).
             */
            inline T& operator & () const;

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @throws IllegalOperationException If the user attempts
             *      to create multiple instances of the singleton.
             */
            Singleton ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the actual singleton object. */
            static T *theSingleton;

            /** @brief Unusable operators-the user
             * cannot assign or copy the singleton object. */
            Singleton ( const Singleton &vs );
            Singleton& operator = ( const Singleton &vs );
    };
    
    // Initialize the static instance.
    template< typename T > T* Singleton< T >::theSingleton = null;

    template< typename T > Singleton< T >::~Singleton ()
    {
        theSingleton = null;
    }
    
    template< typename T > T* Singleton< T >::GetInstance ()
    {
        // Make sure the static instance has been created.
        if ( theSingleton == null )
        {
            throw NullPointerException ( "Singleton<T>::GetInstance - The singleton object has not yet been created or has been destroyed." );
        }
        return theSingleton;
    }
    
    template< typename T > inline T* Singleton< T >::operator * () const
    {
        return theSingleton;
    }
    
    template< typename T > inline T& Singleton< T >::operator & () const
    {
        return *theSingleton;
    }
    
    template< typename T > Singleton< T >::Singleton ()
    {
        // Make sure that there is only ever one instance of the class.
        if ( theSingleton != null )
        {
            throw IllegalOperationException ( "Singleton<T>::Singleton - Cannot create multiple instances of a singleton." );
        }

        // Calculate the offset from the beginning of
        // the object in memory to where non-singleton part
        // of the object is (remove the Singleton part of the object).
        int pointerOffset = (int) ( (T*) 1 ) - (int) ( (Singleton< T >*) 1 );
        theSingleton = (T*) ( ( (int) this ) + pointerOffset );
    }

}

#endif
