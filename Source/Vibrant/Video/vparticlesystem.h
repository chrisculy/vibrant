/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vparticlesystem.h
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

#ifndef VIBRANT_PARTICLESYSTEM_H
#define VIBRANT_PARTICLESYSTEM_H

#include "vobject.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates particle systems.
     * 
     * @author Chris Culy
     */
    class VAPI ParticleSystem : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            ParticleSystem ();

            /**
             * @brief Destructor.
             */
            ~ParticleSystem ();
            
            //************************ General Interface ***********************//
    };

}

#endif
