/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vclient.h
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

#ifndef VIBRANT_CLIENT_H
#define VIBRANT_CLIENT_H

#include "varray.h"
#include "vaudio.h"
#include "vconfig.h"
#include "venginesystem.h"
#include "venginethread.h"
#include "vinput.h"
#include "vstring.h"
#include "vsystem.h"
#include "vtime.h"
#include "vtimedupdater.h"
#include "vupdatable.h"
#include "vvideo.h"

namespace Vibrant
{
    
    /**
     * @brief Provides the client system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see TimedUpdater
     */
    class VAPI Client : public EngineSystem, public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the client
             *      uses to construct itself.
             */
            Client ( Config* config );

            /**
             * @brief Destructor.
             */
            virtual ~Client ();

            /**
             * @see EngineSystem#Start()
             */
            virtual void Start ();

            /**
             * @see EngineSystem#Stop()
             */
            virtual void Stop ();

            /**
             * @brief Updates the client.
             * 
             * <p>
             * Note: must update only if DoUpdate () is true.
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             */
            virtual void Update ();

            /**
             * @brief Connects to the given server.
             * 
             * @param server The server's IP or name (automatically resolves the name).
             */
            virtual void Connect ( String server );

            /**
             * @brief Sends information to the server.
             * 
             * <p>
             * Just uses the NetworkStream interface to store all the information
             * from the needed objects in a buffer and records all needed information
             * in the buffer's header.
             * </p>
             */
            virtual void Send ();

            /**
             * @brief Processes the information from the server.
             * 
             * <p>
             * Just uses the NetworkStream interface to get the information
             * and then by using the header for each chunk, stores the data
             * in the proper objects.
             * </p>
             */
            virtual void Receive ();

            /**
             * @brief Gets whether the client is paused or not.
             * 
             * @return Whether the client is paused or not.
             */
            bool IsPaused ();

            /**
             * @brief Sets whether the client is paused or not.
             * 
             * @param paused Whether the client should be paused or not.
             */
            void SetPaused ( bool paused );

            /**
             * @brief Returns whether the client is done or not.
             * 
             * @return Whether the client is done or not.
             */
            bool IsDone ();

            /**
             * @brief Sets whether the client is done or not.
             * 
             * @param done Whether the client is done or not.
             */
            void SetDone ( bool done );

            //************************ General Interface ***********************//

        protected:
            
            /** @brief The Time Subsystem. */
            Time* time;

            /** @brief The Input Subsystem. */
            InputPtr input;

            /** @brief The Audio Subsystem. */
            AudioPtr audio;

            /** @brief The Video Subsystem. */
            VideoPtr video;

            /** @brief Holds the client's systems that are running in the main therad. */
            Array< EngineSystemPtr >* systems;

            /** @brief Holds the client's children threads that are running the other client systems. */
            Array< EngineThread* >* threads;

            /** @brief Holds whether the client is done or not. */
            bool done;

            /** @brief Holds whether the client is paused or not. */
            bool paused;
    };

}

#endif
