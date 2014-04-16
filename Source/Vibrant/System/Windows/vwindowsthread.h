/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsthread.h
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

#ifndef VIBRANT_WINDOWSTHREAD_H
#define VIBRANT_WINDOWSTHREAD_H

#include "vasynchronous.h"
#include "vthread.h"

namespace Vibrant
{
    
    /**
     * @brief Implements multithreading for Windows systems.
     * 
     * @see Thread
     * @author Chris Culy
     */
    class VAPI WindowsThread : public Thread
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            WindowsThread ();

            /**
             * @brief Destructor.
             */
            ~WindowsThread ();

            /**
             * @see Thread#Create()
             */
            void Create ();

            /**
             * @see Thread#Join()
             */
            void Join ();

            /**
             * @see Thread#Run()
             */
            virtual void Run ();

            /**
             * @brief Retrieves the thread's handle.
             * 
             * @return The thread's handle.
             */
            uintptr_t GetHandle ();

            /**
             * @see Thread#Execute(AsynchCallback, AsynchState*)
             */
            static Thread* Execute ( AsynchCallback callback, AsynchState* state );

            /**
             * @brief The Windows thread callback function
             * used for running a VIBRANT_THREAD derived object.
             * 
             * <p>
             * This function just calls the <code>run</code>
             * member function for the desired thread.
             * </p>
             * 
             * @param thread The thread to be executed.
             * @return The result; should be zero.
             */
            static unsigned int __stdcall RunThread ( void* thread );

            /**
             * @brief The Windows thread callback function
             * used for running a given asynchronous operation.
             * 
             * @param asynchOperation The asynchronous operation
             *      to be executed.
             * @return The result; should be zero.
             */
            static unsigned int __stdcall RunFunction ( void* asynchOperation );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the handle to the thread. */
            uintptr_t handle;
    };

}

#endif

#endif
