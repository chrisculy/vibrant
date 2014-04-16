/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcolor.h
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

#ifndef VIBRANT_COLOR_H
#define VIBRANT_COLOR_H

#include "vreader.h"
#include "vserializable.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates colors.
     * 
     * @author Chris Culy
     */
    class VAPI Color : public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param r The red value of the color.
             * @param g The green value of the color.
             * @param b The blue value of the color.
             * @param a The alpha value of the color.
             */
            Color ( float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0 );

            /**
             * @brief Copy constructor.
             * 
             * @param color The color to construct this color from.
             */
            Color ( const Color& color );

            /**
             * @brief Destructor.
             */
            virtual ~Color ();

            /**
             * @brief Retrieves the red component of the color.
             * 
             * @return The red component.
             */
            float GetRed () const;

            /**
             * @brief Retrieves the green component of the color.
             * 
             * @return The green component.
             */
            float GetGreen () const;

            /**
             * @brief Retrieves the blue component of the color.
             * 
             * @return The blue component.
             */
            float GetBlue () const;

            /**
             * @brief Retrieves the alpha component of the color.
             * 
             * @return The alpha component.
             */
            float GetAlpha () const;

            /**
             * @brief Assignment operator.
             * 
             * @param color The color to assign to this color.
             * @return The result of the assignment
             *      (this color after assignment).
             */
            const Color& operator= ( const Color &color );

            //************************ General Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );

            //************************ Streaming system ************************//

        private:
            
            /** @brief Holds the red component of the color. */
            float r;

            /** @brief Holds the green component of the color. */
            float g;

            /** @brief Holds the blue component of the color. */
            float b;

            /** @brief Holds the alpha component of the color. */
            float a;
    };

}

#endif
