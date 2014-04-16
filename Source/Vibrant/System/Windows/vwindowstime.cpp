/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowstime.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vconfig.h"
#include "vwindowstime.h"

namespace Vibrant
{
    
    WindowsTime::WindowsTime ( Config* config ) :
        Time ( config )
    {
        this->performanceLatency = 0;
        
        // Set the high performance counter frequency.
        this->performanceFrequency = 0;
        QueryPerformanceFrequency ( (LARGE_INTEGER*) &performanceFrequency );
        
        // Convert the frequency from counts/second to counts/millisecond.
        if ( this->performanceFrequency != 0 )
        {
            this->performanceFrequency /= 1000;
        }

        // Check if the high performance counter is supported at all (returns 0 if it is not supported).
        if ( this->performanceFrequency == 0 )
        {
            // TODO: Implement a fallback (such as using GetTickCount64()).
            // This is incorrect, but prevents division by zero.
            this->performanceFrequency = 1;
        }
        
        // Calculate the latency of GetSystemTime().
        __int64 performanceCountBefore = 0;
        __int64 performanceCountAfter = 0;
        
        QueryPerformanceCounter ( (LARGE_INTEGER*) &performanceCountBefore );
        this->GetTime ();
        QueryPerformanceCounter ( (LARGE_INTEGER*) &performanceCountAfter );
        
        this->performanceLatency = performanceCountAfter - performanceCountBefore;
    }
    
    WindowsTime::~WindowsTime ()
    {
        /* stub function */
    }
    
    long WindowsTime::GetTime ()
    {
        static __int64 performanceCount = 0;
        
        QueryPerformanceCounter ( (LARGE_INTEGER*) &performanceCount );
        return (long) ( ( performanceCount - performanceLatency ) / this->performanceFrequency );
    }

}

#endif
