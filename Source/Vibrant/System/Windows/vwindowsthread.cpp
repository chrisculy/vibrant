/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsthread.cpp
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

#include "vmutexlock.h"
#include "vmutex.h"
#include "vstring.h"
#include "vwindowsthread.h"

namespace Vibrant
{
    
    WindowsThread::WindowsThread ()
    {
        /* stub function */
    }
    
    WindowsThread::~WindowsThread ()
    {
        // Wait until the thread is finished before ending.
        if ( !this->IsDone () )
        {
            this->Join ();
        }
    }
    
    void WindowsThread::Create ()
    {
        // This is a pointer to this thread
        // that allows us to call this 
        // thread's run () function during
        // thread execution.
        void* thisThread = (void*) this;
        
        // Start the thread running right away.
        unsigned int flags = 0;
        
        // Holds the thread's ID temporarily.
        unsigned int threadID = 0;
        
        // Create the thread (with default
        // security attributes and stack size).
        this->handle = _beginthreadex ( null, 0, &WindowsThread::RunThread, thisThread, flags, &threadID );
        
        // Set the thread's id.
        this->SetID ( threadID );
    }
    
    void WindowsThread::Join ()
    {
        WaitForSingleObject ( (HANDLE) this->handle, INFINITE );
    }
    
    void WindowsThread::Run ()
    {
        /* stub function */
    }
    
    uintptr_t WindowsThread::GetHandle ()
    {
        return this->handle;
    }
    
    Thread* WindowsThread::Execute ( AsynchCallback callback, AsynchState* state )
    {
        WindowsThread* thread = new WindowsThread ();
        
        // Create an asynchronous operation object
        // from the given parameters (cleaned up in
        // WindowsThread::RunFunction).
        Thread::AsynchOperation* operation = new Thread::AsynchOperation ();
        operation->callback = callback;
        operation->state = state;
        
        // Start the thread running right away.
        unsigned int flags = 0;
        
        // Holds the thread's ID temporarily.
        unsigned int threadID = 0;
        
        // Create the thread (with default security attributes and stack size).
        thread->handle = _beginthreadex ( null, 0, &WindowsThread::RunFunction, (void*) operation, flags, &threadID );
        
        // Set the thread's id.
        thread->SetID ( threadID );
        
        return thread;
    }
    
    unsigned int __stdcall WindowsThread::RunThread ( void* thread )
    {
        // Create a pointer to the wanted thread and
        // then call its run function.
        Thread* callingThread = (Thread*) thread;
        callingThread->Run ();
        
        return 0;
    }
    
    unsigned int __stdcall WindowsThread::RunFunction ( void* asynchOperation )
    {
        // Get the asynchronous operation and execute it.
        Thread::AsynchOperation* operation = (AsynchOperation*) asynchOperation;
        operation->callback ( operation->state );
        
        // Clean up memory from creating the
        // asynchronous operation object.
        delete operation;
        operation = null;
        
        return 0;
    }

}

#endif
