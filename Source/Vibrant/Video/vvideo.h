/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvideo.h
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

#ifndef VIBRANT_VIDEO_H
#define VIBRANT_VIDEO_H

#include "vconfig.h"
#include "venginesystem.h"
#include "vpointer.h"
#include "vrenderer.h"
#include "vrenderwindow.h"
#include "vscenemanager.h"
#include "vtexture.h"
#include "vtimedupdater.h"
#include "vvertex.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the video system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see TimedUpdater
     */
    class VAPI Video : public EngineSystem, public TimedUpdater
    {
        public:
            
            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             * 
             * <p>
             * Sets up the video system from the given
             * configuration and sets/creates the main render window. The configuration
             * should include the bit depth, screen resolution, any video flags,
             * and the renderer type. The renderer creates a SceneManager from
             * the given render window, or creates the default one if
             * <code>renderWindow</code> is <code>null</code>.
             * <br><b>Note:</b> The render window is either null and a default
             * one is created (which should be specified somewhere by the custom
             * implementation), or it is loaded from a file (usually streamed).
             * </p>
             * 
             * @param config The configuration used to setup the video system.
             * @param renderWindow The main render window for the video system.
             */
            Video ( Config* config, RenderWindow* renderWindow = null );

            /**
             * @brief Destructor.
             */
            virtual ~Video ();

            /**
             * @brief Starts the video system (essentially does
             * any late initialization that is needed).
             * 
             * @see Updatable#Start()
             */
            virtual void Start () = 0;

            /**
             * @brief Updates the video system.
             * 
             * <p>
             * Note: must update only if DoUpdate () is true.
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             * @see Updatable#Update()
             */
            virtual void Update () = 0;

            /**
             * @brief Sets whether the video mode is fullscreen or not.
             * 
             * @param isFullscreen Whether the mode should
             *      be fullscreen or not (windowed).
             */
            void SetIsFullscreen ( bool isFullscreen );

            /**
             * @brief Retrieves whether the video mode is fullscreen or not.
             * 
             * @return <code>true</code> if the video mode
             *      is fullscreen;<code>false</code> otherwise.
             */
            bool IsFullscreen ();

            /**
             * @brief Retrieves the video system's main render window.
             * 
             * @return The main render window.
             */
            RenderWindow* GetMainRenderWindow ();

            /**
             * @brief Change the video display to fullscreen.
             * 
             * @param width The width of the render area.
             * @param height The height of the render area.
             * @param bpp The bits per pixel of the render area.
             * @return <code>true</code> if the video display was changed to
             *      fullscreen successfully; <code>false</code> otherwise.
             */
            virtual bool GoFullscreen ( int width, int height, int bpp ) = 0;

            /**
             * @brief Creates an index buffer object in video memory.
             * 
             * @param indices The index data to be stored in the index buffer.
             * @param count The number of indices.
             * @return The system graphics handle to the index buffer.
             */
            virtual IndexBufferHandle CreateIndexBuffer ( unsigned short* indices, unsigned int count ) = 0;
            /**
             * @brief Creates a texture in video memory.
             * 
             * @param data The texture's image data (in RGBA format).
             * @param width The texture's width.
             * @param height The texture's height.
             * @return The system graphics handle to the texture.
             */
            virtual TextureHandle CreateTexture ( byte* data, int width, int height ) = 0;
            /**
             * @brief Creates a vertex buffer object in video memory.
             * 
             * @param vertices The vertex data to be stored in the vertex buffer.
             * @param count The number of vertices in the vertex buffer.
             * @return The system graphics handle to the vertex buffer.
             */
            virtual VertexBufferHandle CreateVertexBuffer ( Vertex::VertexData* vertices, unsigned int count ) = 0;
            /**
             * @brief Destroys the given index buffer.
             * 
             * @param buffer The system graphics handle to the index buffer to be destroyed.
             */
            virtual void DestroyIndexBuffer ( IndexBufferHandle buffer ) = 0;
            /**
             * @brief Destroys the given texture.
             * 
             * @param texture The system graphics handle to the texture to be destroyed.
             */
            virtual void DestroyTexture ( TextureHandle texture ) = 0;
            /**
             * @brief Destroys the given vertex buffer.
             * 
             * @param buffer The system graphics handle to the vertex buffer to be destroyed.
             */
            virtual void DestroyVertexBuffer ( VertexBufferHandle buffer ) = 0;
            
            /**
             * @brief Binds the given index buffer to be used for rendering.
             * 
             * @param buffer The system graphics handle to the index buffer to be bound.
             */
            virtual void BindIndexBuffer ( IndexBufferHandle buffer ) = 0;
            /**
             * @brief Binds the given texture to be used for rendering.
             * 
             * @param texture The system graphics handle to the texture to be bound.
             */
            virtual void BindTexture ( TextureHandle texture ) = 0;
            /**
             * @brief Binds the given vertex buffer to be used for rendering.
             * 
             * @param buffer The system graphics handle to the vertex buffer to be bound.
             */
            virtual void BindVertexBuffer ( VertexBufferHandle buffer ) = 0;
            /**
             * @brief Unbinds the currently bound index buffer.
             */
            virtual void UnbindIndexBuffer () = 0;
            /**
             * @brief Unbinds the currently bound texture.
             */
            virtual void UnbindTexture () = 0;
            /**
             * @brief Unbinds the currently bound vertex buffer.
             */
            virtual void UnbindVertexBuffer () = 0;
            

            //************************ General Interface ************************//

        protected:
            
            //************************ General Interface ************************//

            /** @brief Holds the renderer. */
            Renderer* renderer;

            /** @brief Holds the main render window (the actual screen). */
            RenderWindow* renderWindow;

            /** @brief Holds the scene manager. */
            SceneManager* sceneManager;

            //************************ General Interface ************************//

        private:
            
            /** @brief Holds if the video system is full screen. */
            bool isFullscreen;

            /** @brief Holds if the video mode needs to be updated. */
            bool videoModeIsDirty;
    };
    
    typedef Pointer< Video > VideoPtr;
    
    typedef Video* (*GetVideoSystemFunction) ( Config*, RenderWindow* );

}

#endif
