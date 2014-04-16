/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmutex.h
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

#ifndef VIBRANT_MUTEX_H
#define VIBRANT_MUTEX_H

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a mutex object.
     * 
     * @author Chris Culy
     */
    class VAPI Mutex
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Mutex ();

            /**
             * @brief Destructor.
             */
            virtual ~Mutex ();

            /**
             * @brief Waits on the mutex until it is free.
             */
            virtual void Wait () = 0;

            /**
             * @brief Retrieves a new mutex which the
             * user is responsible for destroying.
             * 
             * @return A new mutex.
             */
            static Mutex* GetNewMutex ();

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Friend class used to actually lock and unlock mutexes.
             */
            friend class MutexLock;

            /**
             * @brief Locks the mutex.
             */
            virtual void Lock () = 0;

            /**
             * @brief Unlocks the mutex.
             */
            virtual void Unlock () = 0;
            
            //************************ General Interface ***********************//
    };

}

#endif
