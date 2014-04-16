/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtexture.h
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

#ifndef VIBRANT_TEXTURE_H
#define VIBRANT_TEXTURE_H

#include <IL/il.h>

#include "vobject.h"
#include "vpointer.h"
#include "vreader.h"
#include "vstring.h"
#include "vwriter.h"

namespace Vibrant
{
    /** @brief Represents the system graphics handle to a texture. */
    typedef unsigned int TextureHandle;
    
    /** @brief Represents the DevIL handle to an image. */
    typedef ILuint ImageHandle;
    
    /**
     * @brief Encapsulates an image texture normally used
     * as a texture for a 3D object (UV mapped).
     * 
     * @author Chris Culy
     * @see Object
     */
    class VAPI Texture : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param filename The filename of the texture's image file.
             */
            Texture ( String filename = "" );

            /**
             * @brief Destructor.
             */
            ~Texture ();
            
            /**
             * @brief Binds the texture to be used for rendering.
             */
            void Bind ();
            /**
             * @brief Unbinds the texture.
             */
            void Unbind ();

            /**
             * @brief Retrieves the texture's ID.
             * 
             * @return The texture's ID.
             */
            unsigned int GetTextureID () const;
            /**
             * @brief Retrieves the texture's filename.
             * 
             * @return The texture's filename.
             */
            String GetFilename () const;
            /**
             * @brief Retrieves the texture's width.
             * 
             * @return The width.
             */
            int GetWidth();
            /**
             * @brief Retrieves the texture's height.
             * 
             * @return The height.
             */
            int GetHeight();

            //************************ General Interface ***********************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all textures.
             * 
             * @return The Texture RTTI.
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

            /** @brief Holds the texture's filename. */
            String filename;

            /** @brief Holds the width of the texture. */
            int width;

            /** @brief Holds the height of the texture. */
            int height;

            /** @brief Holds the system graphics handle of the texture. */
            TextureHandle textureHandle;
            
            /** @brief Holds the DevIL handle of the texture's image. */
            ImageHandle imageHandle;
    };
    
    typedef Pointer< Texture > TexturePtr;

}

#endif
