/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvertexbuffer.cpp
 * 
 * 
 * --  Copyright (c) 2007-2009 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

// Include precompiled header.
#include "vprecompiled.h"

#include "vsystemmanager.h"
#include "vvideo.h"
#include "vvertexbuffer.h"

namespace Vibrant
{
    VertexBuffer::VertexBuffer ( Vertex* vertices, unsigned int count )
    {
        // Get the vertex data in the proper format to send to the video card.
        for ( unsigned int i = 0; i < count; i++ )
        {
            buffer.Push ( vertices[ i ].GetVertexData () );
        }
        
        handle = 0;
    }
    
    VertexBuffer::~VertexBuffer ()
    {
        SystemManager::GetVideoSystem ()->DestroyVertexBuffer ( handle );
    }
    
    void VertexBuffer::Bind ()
    {
        // If the vertex buffer has not yet been created in video memory, create it.
        if ( handle == 0 )
        {
            handle = SystemManager::GetVideoSystem ()->CreateVertexBuffer ( buffer, buffer.Size () );
        }
        SystemManager::GetVideoSystem ()->BindVertexBuffer ( handle );
    }
    
    void VertexBuffer::Unbind ()
    {
        SystemManager::GetVideoSystem ()->UnbindVertexBuffer ();
    }
    
    const int VertexBuffer::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void VertexBuffer::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "vertexbuffer" );
        
        // Write out the vertices.
        writer->WriteProperty ( "size", buffer.Size () );
        for ( int i = 0; i < buffer.Size (); i++ )
        {
            writer->WriteChild ( Vertex::VertexDataSerializer::MakeWritable ( &buffer[ i ] ) );
        }
        
        writer->EndObject ();
    }
    
    void VertexBuffer::Read ( Reader* reader )
    {
        reader->BeginObject ( "vertexbuffer" );
        
        // Read in the vertices.
        int vertexCount = 0;
        reader->ReadProperty ( "size", &vertexCount );
        Array< Vertex::VertexData > newBuffer ( vertexCount );
        for ( int i = 0; i < vertexCount; i++ )
        {
            reader->ReadChild ( Vertex::VertexDataSerializer::MakeReadable ( &newBuffer[ i ] ) );
        }
        buffer = Array< Vertex::VertexData > ( vertexCount, newBuffer );
        
        reader->EndObject ();
    }
}
