/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vboundingvolume.h
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

#ifndef VIBRANT_BOUNDINGVOLUME_H
#define VIBRANT_BOUNDINGVOLUME_H

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the concept of a bounding volume for a 3D object.
     * 
     * @author Chris Culy
     */
    class VAPI BoundingVolume
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            BoundingVolume ();

            /**
             * @brief Destructor.
             */
            ~BoundingVolume ();

            /**
             * @brief Grows this bounding volume to contain
             * the specified bounding volume.
             * 
             * @param volume The volume to add to this volume.
             */
            void GrowToContain ( BoundingVolume volume );

            /**
             * @brief Clears the bounding volume to nothing.
             */
            void Clear ();
            
            //************************ General Interface ***********************//
    };

}

#endif
