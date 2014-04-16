/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vglrenderer.cpp
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
#include "vprecompiled_opengl.h"

#include "vglrenderer.h"
#include "vindexbuffer.h"
#include "vmesh.h"
#include "vtextureeffect.h"

namespace Vibrant
{
    
    /**
     * @brief Converts from Mesh::MeshType to the equivalent OpenGL drawing mode.
     * 
     * @param meshType The mesh's geometry type.
     * @return The equivalent OpenGL drawing mode.
     */
    static GLenum ConvertMeshTypeToMode ( Mesh::MeshType meshType )
    {
        switch ( meshType )
        {
            case Mesh::LINE_CLOSED:
                return GL_LINE_LOOP;
            case Mesh::LINE_OPEN:
                return GL_LINES;
            case Mesh::LINE_SEGMENT:
                return GL_LINE_STRIP;
            case Mesh::POINT:
                return GL_POINTS;
            case Mesh::QUAD:
                return GL_QUADS;
            case Mesh::QUAD_STRIP:
                return GL_QUAD_STRIP;
            case Mesh::TRIANGLE_FAN:
                return GL_TRIANGLE_FAN;
            case Mesh::TRIANGLE_STRIP:
                return GL_TRIANGLE_STRIP;
            case Mesh::TRIANGLE:
            default:
                return GL_TRIANGLES;
        }
    }
    
    GLRenderer::GLRenderer ( const Renderer::RendererConfiguration& config ) :
        Renderer ( config )
    {
        // Set our type to OpenGL.
        SetRendererType ( OPENGL );
        
        // Set up OpenGL in general.
        glShadeModel ( GL_SMOOTH );
        glClearColor ( 0.0, 0.0, 0.0, 0.0 );
        glClearDepth ( 1.0 );
        glEnable ( GL_DEPTH_TEST );
        glDepthFunc ( GL_LEQUAL );
        glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
        
        // Set up materials.
        glEnable ( GL_COLOR_MATERIAL );
        glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
        
        float materialAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
        float materialDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        float materialSpecular[] = { 0.0, 0.0, 0.0, 1.0 };
        
        glMaterialfv ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbient );
        glMaterialfv ( GL_FRONT, GL_DIFFUSE, materialDiffuse );
        glMaterialfv ( GL_FRONT, GL_SPECULAR, materialSpecular );
        
        // Set up lighting.
        glEnable ( GL_LIGHTING );
        float lightPosition[] = { 0.0, 10.0, 0.0 };
        float lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        float lightAmbient[] = { 0.5, 0.5, 0.5, 1.0 };
        glLightfv ( GL_LIGHT0, GL_POSITION, lightPosition );
        glLightfv ( GL_LIGHT0, GL_DIFFUSE, lightDiffuse );
        glLightfv ( GL_LIGHT0, GL_AMBIENT, lightAmbient );
        glEnable ( GL_LIGHT0 );
        
        // Set up texturing.
        glEnable ( GL_TEXTURE_RECTANGLE_ARB );
        
        // Enable blending (for textures with alpha).
        glEnable ( GL_BLEND );
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }
    
    void GLRenderer::Update ()
    {
        /* stub function */
    }
    
    void GLRenderer::Draw ( const RenderWindow* renderWindow )
    {
        // Create the view.
        glViewport ( renderWindow->GetX (), renderWindow->GetY (), renderWindow->GetWidth (), renderWindow->GetHeight () );
        glMatrixMode ( GL_PROJECTION );
        glLoadIdentity ();
        
        // Set up the camera projection.
        if ( renderWindow->GetDisplayStyle ()->Is2D () )
        {
            // Set up the 2D orthographics projection.
            // Note: Once implemented, this will get the values from the render window's camera (the -1 and 1 values).
            glOrtho ( renderWindow->GetX (), renderWindow->GetX () + renderWindow->GetWidth (), renderWindow->GetY (),
                renderWindow->GetY () + renderWindow->GetHeight (), -1, 1 );
            
            // Disable depth testing and lighting for 2D rendering.
            glDisable ( GL_DEPTH_TEST );
            glDisable ( GL_LIGHTING );
        }
        else
        {
            // Set up the 3D perspective projection.
            // Note: Once implemented, this will get the values from the render window's camera (the 45.0f, 1.0f, and 1000.0f values).
            gluPerspective ( 45.0f, (GLfloat) ( renderWindow->GetWidth () ) / (GLfloat) ( renderWindow->GetHeight () ), 1.0f, 1000.0f );
            
            // Enable depth testing and lighting for 3D rendering.
            glEnable ( GL_DEPTH_TEST );
            glEnable ( GL_LIGHTING );
        }

        // Clear the screen and depth buffers.
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        // Draw the window
        Renderer::Draw ( renderWindow );
    }
    
    void GLRenderer::Draw ( const GUI* gui )
    {
        /* stub function */
    }
    
    void GLRenderer::Draw ( const Mesh* mesh )
    {
        // Get ready for drawing.
        glMatrixMode ( GL_MODELVIEW );
        glLoadIdentity ();
        
        // Multiply by the mesh's world transformation.
        glMultMatrixf ( mesh->world.GetValues () );
        glPushMatrix ();
        {
            // Begin all effects.
            for ( int i = 0; i < mesh->EffectCount (); i++ )
            {
                BeginEffect ( mesh->GetEffect ( i ) );
            }

            // Bind the vertices and indices.
            VertexBufferPtr vertices = mesh->GetVertices ();
            IndexBufferPtr indices = mesh->GetIndices ();
            vertices->Bind ();
            indices->Bind ();
            
            GLenum mode = ConvertMeshTypeToMode ( mesh->GetMeshType () );
            int count = mesh->GetIndices ()->Size ();
            glDrawElements ( mode, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0) );
            
            vertices->Unbind ();
            indices->Unbind ();
            
            // End all effects.
            for ( int i = 0; i < mesh->EffectCount (); i++ )
            {
                EndEffect ( mesh->GetEffect ( i ) );
            }
        }
        glPopMatrix ();
    }
    
    void GLRenderer::Draw ( const Vertex& vertex )
    {
        /* stub function */
    }
    
    void GLRenderer::ApplyLighting ( const Light* light )
    {
        /* stub function */
    }
    
    void GLRenderer::BeginEffect ( const Effect* effect )
    {
        // Texture effects.
        if ( effect->IsDerived ( TextureEffect::GetRTTI () ) )
        {
            TextureEffect* textureEffect = (TextureEffect*) effect;
            textureEffect->GetTexture ()->Bind ();
        }
    }
    
    void GLRenderer::EndEffect ( const Effect* effect )
    {
        // Texture effects.
        if ( effect->IsDerived ( TextureEffect::GetRTTI () ) )
        {
            TextureEffect* textureEffect = (TextureEffect*) effect;
            textureEffect->GetTexture ()->Unbind ();
        }
    }
    
    void GLRenderer::SetupEffect ( const Effect* effect )
    {
        /* stub function */
    }
}
