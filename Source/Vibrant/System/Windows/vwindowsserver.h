/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsserver.h
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

#ifndef VIBRANT_WINDOWSSERVER_H
#define VIBRANT_WINDOWSSERVER_H

#include "vserver.h"

namespace Vibrant
{
    
    /**
     * @brief Implements servers for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsServer : public Server
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the server
             *      uses to construct itself.
             */
            WindowsServer ( Config* config );

            /**
             * @brief Destructor.
             */
            ~WindowsServer ();

            /**
             * @see Thread#Run()
             */
            void Run ();
            
            //************************ General Interface ***********************//
    };

}

#endif

#endif
