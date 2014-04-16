/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vapplication.h
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

#ifndef VIBRANT_APPLICATION_H
#define VIBRANT_APPLICATION_H

#include "vclient.h"
#include "vconfig.h"
#include "vserver.h"
#include "vsingleton.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the application; this is
     * the main entry point and the very top layer.
     * 
     * @author Chris Culy
     */
    class VAPI Application : public Singleton< Application >
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the application
             *      uses to construct itself.
             */
            Application ( Config* config );

            /**
             * @brief Destructor.
             */
            virtual ~Application ();

            /**
             * @brief Runs the application.
             */
            virtual void Run ();

            /**
             * @brief Retrieves the application client.
             * 
             * @return The client.
             */
            Client* GetClient ();

            /**
             * @brief Retrieves the application server.
             * 
             * @return The server.
             */
            Server* GetServer ();

            //************************ General Interface ***********************//

        protected:
            
            /** @brief Holds the application's client. */
            Client* client;

            /** @brief Holds the application's server (only
             * used if the application is a local application). */
            Server* server;
    };

}

#endif
