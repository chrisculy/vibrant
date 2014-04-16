/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtexture.cpp
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

#include <IL/il.h>

#include "vlog.h"
#include "vreader.h"
#include "vstring.h"
#include "vsystemmanager.h"
#include "vtexture.h"
#include "vvideo.h"
#include "vwriter.h"

namespace Vibrant
{
    void ResourceManagerLoadImageDimensions ( String filename, ImageHandle& imageHandle, int& width, int& height )
    {
        static bool initialized = false;
        if ( !initialized )
        {
            ilInit ();
            initialized = true;
        }

        // TODO: Add error checking.
        imageHandle = ilGenImage ();
        ilBindImage ( imageHandle );
        ilLoadImage ( filename.CString () );
        width = ilGetInteger ( IL_IMAGE_WIDTH );
        height = ilGetInteger ( IL_IMAGE_HEIGHT );
    }
    
    byte* ResourceManagerLoadImage ( String filename, ImageHandle imageHandle )
    {
        // TODO: Add error checking.
        ilBindImage ( imageHandle );
        ilLoadImage ( filename.CString () );
        byte* data = ilGetData ();
        
        return data;
    }
    
    Texture::Texture ( String filename )
    {
        this->filename = filename;
        textureHandle = 0;
        imageHandle = 0;
        width = 0;
        height = 0;
        ResourceManagerLoadImageDimensions ( filename, imageHandle, width, height );
    }
    
    Texture::~Texture ()
    {
        // Release the system graphics handle for the texture.
        if ( textureHandle != 0 )
        {
            SystemManager::GetVideoSystem ()->DestroyTexture ( textureHandle );
        }
        
        // Release the DevIL image handle for the texture's image.
        if ( imageHandle != 0 )
        {
            ilDeleteImage ( imageHandle );
        }
    }
    
    void Texture::Bind ()
    {
        // Load the texture into video memory if it is not yet there.
        if ( textureHandle == 0 )
        {
            byte* data = ResourceManagerLoadImage ( filename, imageHandle );
            textureHandle = SystemManager::GetVideoSystem ()->CreateTexture ( data, width, height );
        }
        SystemManager::GetVideoSystem ()->BindTexture ( textureHandle );
    }
    
    void Texture::Unbind ()
    {
        SystemManager::GetVideoSystem ()->UnbindTexture ();
    }
    
    unsigned int Texture::GetTextureID () const
    {
        return textureHandle;
    }
    
    String Texture::GetFilename () const
    {
        return filename;
    }
    
    int Texture::GetWidth ()
    {
        return width;
    }
    
    int Texture::GetHeight ()
    {
        return height;
    }
    
    const RTTI* Texture::GetType () const
    {
        return Texture::GetRTTI ();
    }
    
    RTTI* Texture::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            type = new RTTI ( "Texture", baseTypes );
        }
        return type;
    }
    
    const int Texture::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Texture::Write ( Writer* writer ) const
    {
        writer->BeginObject ( GetType ()->GetName () );
        writer->WriteProperty ( "filename", GetFilename () );
        writer->WriteProperty ( "texture-id", textureHandle );
        
        // Write out the Object part of this object.
        writer->BeginBase ();
        Object::Write ( writer );
        writer->EndBase ();
        writer->EndObject ();
    }
    
    void Texture::Read ( Reader* reader )
    {
        reader->BeginObject ( GetType ()->GetName () );
        reader->ReadProperty ( "filename", &filename );
        reader->ReadProperty ( "texture-id", &textureHandle );
        
        // Read in the Object part of this object.
        reader->BeginBase ();
        Object::Read ( reader );
        reader->EndBase ();
        reader->EndObject ();
    }
}
