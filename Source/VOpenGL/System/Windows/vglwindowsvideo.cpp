/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vglwindowsvideo.cpp
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vglrenderer.h"
#include "vglwindowsvideo.h"
#include "vrenderwindow.h"
#include "vstring.h"
#include "vvertex.h"
#include "vwindowsexception.h"
#include "vwindowsvideo.h"

#ifdef _DEBUG
#include "vconvert.h"
#include "vexception.h"
#endif

namespace Vibrant
{
    
    GLWindowsVideo::GLWindowsVideo ( Config* config, RenderWindow* renderWindow ) :
        WindowsVideo ( config, renderWindow )
    {
        /* stub function */
    }
    
    GLWindowsVideo::~GLWindowsVideo ()
    {
        // Destroy everything that still exists in the application
        // if the app has a window handle.
        if ( this->windowHandle != 0 )
        {
            // If the app has a device context.
            if ( this->deviceContext != 0 )
            {
                // Set the current rendering context to 0.
                // Note: This sets the rendering context for
                // the given deviceContext; it does not mess up
                // the device context (or set it to null).
                wglMakeCurrent ( this->deviceContext, 0 );
                
                //if the app has a rendering context
                if ( this->renderContext != 0 )
                {
                    // Delete the rendering context and set it to 0.
                    wglDeleteContext ( this->renderContext );
                    this->renderContext = 0;
                }
            }
        }
    }
    
    IndexBufferHandle GLWindowsVideo::CreateIndexBuffer ( unsigned short* indices, unsigned int count )
    {
        // Create the buffer.
        IndexBufferHandle handle = 0;
        glGenBuffers ( 1, &handle );
        
        // Bind it and fill it with the given data.
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, handle );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), indices, GL_STATIC_DRAW );
        
#ifdef _DEBUG
        // TODO: Fix up the error handling here (and in general for OpenGL calls).
        int bufferSize = 0;
        glGetBufferParameteriv ( GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize );
        if ( (int) ( count * sizeof(unsigned short) ) != bufferSize )
        {
            glDeleteBuffers ( 1, &handle );
            handle = 0;
            String arg1, arg2, arg3;
            ValToString ( count * sizeof(unsigned short), &arg1 );
            ValToString ( bufferSize, &arg2 );
            ValToString ( glGetError (), &arg3 );
            throw Exception ( "GLWindowsVideo::CreateIndexBuffer - Failed to create index buffer (" + arg1 + "!=" + arg2 + ") with error "
                + arg3 );
        }
#endif
        
        // Return the handle to the buffer.
        return handle;
    }
    
    TextureHandle GLWindowsVideo::CreateTexture ( byte* data, int width, int height )
    {
        // Create the texture.
        TextureHandle handle = 0;
        glGenTextures ( 1, &handle );
        
        // Load the texture data into memory (with bilinear filtering enabled).
        glBindTexture ( GL_TEXTURE_RECTANGLE_ARB, handle );
        glTexParameteri ( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri ( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D ( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
        
        // Unbind the texture and return the system graphics handle to it.
        glBindTexture ( GL_TEXTURE_RECTANGLE_ARB, 0 );
        return handle;
    }
    
    VertexBufferHandle GLWindowsVideo::CreateVertexBuffer ( Vertex::VertexData* vertices, unsigned int count )
    {
        // Create the buffer.
        VertexBufferHandle handle = 0;
        glGenBuffers ( 1, &handle );
        
#ifdef _DEBUG
        int error = 0;
        if ( ( error = glGetError () ) != GL_NO_ERROR )
        {
            String arg1;
            ValToString ( error, &arg1 );
            throw Exception ( "Failed to generate a buffer handle with error " + arg1 );
        }
#endif
        
        // Bind it and fill it with the given data.
        glBindBuffer ( GL_ARRAY_BUFFER, handle );
        glBufferData ( GL_ARRAY_BUFFER, count * sizeof(Vertex::VertexData), vertices, GL_STATIC_DRAW );
        
#ifdef _DEBUG
        int bufferSize = 0;
        glGetBufferParameteriv ( GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize );
        if ( (int) ( count * sizeof(Vertex::VertexData) ) != bufferSize )
        {
            glDeleteBuffers ( 1, &handle );
            handle = 0;
            String arg1, arg2, arg3;
            ValToString ( count * sizeof(Vertex::VertexData), &arg1 );
            ValToString ( bufferSize, &arg2 );
            ValToString ( glGetError (), &arg3 );
            throw Exception ( "GLWindowsVideo::CreateVertexBuffer - Failed to create vertex buffer (" + arg1 + "!=" + arg2
                + ") with error " + arg3 );
        }
#endif
        
        // Return the handle to the buffer.
        return handle;
    }
    
    void GLWindowsVideo::DestroyIndexBuffer ( IndexBufferHandle buffer )
    {
        glDeleteBuffers ( 1, &buffer );
    }
    
    void GLWindowsVideo::DestroyTexture ( TextureHandle texture )
    {
        glDeleteTextures ( 1, &texture );
    }
    
    void GLWindowsVideo::DestroyVertexBuffer ( VertexBufferHandle buffer )
    {
        glDeleteBuffers ( 1, &buffer );
    }
    
    void GLWindowsVideo::BindIndexBuffer ( IndexBufferHandle buffer )
    {
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffer );
    }
    
    void GLWindowsVideo::BindTexture ( TextureHandle texture )
    {
        glBindTexture ( GL_TEXTURE_RECTANGLE_ARB, texture );
    }
    
    void GLWindowsVideo::BindVertexBuffer ( VertexBufferHandle buffer )
    {
        glBindBuffer ( GL_ARRAY_BUFFER, buffer );
        
        // Set up the pointers into the vertex buffer and enable 
        // the needed arrays to draw using the vertex buffer.
        
        glVertexPointer ( 3, GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::POSITION_OFFSET) );
        glEnableClientState ( GL_VERTEX_ARRAY );
        
        glNormalPointer ( GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::NORMAL_OFFSET) );
        glEnableClientState ( GL_NORMAL_ARRAY );
        
        glColorPointer ( 4, GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::COLOR_OFFSET) );
        glEnableClientState ( GL_COLOR_ARRAY );
        
        glClientActiveTexture ( GL_TEXTURE0 );
        glTexCoordPointer ( 2, GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::TEXTURE_COORDS_0_OFFSET) );
        glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
        
        // TODO: Implement multitexturing (don't forget disabling in UnbindVertexBuffer).
