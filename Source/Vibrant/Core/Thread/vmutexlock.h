/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmutexlock.h
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision: 130 $
 * $Author: Chris $
 * $Date: 2008-01-16 22:31:42 -0500 (Wed, 16 Jan 2008) $
 */

#ifndef VIBRANT_MUTEXLOCK_H
#define VIBRANT_MUTEXLOCK_H

#include "vmutex.h"

namespace Vibrant
{
    
    /**
     * @brief Provides safe (RAII-see http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization)
     * locking and unlocking for mutexes.
     * 
     * @see Mutex
     * @author Chris Culy
     */
    class VAPI MutexLock
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor (locks the given mutex).
             * 
             * @param mutex The mutex to lock.
             */
            MutexLock ( const Mutex* mutex );

            /**
             * @brief Destructor (unlocks the mutex).
             */
            ~MutexLock ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the mutex (that is being lock/unlocked). */
            Mutex* mutex;
    };

// Define a handy macro for locking mutexes.
#define LockMutex(mutex) MutexLock lock ( mutex )

}

// Include inline definitions.
#include "vmutexlock.inl"

#endif
