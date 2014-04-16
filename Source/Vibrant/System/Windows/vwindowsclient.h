/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsclient.h
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

#ifndef VIBRANT_WINDOWSCLIENT_H
#define VIBRANT_WINDOWSCLIENT_H

#include "vclient.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the network client for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsClient : public Client
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @see Client#Client(Config*)
             */
            WindowsClient ( Config* config );

            /**
             * @see Client#~Client()
             */
            ~WindowsClient ();

            /**
             * @brief Retrieves whether the client is in high performance mode or not
             * (whether or not it completely hogs the CPU causing all other apps to be slow).
             * 
             * @return Whether the client is in high performance mode.
             */
            bool IsInHighPerformanceMode ();

            /**
             * @brief Sets whether the client is in high performance mode or not
             * (whether or not it completely hogs the CPU causing all other apps to be slow).
             * 
             * @param inHighPerformanceMode Whether the client is in high performance mode.
             */
            void SetInHighPerformanceMode ( bool inHighPerformanceMode );

            /**
             * @see Client#Update()
             */
            virtual void Update ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds whether the client is in high performance mode (to the detriment of other applications). */
            bool inHighPerformanceMode;
    };

}

#endif

#endif
