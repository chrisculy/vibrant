/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vthread.h
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

#ifndef VIBRANT_THREAD_H
#define VIBRANT_THREAD_H

#include "vasynchronous.h"
#include "vstring.h"
#include "vtimedupdater.h"

namespace Vibrant
{
    
    // Forward Class Declarations.
    class Mutex;
    
    /**
     * @brief Allows for multithreaded systems (that 
     * are implemented as classes derived from this class).
     * 
     * @see TimedUpdater
     * @author Chris Culy
     */
    class VAPI Thread : public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Thread ();

            /**
             * @brief Destructor.
             * 
             * <p>
             * Note: All derived destructors should do the following
             * at the beginning:
             * <pre>
             *  // Wait until the thread is finished before ending.
             *  if ( !this->IsDone () )
             *  {
             *      this->join ();
             *  }
             * </pre>
             * </p>
             */
            virtual ~Thread ();

            /**
             * @brief Creates the thread.
             */
            virtual void Create () = 0;

            /**
             * @brief Joins the thread with the thread
             * from which this function is called
             * (i.e. waits until the thread is finished).
             */
            virtual void Join () = 0;

            /**
             * @brief Exits the thread.
             */
            virtual void Exit ();

            /**
             * @brief The function that is run by the thread.
             * 
             * <p>
             * This function retrieves the parameters from <code>param</code>.<br>
             * <i>Note: the update should only occur if DoUpdate () is true.</i>
             * <br><br>
             * This function should be written in the following form:
             * <pre>
             * while ( !IsDone () )
             * {
             *      if ( this->DoUpdate () )
             *      {
             *          // Do stuff here. //
             *      }
             * }
             * </pre>
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             */
            virtual void Run () = 0;

            /**
             * @brief Returns whether the thread is done or not.
             * 
             * <p>
             * This should be implemented in a thread-safe
             * manner by the system thread implementation.
             * </p>
             * 
             * @return Whether the thread is done or not.
             */
            virtual bool IsDone ();

            /**
             * @brief Retrieves the parameter used by the thread during execution.
             * 
             * @return The thread's parameter.
             */
            virtual const void* GetParam ();

            /**
             * @brief Gets the thread's priority.
             * 
             * @return The thread's priority or time slice. This is
             *      in the format of a percent of time spent in the thread
             *      each second as a integer from 0-100. (i.e. 30% of CPU time
             *      would be passed in as priority = 30.)
             */
            virtual inline const int GetPriority ();

            /**
             * @brief Retrieves the thread's ID.
             * 
             * @return The thread's ID.
             */
            virtual inline const unsigned int GetID ();

            /**
             * @brief Retrieves the thread's name.
             * 
             * @return The thread's name.
             */
            inline const String& GetName ();

            /**
             * @brief Sets whether the thread is done or not.
             * 
             * <p>
             * This should be implemented in a thread-safe
             * manner by the system thread implementation.
             * </p>
             * 
             * @param done Whether the thread is done or not.
             */
            virtual void SetDone ( bool done );

            /**
             * @brief Sets the parameters that will be used
             * by the thread during execution.
             * 
             * @param param The new parameters.
             */
            virtual void SetParam ( void* param );

            /**
             * @brief Sets the thread's priority.
             * 
             * @param priority The thread's priority or time slice. This is
             *      in the format of a percent of time spent in the thread
             *      each second as a integer from 0-100. (i.e. 30% of CPU time
             *      would be passed in as priority = 30.)
             * @throws IllegalArgumentException If <code>priority &lt; 0</code>
             *      or <code>priority &gt; 100</code>.
             */
            virtual void SetPriority ( int priority );

            /**
             * @brief Sets the thread's ID.
             * 
             * @param id The thread's ID.
             */
            virtual void SetID ( unsigned int id );

            /**
             * @brief Executes the given callback function
             * as an asynchronous operation with the
             * given asynchronous state object parameter.
             * 
             * <p>
             * <b>Note: All Thread derived classes must implement
             * this exact same function.</b>
             * </p>
             * 
             * @param callback The function to execute.
             * @param state The state of the asynchronous operation.
             * @return The thread that the function will be run (or is running) in.
             *      Note: This thread object is dynamically allocated-the user
             *      must deallocate the memory when finished with the thread object.
             */
            static Thread* Execute ( AsynchCallback callback, AsynchState* state );

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Represents an asynchronous operation.
             * 
             * @author Chris Culy
             */
            struct AsynchOperation
            {
                    /** @brief Holds the function to execute. */
                    AsynchCallback callback;

                    /** @brief Holds the state of the operation. */
                    AsynchState* state;
            };

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds whether the thread is done or not. */
            bool done;

            /** @brief Holds the thread priority. */
            int priority;

            /** @brief Holds the thread's ID. */
            unsigned int id;

            /** @brief Holds the parameter that is used by
             * the thread during execution. */
            void* param;

            /** @brief Holds the mutex for the thread's done variable. */
            Mutex* doneMutex;

            /** @brief Holds the mutex for the thread's param variable. */
            Mutex* paramMutex;

            /** @brief Holds the thread's name. This is
             * auto generated from the ID and is
             * currently only used as a reference for
             * the mutex that determines whether the
             * thread is done or not. */
            String name;
    };

}

// Include inline definitions.
#include "vthread.inl"

#endif
