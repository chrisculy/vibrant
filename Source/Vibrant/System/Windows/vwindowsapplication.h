/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsapplication.h
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

#ifndef VIBRANT_WINDOWSAPPLICATION_H
#define VIBRANT_WINDOWSAPPLICATION_H

#include "vapplication.h"
#include "vconfig.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Implements applications for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsApplication : public Application
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration that the
             *      application uses to construct itself.
             * @param hInstance The Windows application instance.
             */
            WindowsApplication ( Config* config, HINSTANCE hInstance );

            /**
             * @brief Destructor.
             */
            ~WindowsApplication ();

            /**
             * @see Application#Run()
             */
            void Run ();

            /**
             * @brief Registers the window class for the application.
             * 
             * @return <code>true</code> if successful;
             *      <code>false</code> otherwise.
             */
            bool RegisterWindowClass ();

            /**
             * @brief Retrieves the Windows application instance.
             * 
             * @return The Windows application instance.
             */
            HINSTANCE GetHInstance ();

            /**
             * @brief Retrieves the class name of the application.
             * 
             * @return The class name.
             */
            String GetClassName ();

            /**
             * @brief Retrieves the title of the application.
             * 
             * @return The title.
             */
            String GetTitle ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds if the server is remote. */
            bool serverIsRemote;

            /** @brief Holds the Windows "instance" for the application. */
            HINSTANCE hInstance;

            /** @brief Holds the Windows class name for the application. */
            String className;

            /** @brief Holds the application title. */
            String title;
    };

}

#endif

#endif
