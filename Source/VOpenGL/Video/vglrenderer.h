/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vglrenderer.h
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

#ifndef VIBRANT_GLRENDERER_H
#define VIBRANT_GLRENDERER_H

#include "vdll.h"
#include "veffect.h"
#include "vgui.h"
#include "vlight.h"
#include "vmesh.h"
#include "vrenderer.h"
#include "vrenderwindow.h"
#include "vvertex.h"

namespace Vibrant
{
    
    /**
     * @brief This class implements the Renderer interface using OpenGL.
     * 
     * @author Chris Culy
     */
    class GLRenderer : public Renderer
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @see Renderer#Renderer(Renderer#RendererConfiguration*)
             */
            GLRenderer ( const Renderer::RendererConfiguration& config = null );

            //************************ General Interface ***********************//
            

            //************************* Update Interface ************************//

            /**
             * @see Renderer#Update
             */
            virtual void Update ();

            /**
             * @see Renderer#Draw(RenderWindow*)
             */
            virtual void Draw ( const RenderWindow* renderWindow );

            //************************* Update Interface ************************//

        protected:
            
            //************************* Update Interface ************************//

            /**
             * @see Renderer#Draw(GUI*)
             */
            virtual void Draw ( const GUI* gui );

            /**
             * @see Renderer#Draw(Mesh*)
             */
            virtual void Draw ( const Mesh* mesh );

            /**
             * @see Renderer#Draw(Vertex)
             */
            virtual void Draw ( const Vertex& vertex );

            /**
             * @see Renderer#ApplyLighting(Light*)
             */
            virtual void ApplyLighting ( const Light* light );

            /**
             * @see Renderer#BeginEffect(Effect*)
             */
            virtual void BeginEffect ( const Effect* effect );

            /**
             * @see Renderer#EndEffect(Effect*)
             */
            virtual void EndEffect ( const Effect* effect );

            /**
             * @see Renderer#SetupEffect(Effect*)
             */
            virtual void SetupEffect ( const Effect* effect );
            
            //************************* Update Interface ************************//
    };

}

#endif
