/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgui.h
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

#ifndef VIBRANT_GUI_H
#define VIBRANT_GUI_H

#include "vconfig.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the graphical user interface system.
     * 
     * @author Chris Culy
     * @see Config
     */
    class VAPI GUI
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the GUI uses
             *      to construct itself.
             */
            GUI ( Config *config );

            /**
             * @brief Destructor.
             */
            virtual ~GUI ();

            /**
             * @brief Updates the GUI system.
             */
            virtual void Update ();
            
            //************************ General Interface ***********************//
    };

}

#endif
