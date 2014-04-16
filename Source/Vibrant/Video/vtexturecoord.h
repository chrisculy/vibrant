/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtexturecoord.h
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

#ifndef VIBRANT_TEXTURECOORD_H
#define VIBRANT_TEXTURECOORD_H

#include "vreader.h"
#include "vserializable.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates texture coordinates for UV mapping.
     * 
     * @author Chris Culy
     */
    class VAPI TextureCoord : public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param s The s (x) texture coordinate.
             * @param t The t (y) texture coordinate.
             * @param uvImageID The unique ID number of the
             *      texture coordinate's corresponding texture.
             */
            TextureCoord ( float s = 0.0, float t = 0.0, unsigned int uvImageID = 0 );

            /**
             * @brief Copy constructor.
             * 
             * @param textureCoord The texture coordinate to
             *      construct this object from.
             */
            TextureCoord ( const TextureCoord& textureCoord );

            /**
             * @brief Destructor.
             */
            virtual ~TextureCoord ();

            /**
             * @brief Retrieves the s (x) coordinate.
             * 
             * @return The s coordinate.
             */
            float GetS () const;

            /**
             * @brief Retrieves the t (y) coordinate.
             * 
             * @return The t coordinate.
             */
            float GetT () const;

            /**
             * @brief Retrieves the UV image ID.
             * 
             * @return The UV image ID.
             */
            unsigned int GetUVImageID () const;

            /**
             * @brief Sets the s (x) coordinate.
             * 
             * @param s The new s coordinate.
             */
            void SetS ( float s );

            /**
             * @brief Sets the t (y) coordinate.
             * 
             * @param t The new t coordinate.
             */
            void SetT ( float t );

            /**
             * @brief Sets the UV image ID.
             * 
             * @param uvImageID The new UV image ID.
             */
            void SetUVImageID ( unsigned int uvImageID );

            /**
             * @brief Assignment operator.
             * 
             * @param textureCoord The texture coordinate to
             *      assign to this texture coordinate.
             * @return The result of the assignment
             *      (this texture coordinate after assignment).
             */
            const TextureCoord& operator= ( const TextureCoord &textureCoord );

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
            
            /** @brief Holds the s coordinate. */
            float s;

            /** @brief Holds the t coordinate. */
            float t;

            /** @brief Holds the UV image ID. */
            unsigned int uvImageID;
    };

}

#endif
