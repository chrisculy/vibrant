/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vitemspecification.h
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

#ifndef VIBRANT_ITEMSPECIFICATION_H
#define VIBRANT_ITEMSPECIFICATION_H

#include "vobject.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates an item specification or type
     * of item (rather than an instance of an item).
     * 
     * @author Chris Culy
     */
    class ItemSpecification : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs an item specification.
             */
            ItemSpecification ();

            /**
             * @brief Destructor.
             */
            ~ItemSpecification ();
            
            //************************ General Interface ***********************//
    };

}

#endif