//        glClientActiveTexture ( GL_TEXTURE1 );
//        glTexCoordPointer ( 2, GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::TEXTURE_COORDS_1_OFFSET) );
//        glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
        
//        glClientActiveTexture ( GL_TEXTURE2 );
//        glTexCoordPointer ( 2, GL_FLOAT, Vertex::DATA_SIZE, BUFFER_OFFSET(Vertex::TEXTURE_COORDS_2_OFFSET) );
//        glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    }
    
    void GLWindowsVideo::UnbindIndexBuffer ()
    {
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
    
    void GLWindowsVideo::UnbindTexture ()
    {
        glBindTexture ( GL_TEXTURE_RECTANGLE_ARB, 0 );
    }
    
    void GLWindowsVideo::UnbindVertexBuffer ()
    {
//        glClientActiveTexture ( GL_TEXTURE2 );
//        glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
//        glClientActiveTexture ( GL_TEXTURE1 );
//        glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
        glClientActiveTexture ( GL_TEXTURE0 );
        glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState ( GL_COLOR_ARRAY );
        glDisableClientState ( GL_NORMAL_ARRAY );
        glDisableClientState ( GL_VERTEX_ARRAY );
        
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    }
    
    void GLWindowsVideo::StartVideo ()
    {
        // Attempt to get the rendering context.
        this->renderContext = wglCreateContext ( this->deviceContext );
        if ( this->renderContext == null )
        {
            ReleaseDC ( this->windowHandle, this->deviceContext );
            this->deviceContext = 0;
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
            throw WindowsException ( "Could not get the rendering context." );
        }

        // Attempt to make the rendering context the current rendering context.
        if ( !wglMakeCurrent ( this->deviceContext, this->renderContext ) )
        {
            wglDeleteContext ( this->renderContext );
            this->renderContext = 0;
            ReleaseDC ( this->windowHandle, this->deviceContext );
            this->deviceContext = 0;
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
            throw WindowsException ( "Could not make the rendering context the current rendering context." );
        }

        // Initialize GLee (and make all available OpenGL functionality accessible).
        GLeeInit ();
        
        // Create the renderer and set the main render window.
        Renderer::RendererConfiguration rendererConfig ( this->width, this->height, this->bpp );
        this->renderer = new GLRenderer ( rendererConfig );
        
        // Try to turn off vertical sync.
        if ( WGL_EXT_swap_control )
        {
            wglSwapIntervalEXT ( 0 );
        }
        
        // Make sure texture rectangles are supported.
        if ( !GL_ARB_texture_rectangle )
        {
            // TODO: Maybe make this a more specific exception (VideoException?).
            throw Exception ( "Texture rectangles are not supported." );
        }
    }
    
    bool GLWindowsVideo::CheckExtension ( String extensionName )
    {
        // Get the supported extensions.
        String supportedExtensions = (vchar*) glGetString ( GL_EXTENSIONS );
        
        // Make sure that the wanted extension and
        // the list of extensions are valid.
        if ( supportedExtensions.IsEmpty () || extensionName.IsEmpty () )
        {
            return false;
        }

        // Search the list for the given extension.
        unsigned int index = 0;
        int nextIndex = 0;
        String currentExtension = "";
        while ( nextIndex != String::INVALID_INDEX )
        {
            nextIndex = supportedExtensions.Find ( " ", index );
            currentExtension = supportedExtensions.Substring ( index, nextIndex - index - 1 );
            if ( currentExtension == extensionName )
            {
                return true;
            }
            index = nextIndex + 1;
        }
        
        return false;
    }
    
    extern "C" VAPI Video* GetVideoSystem ( Config* config, RenderWindow* renderWindow )
    {
        static Video* video = new GLWindowsVideo ( config, renderWindow );
        return video;
    }

}

#endif
