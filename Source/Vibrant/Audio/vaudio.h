/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vaudio.h
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

#ifndef VIBRANT_AUDIO_H
#define VIBRANT_AUDIO_H

#include "vconfig.h"
#include "venginesystem.h"
#include "vpointer.h"
#include "vtimedupdater.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the audio system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see TimedUpdater
     */
    class VAPI Audio : public EngineSystem, public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the audio system
             *      uses to construct itself.
             */
            Audio ( Config* config );

            /**
             * @brief Destructor.
             */
            ~Audio ();

            /**
             * @brief Updates the audio system.
             * 
             * <p>
             * Note: must update only if DoUpdate () is true.
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             * @see Updatable#Update()
             */
            virtual void Update ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< Audio > AudioPtr;

}

#endif
