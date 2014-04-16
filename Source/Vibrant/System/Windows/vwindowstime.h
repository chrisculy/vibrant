/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowstime.h
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#ifndef VIBRANT_WINDOWSTIME_H
#define VIBRANT_WINDOWSTIME_H

#include "vconfig.h"
#include "vtime.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the time system for the Windows
     * operating system.
     * 
     * @author Chris Culy
     * @see Time
     */
    class VAPI WindowsTime : public Time
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @see Time#Time(Config*)
             */
            WindowsTime ( Config* config );

            /**
             * @see Time#~Time()
             */
            ~WindowsTime ();

            /**
             * @see Time#GetTime()
             */
            long GetTime ();

            //************************ General Interface ***********************//

        private:
            
            /** Holds the latency of calling the GetSystemTime function. */
            __int64 performanceLatency;

            /** Holds the frequency of the high performance system counter. */
            __int64 performanceFrequency;
    };

}

#endif

#endif
