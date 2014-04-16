/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgenerictime.h
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

#ifndef VIBRANT_GENERICTIME_H
#define VIBRANT_GENERICTIME_H

#include "vtime.h"

namespace Vibrant
{
    
    /**
     * @brief Stub implementation of Time.
     * 
     * @author Chris Culy
     */
    class VAPI GenericTime : public Time
    {
        public:
            
            /**
             * @see Time#GetTime
             */
            long GetTime ()
            {
                return -1;
            }
    };

}

#endif
