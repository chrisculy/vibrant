/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtimedupdater.cpp
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

#include "vlog.h"
#include "vsystemmanager.h"
#include "vtime.h"
#include "vtimedupdater.h"

namespace Vibrant
{
    
    TimedUpdater::TimedUpdater ( int frequency )
    {
        this->updateCount = 0;
        // Don't ever divide by zero.
        this->millisecondsPassed = 0.0001;
        this->frequency = frequency;
        
        this->updateTimeInterval = ( frequency > 0 ) ? ( 1000 / frequency ) : -1;
        // Set the time variables initially ((as late as possible).
        // We also set them whenever the frequency is set.
        Time* time = SystemManager::GetTimeSystem ();
        previousTime = time->GetTime ();
        previousUpdateTime = time->GetTime ();
        currentTime = time->GetTime ();
    }
    
    TimedUpdater::~TimedUpdater ()
    {
        /* stub function */
    }
    
    void TimedUpdater::SetFrequency ( int frequency )
    {
        this->frequency = frequency;
        this->updateTimeInterval = ( frequency > 0 ) ? ( 1000 / frequency ) : -1;
        // Set the time variables (as late as possible).
        Time* time = SystemManager::GetTimeSystem ();
        previousTime = time->GetTime ();
        previousUpdateTime = time->GetTime ();
        currentTime = time->GetTime ();
    }
    
    int TimedUpdater::GetFrequency ()
    {
        return this->frequency;
    }
    
    double TimedUpdater::GetFrameRate ()
    {
        return ( (double) this->updateCount ) / ( this->millisecondsPassed / 1000.0 );
    }
    
    bool TimedUpdater::DoUpdate ()
    {
        // Get the current time.
        Time* time = SystemManager::GetTimeSystem ();
        currentTime = time->GetTime ();
        
        // If we are just supposed to update all the time, then update.
        if ( this->frequency == -1 )
        {
            this->updateCount++;
            this->millisecondsPassed += currentTime - previousTime;
            previousTime = currentTime;
            return true;
        }
        // If the time that has passed since the last update is
        // greater than the minumum time interval for an update, then update.
        else if ( ( currentTime - previousUpdateTime ) > this->updateTimeInterval )
        {
            this->updateCount++;
            // Update the time variables.
            this->millisecondsPassed += currentTime - previousTime;
            previousUpdateTime += updateTimeInterval;
            previousTime = currentTime;
            return true;
        }
        // Otherwise, don't.
        else
        {
            return false;
        }
    }

}
