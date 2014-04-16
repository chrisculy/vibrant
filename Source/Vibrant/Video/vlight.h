/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vlight.h
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

#ifndef VIBRANT_LIGHT_H
#define VIBRANT_LIGHT_H

#include "vobject.h"
#include "vpointer.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a 3D light.
     * 
     * @author Chris Culy
     */
    class VAPI Light : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Light ();

            /**
             * @brief Destructor.
             */
            ~Light ();

            /**
             * @brief Updates the light.
             */
            virtual void Update ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< Light > LightPtr;

}

#endif
