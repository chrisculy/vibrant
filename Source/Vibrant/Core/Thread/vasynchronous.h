/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vasynchronous.h
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

#ifndef VIBRANT_ASYNCHRONOUS_H
#define VIBRANT_ASYNCHRONOUS_H

namespace Vibrant
{
    
    /**
     * @brief Represents the state of an asynchronous operation.
     * 
     * @author Chris Culy
     */
    class VAPI AsynchState
    {
        public:

        //************************ General Interface ***********************//

        /**
         * @brief Constuctor.
         */
        AsynchState ()
        {
            /* stub function */
        }

        /**
         * @brief Destructor.
         */
        virtual ~AsynchState ()
        {
            /* stub function */
        }

        //************************ General Interface ***********************//
    };

    /**
     * @brief Defines the function interface for
     * asynchronous operation callbacks.
     * 
     * @param state The state of the asynchronous operation.
     */
    typedef void (*AsynchCallback) ( AsynchState* state );

}

#endif
