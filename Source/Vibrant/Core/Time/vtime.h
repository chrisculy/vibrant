/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtime.h
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

#ifndef VIBRANT_TIME_H
#define VIBRANT_TIME_H

#include "vconfig.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the time system.
     * 
     * @author Chris Culy
     * @see Config
     */
    class VAPI Time
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration used to construct the time system.
             */
            Time ( Config* config );

            /**
             * @brief Destructor.
             */
            virtual ~Time ();

            /**
             * @brief Retrieves the current system time in milliseconds.
             * 
             * @return The current system time in milliseconds
             *      or -1 if the system time cannot be retrieved.
             */
            virtual long GetTime () = 0;
            
            //************************ General Interface ***********************//
    };

}

#endif
