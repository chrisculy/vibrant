/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrenderer.h
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

#ifndef VIBRANT_RENDERER_H
#define VIBRANT_RENDERER_H

#include "vscenenode.h"
#include "varray.h"
#include "veffect.h"
#include "vgui.h"
#include "vlight.h"
#include "vmesh.h"
#include "vrenderwindow.h"
#include "vvertex.h"

namespace Vibrant
{
    
    /**
     * @brief This class encapsulates the functionality of drawing to the screen.
     * 
     * TODO: Update this comment.
     * <p>
     * This class is implemented as a singleton because it is convenient
     * and desirable to be able to have one "global" renderer for a given
     * application. The only situation that was considered for desiring
     * the use of multiple renderers involved comparing the differences
     * between different graphics APIs simultaneously. However, this can
     * be accomplished by running two separate applications or embedding
     * two different applications as controls within another application.
     * </p>
     * 
     * <p>
     * Note: All video initialization is done in the constructors
     * of Renderer-derived class implementations.
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI Renderer
    {
        public:
            
            //********************** Renderer Configuration *********************//

            /**
             * @brief Represents the configuration for a renderer.
             * 
             * @author Chris Culy
             */
            struct RendererConfiguration
            {
                    /**
                     * @brief Constructor.
                     * 
                     * @param width The width of the render area.
                     * @param height The height of the render area.
                     * @param bitsPerPixel The bits per pixel of the render area.
                     */
                    RendererConfiguration ( int width = 1024, int height = 768, int bitsPerPixel = 24 )
                    {
                        this->width = width;
                        this->height = height;
                        this->bitsPerPixel = bitsPerPixel;
                    }
                    
                    /** @brief Holds the width of the renderer's render area. */
                    int width;

                    /** @brief Holds the height of the renderer's render area. */
                    int height;

                    /** @brief Holds the bits per pixel of the renderer's render area. */
                    int bitsPerPixel;
            };

            //********************** Renderer Configuration *********************//
            

            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             */
            Renderer ( const RendererConfiguration& config = RendererConfiguration () );

            /**
             * @brief Destructor.
             */
            virtual ~Renderer ();

            /**
             * @brief Defines the different types of renderers.
             */
            enum RendererType
            {
                OPENGL,
                DIRECTX
            };

            /**
             * @brief Retreives the renderer's type.
             * 
             * <p>
             * This specifies the graphics API that
             * is used to implement the Renderer interface.
             * </p>
             * 
             * @return The renderer's type.
             */
            const RendererType GetRendererType ();

            /**
             * @brief Retrieves the render area's width.
             * 
             * @return The width.
             */
            int GetWidth ();

            /**
             * @brief Retrieves the render area's height.
             * 
             * @return The height.
             */
            int GetHeight ();

            /**
             * @brief Retrieves the render area's bits per pixel.
             * 
             * @return The bits per pixel.
             */
            int GetBitsPerPixel ();

            /**
             * @brief Sets the render area's width.
             * 
             * @param width The new width.
             */
            void SetWidth ( int width );

            /**
             * @brief Sets the render area's height.
             * 
             * @param height The new height.
             */
            void SetHeight ( int height );

            /**
             * @brief Sets the render area's bits per pixel.
             * 
             * @param bitsPerPixel The new bits per pixel.
             */
            void SetBitsPerPixel ( int bitsPerPixel );

            //************************ General Interface ************************//
            

            //************************ Drawing Interface ************************//

            /**
             * @brief Draws a RenderWindow to the screen.
             * 
             * @param renderWindow The render window to draw.
             */
            virtual void Draw ( const RenderWindow* renderWindow );

            //************************ Drawing Interface ************************//

        protected:
            
            //************************ General Interface ************************//

            /**
             * @brief Sets the renderer's type (OpenGL, DirectX, etc.)
             * 
             * @param type The type of the renderer.
             */
            void SetRendererType ( RendererType type );

            //************************ General Interface ************************//
            

            //************************ Drawing Interface ************************//

            /**
             * @brief Draws a GUI to the screen.
             * 
             * @param gui The graphical user interface to draw.
             */
            virtual void Draw ( const GUI* gui );

            /**
             * @brief Draws a SceneNode.
             * 
             * @param node The node to draw.
             */
            virtual void Draw ( const SceneNode* node );

            /**
             * @brief Draws a Mesh.
             * 
             * @param mesh The mesh to draw.
             */
            virtual void Draw ( const Mesh* mesh ) = 0;

            /**
             * @brief Draws a Vertex.
             * 
             * @param vertex The vertex to draw.
             */
            virtual void Draw ( const Vertex& vertex ) = 0;

            /**
             * @brief Applies the lighting associated with the specified light.
             * 
             * @param light The light to include in lighting calculations.
             */
            virtual void ApplyLighting ( const Light* light ) = 0;

            /**
             * @brief Begins an effect.
             * 
             * @param effect The effect to begin.
             */
            virtual void BeginEffect ( const Effect* effect ) = 0;

            /**
             * @brief Ends an effect.
             * 
             * @param effect The effect to end.
             */
            virtual void EndEffect ( const Effect* effect ) = 0;

            /**
             * @brief Sets up a Effect.
             * 
             * @param effect The effect to set up.
             */
            virtual void SetupEffect ( const Effect* effect ) = 0;

            //************************ Drawing Interface ************************//

        protected:
            
            /** @brief Holds the width of the render area. */
            int width;

            /** @brief Holds the height of the render area. */
            int height;

            /** @brief Holds the bits per pixel of the render area. */
            int bitsPerPixel;

        private:
            
            /** @brief The type of renderer (i.e. OpenGL, DirectX, etc.). */
            RendererType type;
    };

}

#endif
