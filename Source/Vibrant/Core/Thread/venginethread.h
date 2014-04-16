/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: venginethread.h
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

#ifndef VIBRANT_ENGINETHREAD_H
#define VIBRANT_ENGINETHREAD_H

#include "varray.h"
#include "venginesystem.h"
#include "vsystem.h"

#include VIBRANT_THREAD_INCLUDE_FILE

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a thread type that runs and
     * updates a given set of engine systems.
     * 
     * @author Chris Culy
     * @see Array
     * @see EngineSystem
     * @see Thread
     */
    class VAPI EngineThread : public VIBRANT_THREAD
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param engineSystems The set of engine systems.
             */
            EngineThread ( Array< EngineSystemPtr >* engineSystems = null );

            /**
             * @brief Destructor.
             */
            ~EngineThread ();

            /**
             * @brief The thread's run function.
             */
            virtual void Run ();

            /**
             * @brief Retrieves the thread's engine systems.
             * 
             * @return The thread's engine systems.
             */
            Array< EngineSystemPtr >* GetEngineSystems ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the objects to be updated while the thread runs. */
            Array< EngineSystemPtr >* engineSystems;
    };

}

#endif
