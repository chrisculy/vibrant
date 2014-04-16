/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vindexbuffer.cpp
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

#include "varray.h"
#include "vindexbuffer.h"
#include "vsystemmanager.h"
#include "vvideo.h"

namespace Vibrant
{
    
    IndexBuffer::IndexBuffer ( unsigned short* indices, unsigned int count )
    {
        buffer = Array< unsigned short > ( count, indices );
        handle = 0;
    }
    
    IndexBuffer::~IndexBuffer ()
    {
        SystemManager::GetVideoSystem ()->DestroyIndexBuffer ( handle );
    }
    
    void IndexBuffer::Bind ()
    {
        // If the index buffer has not yet been created in video memory, create it.
        if ( handle == 0 )
        {
            handle = SystemManager::GetVideoSystem ()->CreateIndexBuffer ( buffer, buffer.Size () );
        }
        SystemManager::GetVideoSystem ()->BindIndexBuffer ( handle );
    }
    
    void IndexBuffer::Unbind ()
    {
        SystemManager::GetVideoSystem ()->UnbindIndexBuffer ();
    }
    
    const int IndexBuffer::Size () const
    {
        return buffer.Size ();
    }
    
    const int IndexBuffer::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void IndexBuffer::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "indexbuffer" );
        
        // Write out the indices.
        writer->WriteProperty ( "size", buffer.Size () );
        writer->WriteProperty ( "data", buffer, buffer.Size () );
        
        writer->EndObject ();
    }
    
    void IndexBuffer::Read ( Reader* reader )
    {
        reader->BeginObject ( "indexbuffer" );
        
        // Read in the indices.
        int indexCount = 0;
        reader->ReadProperty ( "size", &indexCount );
        unsigned short* newBuffer = new unsigned short[ indexCount ];
        reader->ReadProperty ( "data", newBuffer, indexCount );
        buffer = Array< unsigned short > ( indexCount, newBuffer );
        delete[] newBuffer;
        
        reader->EndObject ();
    }
}
