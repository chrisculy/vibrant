/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vserver.h
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

#ifndef VIBRANT_SERVER_H
#define VIBRANT_SERVER_H

#include "vai.h"
#include "vconfig.h"
#include "venginesystem.h"
#include "vphysics.h"
#include "vsystem.h"
#include "vtime.h"

#include VIBRANT_THREAD_INCLUDE_FILE

namespace Vibrant
{
    
    /**
     * @brief Provides the server system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see Thread
     * @see TimedUpdater
     */
    class VAPI Server : public EngineSystem, public VIBRANT_THREAD
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the server
             *      uses to construct itself.
             */
            Server ( Config* config );

            /**
             * @brief Destructor.
             */
            virtual ~Server ();

            /**
             * @see EngineSystem#Start()
             */
            virtual void Start ();

            /**
             * @see EngineSystem#Stop()
             */
            virtual void Stop ();

            /**
             * @brief Updates the server.
             * 
             * <p>
             * The server updates the time subsystem,
             * sends and receives information to and from the client, and then
             * updates the physics subsystem.
             * Note: must update only if DoUpdate () is true.
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             */
            virtual void Update ();

            /**
             * @brief Sends information to the client.
             * 
             * <p>
             * Just uses the NetworkStream interface to store all the information
             * from the needed objects in a buffer and records all needed information
             * in the buffer's header.
             * </p>
             */
            virtual void Send ();

            /**
             * @brief Processes the information from the client.
             * 
             * <p>
             * Just uses the NetworkStream interface to get the information
             * and then by using the header for each chunk, stores the data
             * in the proper objects.
             * </p>
             */
            virtual void Receive ();

            //************************ General Interface ***********************//

        protected:
            
            /** @brief The Time Subsystem (server's instance). */
            Time* time;

            /** @brief The Physics Subsystem (also calculates object collision and deformation). */
            Physics* physics;

            /** @brief The AI Subsystem (performs most character, unit, and group logic). */
            AI* ai;

            /** @brief Holds the port that the server listens on. */
            unsigned int port;
    };

}

#endif
