/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vphysics.h
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

#ifndef VIBRANT_PHYSICS_H
#define VIBRANT_PHYSICS_H

#include "vconfig.h"
#include "vtimedupdater.h"
#include "vupdatable.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the physics system.
     * 
     * @author Chris Culy
     * @see Config
     * @see TimedUpdater
     * @see Updatable
     */
    class VAPI Physics : public Updatable, public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration that the physics
             *      system uses to construct itself.
             */
            Physics ( Config* config );
            /**
             * @brief Destructor.
             */
            ~Physics ();

            /**
             * @brief Updates the physics system.
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

}

#endif
