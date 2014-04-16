/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vdisplaystyle.h
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

#ifndef VIBRANT_DISPLAYSTYLE_H
#define VIBRANT_DISPLAYSTYLE_H

#include "vobject.h"
#include "vpointer.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a display style such as
     * infrared, night vision, or black and white.
     * 
     * @author Chris Culy
     */
    class VAPI DisplayStyle : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param is2D Whether the display style is 2D or not (3D).
             */
            DisplayStyle ( bool is2D = false );

            /**
             * @brief Destructor.
             */
            ~DisplayStyle ();

            /**
             * @brief Retrieves whether the display style is 2D or not (3D is the default).
             * 
             * @return <code>true</code> if the display style is 2D; <code>false</code> otherwise.
             */
            bool Is2D () const;
            /**
             * @brief Sets whether the display style is 2D or not (3D is the default).
             * 
             * @param is2D Whether or not the display style should be 2D.
             */
            void SetIs2D ( const bool is2D );

            //************************ General Interface ***********************//

        private:
            /** @brief Holds whether the display style is 2D or not (3D). */
            bool is2D;
    };
    
    typedef Pointer< DisplayStyle > DisplayStylePtr;

}

#endif
