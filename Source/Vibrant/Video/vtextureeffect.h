/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtextureeffect.h
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

#ifndef VIBRANT_TEXTUREEFFECT_H
#define VIBRANT_TEXTUREEFFECT_H

#include "veffect.h"
#include "vreader.h"
#include "vtexture.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates all textures for 3D objects.
     * 
     * @author Chris Culy
     */
    class VAPI TextureEffect : public Effect
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param texture The texture for the effect.
             */
            TextureEffect ( Texture* texture );

            /**
             * @brief Destructor.
             */
            ~TextureEffect ();

            /**
             * @brief Retrieves the texture effect's texture.
             */
            Texture* GetTexture () const;

            //************************ General Interface ***********************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all texture effects.
             * 
             * @return The TextureEffect RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//
            

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
            
            /** Holds the texture used in the texture effect. */
            Texture* texture;
    };

}

#endif
