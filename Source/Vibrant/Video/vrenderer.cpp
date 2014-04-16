/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrenderer.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "vscenenode.h"
#include "veffect.h"
#include "vgui.h"
#include "vmesh.h"
#include "vrenderer.h"
#include "vrenderwindow.h"
#include "vvertex.h"

namespace Vibrant
{
    
    Renderer::Renderer ( const Renderer::RendererConfiguration& config )
    {
        this->width = config.width;
        this->height = config.height;
        this->bitsPerPixel = config.bitsPerPixel;
    }
    
    Renderer::~Renderer ()
    {
        /* stub function */
    }
    
    const Renderer::RendererType Renderer::GetRendererType ()
    {
        return type;
    }
    
    void Renderer::Draw ( const RenderWindow* renderWindow )
    {
        // Get the render window's visible scene.
        SceneNode* scene = renderWindow->GetVisibleScene ()->GetRoot ();
        
        if ( scene != null )
        {
            // Draw the visible scene.
            Draw ( scene );
        }

        // Draw the render window's GUI (if it exists).
        GUI* gui = renderWindow->GetGUI ();
        if ( gui != null )
        {
            Draw ( gui );
        }
    }
    
    int Renderer::GetWidth ()
    {
        return width;
    }
    
    int Renderer::GetHeight ()
    {
        return height;
    }
    
    int Renderer::GetBitsPerPixel ()
    {
        return bitsPerPixel;
    }
    
    void Renderer::SetWidth ( int width )
    {
        this->width = width;
    }
    
    void Renderer::SetHeight ( int height )
    {
        this->height = height;
    }
    
    void Renderer::SetBitsPerPixel ( int bitsPerPixel )
    {
        this->bitsPerPixel = bitsPerPixel;
    }
    
    void Renderer::SetRendererType ( Renderer::RendererType type )
    {
        this->type = type;
    }
    
    void Renderer::Draw ( const GUI* gui )
    {
        /* stub function */
    }
    
    void Renderer::Draw ( const SceneNode* node )
    {
        // Set the lights for this node.
        for ( int i = 0; i < node->LightCount (); i++ )
        {
            ApplyLighting ( node->GetLight ( i ) );
        }

        // Execute pre-drawing effects setup.
        for ( int i = 0; i < node->EffectCount (); i++ )
        {
            SetupEffect ( node->GetEffect ( i ) );
        }
        
        // Draw any mesh associated with this node.
        if ( node->IsDerived ( Mesh::GetRTTI () ) )
        {
            Mesh* mesh = (Mesh*) node;
            Draw ( mesh );
        }
        
        // Draw this node's children (if the child is a SceneNode).
        for ( int i = 0; i < node->ChildCount (); i++ )
        {
            if ( node->GetChild ( i )->IsDerived ( SceneNode::GetRTTI () ) )
            {
                SceneNode* child = (SceneNode*) node->GetChild ( i );
                Draw ( child );
            }
        }
    }

}
