/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcamera.h
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

#ifndef VIBRANT_CAMERA_H
#define VIBRANT_CAMERA_H

#include "vobject.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the 3D camera.
     * 
     * @author Chris Culy
     */
    class VAPI Camera : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Camera ();

            /**
             * @brief Destructor.
             */
            ~Camera ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< Camera > CameraPtr;

}

#endif
