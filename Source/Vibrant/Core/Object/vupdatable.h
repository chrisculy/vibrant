/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vupdatable.h
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

#ifndef VIBRANT_UPDATABLE_H
#define VIBRANT_UPDATABLE_H

#include "vpointable.h"
#include "vpointer.h"

namespace Vibrant
{
    
    /**
     * @brief An interface for any object that can be updated.
     * 
     * @author Chris Culy
     * @see Pointable
     */
    class VAPI Updatable : public Pointable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief The update function.
             */
            virtual void Update ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< Updatable > UpdatablePtr;

}

#endif
