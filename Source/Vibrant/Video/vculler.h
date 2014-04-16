/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vculler.h
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

#ifndef VIBRANT_CULLER_H
#define VIBRANT_CULLER_H

#include "vobject.h"
#include "vpointer.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the process of culling on
     * the CPU before the GPU pass.
     * 
     * @author Chris Culy
     */
    class VAPI Culler : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Culler ();

            /**
             * @brief Destructor.
             */
            ~Culler ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< Culler > CullerPtr;

}

#endif
