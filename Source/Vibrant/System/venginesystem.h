/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: venginesystem.h
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

#ifndef VIBRANT_ENGINESYSTEM_H
#define VIBRANT_ENGINESYSTEM_H

#include "vupdatable.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the most basic functionality
     * of a system within the engine that
     * can be started, updated, and stopped.
     * 
     * @author Chris Culy
     */
    class VAPI EngineSystem : public Updatable
    {
        public:
            
            /**
             * @brief Starts the system (performs any set up).
             */
            virtual void Start ();

            /**
             * @brief Stops the system (performs any shut down).
             */
            virtual void Stop ();
    };
    
    typedef Pointer< EngineSystem > EngineSystemPtr;

}

#endif
