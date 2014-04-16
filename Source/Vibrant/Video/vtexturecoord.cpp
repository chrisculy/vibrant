/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtexturecoord.cpp
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

#include "vreader.h"
#include "vsystem.h"
#include "vtexturecoord.h"
#include "vwriter.h"

namespace Vibrant
{
    
    TextureCoord::TextureCoord ( float s, float t, unsigned int uvImageID )
    {
        this->s = s;
        this->t = t;
        this->uvImageID = uvImageID;
    }
    
    TextureCoord::TextureCoord ( const TextureCoord& textureCoord )
    {
        this->s = textureCoord.GetS ();
        this->t = textureCoord.GetT ();
        this->uvImageID = textureCoord.GetUVImageID ();
    }
    
    TextureCoord::~TextureCoord ()
    {
        /* stub function */
    }
    
    float TextureCoord::GetS () const
    {
        return this->s;
    }
    
    float TextureCoord::GetT () const
    {
        return this->t;
    }
    
    unsigned int TextureCoord::GetUVImageID () const
    {
        return this->uvImageID;
    }
    
    void TextureCoord::SetS ( float s )
    {
        this->s = s;
    }
    
    void TextureCoord::SetT ( float t )
    {
        this->t = t;
    }
    
    void TextureCoord::SetUVImageID ( unsigned int uvImageID )
    {
        this->uvImageID = uvImageID;
    }
    
    const TextureCoord& TextureCoord::operator= ( const TextureCoord &textureCoord )
    {
        this->s = textureCoord.GetS ();
        this->t = textureCoord.GetT ();
        this->uvImageID = textureCoord.GetUVImageID ();
        
        return *this;
    }
    
    const int TextureCoord::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void TextureCoord::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "texture-coordinate" );
        writer->WriteProperty ( "image", this->uvImageID );
        writer->WriteProperty ( "s", this->s );
        writer->WriteProperty ( "t", this->t );
        writer->EndObject ();
    }
    
    void TextureCoord::Read ( Reader* reader )
    {
        reader->BeginObject ( "texture-coordinate" );
        reader->ReadProperty ( "image", &this->uvImageID );
        reader->ReadProperty ( "s", &this->s );
        reader->ReadProperty ( "t", &this->t );
        reader->EndObject ();
    }

}
