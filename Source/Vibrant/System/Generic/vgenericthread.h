/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgenericthread.h
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

#ifndef VIBRANT_GENERICTHREAD_H
#define VIBRANT_GENERICTHREAD_H

#include "vthread.h"

namespace Vibrant
{
    
    /**
     * @brief Stub implementation of Thread.
     * 
     * @author Chris Culy
     */
    class VAPI GenericThread : public Thread
    {
        public:
            
            /**
             * @see Thread#Create
             */
            void Create ()
            {
                /* stub function */
            }
            
            /**
             * @see Thread#Join
             */
            void Join ()
            {
                /* stub function */
            }
            
            /**
             * @see Thread#IsDone
             */
            bool IsDone ()
            {
                /* stub function */
                return false;
            }
            
            /**
             * @see Thread#SetDone
             */
            void SetDone ( bool done )
            {
                /* stub function */
            }
            
            /**
             * @see Thread#SetParam
             */
            void SetParam ( void* param )
            {
                /* stub function */
            }
            
            /**
             * @see Thread#Execute
             */
            static Thread* GenericThread::Execute ( AsynchCallback callback, AsynchState* state )
            {
                /* stub function */
                return null;
            }
    };

}

#endif
