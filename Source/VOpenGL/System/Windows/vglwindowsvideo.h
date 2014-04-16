/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vglwindowsvideo.h
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#ifndef VIBRANT_GLWINDOWSVIDEO_H
#define VIBRANT_GLWINDOWSVIDEO_H

#include "vconfig.h"
#include "vmutex.h"
#include "vrenderwindow.h"
#include "vstring.h"
#include "vvertex.h"
#include "vwindowsvideo.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the video system for Windows systems using OpenGL.
     * 
     * @author Chris Culy
     */
    class GLWindowsVideo : public WindowsVideo
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            GLWindowsVideo ( Config* config, RenderWindow* renderWindow = null );

            /**
             * @brief Destructor.
             */
            ~GLWindowsVideo ();

            /**
             * @see Video#CreateIndexBuffer(unsigned short*, unsigned int)
             */
            IndexBufferHandle CreateIndexBuffer ( unsigned short* indices, unsigned int count );
            /**
             * @see Video#CreateTexture(byte*, int, int)
             */
            TextureHandle CreateTexture ( byte* data, int width, int height );
            /**
             * @see Video#CreateVertexBuffer(Vertex::VertexData*, unsigned int)
             */
            VertexBufferHandle CreateVertexBuffer ( Vertex::VertexData* vertices, unsigned int count );
            /**
             * @see Video#DestroyIndexBuffer(IndexBufferHandle)
             */
            void DestroyIndexBuffer ( IndexBufferHandle buffer );
            /**
             * @see Video#DestroyTexture(TextureHandle)
             */
            void DestroyTexture ( TextureHandle texture );
            /**
             * @see Video#DestroyVertexBuffer(VertexBufferHandle)
             */
            void DestroyVertexBuffer ( VertexBufferHandle buffer );
            
            /**
             * @see Video#BindIndexBuffer(IndexBufferHandle)
             */
            void BindIndexBuffer ( IndexBufferHandle buffer );
            /**
             * @see Video#BindTexture(TextureHandle)
             */
            void BindTexture ( TextureHandle texture );
            /**
             * @see Video#BindVertexBuffer(VertexBufferHandle)
             */
            void BindVertexBuffer ( VertexBufferHandle buffer );
            /**
             * @see Video#UnbindIndexBuffer
             */
            void UnbindIndexBuffer ();
            /**
             * @see Video#UnbindTexture
             */
            void UnbindTexture();
            /**
             * @see Video#UnbindVertexBuffer
             */
            void UnbindVertexBuffer ();

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @see WindowsVideo#StartVideo ()
             */
            void StartVideo ();

            /**
             * @brief Checks to see if the given OpenGL
             * extension is supported.
             * 
             * @param extensionName The OpenGL extension name.
             * @return <code>true</code> if it is supported;
             *      <code>false</code> otherwise.
             */
            static bool CheckExtension ( String extensionName );
            
            //************************ General Interface ***********************//
    };
    
    /**
     * @brief Retrieves a new instance of the OpenGL based Windows video system.
     * 
     * @param config The configuration used to setup the video system.
     * @param renderWindow The main render window for the video system.
     * @return An instance of the OpenGL based Windows video system
     *      (the user must delete it when they finish with it).
     */
    extern "C" VAPI Video* GetVideoSystem ( Config* config, RenderWindow* renderWindow );

}

#endif

#endif
