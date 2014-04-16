/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vthread.cpp
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

#include "vasynchronous.h"
#include "vconvert.h"
#include "vmutexlock.h"
#include "vlog.h"
#include "vmutex.h"
#include "vthread.h"
#include "vsystem.h"

#include VIBRANT_THREAD_INCLUDE_FILE

namespace Vibrant
{
    
    Thread::Thread ()
    {
        this->done = false;
        this->doneMutex = Mutex::GetNewMutex ();
    }
    
    Thread::~Thread ()
    {
        // Clean up the mutex.
        if ( this->doneMutex != null )
        {
            delete this->doneMutex;
            this->doneMutex = null;
        }
    }
    
    void Thread::Exit ()
    {
        this->SetDone ( true );
        this->Join ();
    }
    
    bool Thread::IsDone ()
    {
        bool IsDone = false;
        
        // Copy whether the thread is done.
        {
            LockMutex ( this->doneMutex );
            IsDone = this->done;
        }
        return IsDone;
    }
    
    const void* Thread::GetParam ()
    {
        const void* paramPtr = null;
        
        // Copy the thread's current parameter.
        {
            LockMutex ( this->paramMutex );
            paramPtr = this->param;
        }
        return paramPtr;
    }
    
    void Thread::SetDone ( bool done )
    {
        LockMutex ( this->doneMutex );
        this->done = done;
    }
    
    void Thread::SetParam ( void* param )
    {
        LockMutex ( this->paramMutex );
        this->param = param;
    }
    
    void Thread::SetPriority ( int priority )
    {
        this->priority = priority;
    }
    
    void Thread::SetID ( unsigned int id )
    {
        this->id = id;
        ValToString ( id, &this->name );
    }
    
    Thread* Thread::Execute ( AsynchCallback callback, AsynchState* state )
    {
        return VIBRANT_THREAD::Execute ( callback, state );
    }

}
