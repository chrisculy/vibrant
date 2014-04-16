/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtextureeffect.cpp
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
#include "vtextureeffect.h"
#include "vwriter.h"

namespace Vibrant
{
    
    TextureEffect::TextureEffect ( Texture* texture )
    {
        /* stub function */
        this->texture = texture;
    }
    
    TextureEffect::~TextureEffect ()
    {
        /*stub function */
    }
    
    Texture* TextureEffect::GetTexture () const
    {
        return this->texture;
    }
    
    const RTTI* TextureEffect::GetType () const
    {
        return TextureEffect::GetRTTI ();
    }
    
    RTTI* TextureEffect::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            baseTypes.Push ( Effect::GetRTTI () );
            type = new RTTI ( "TextureEffect", baseTypes );
        }
        return type;
    }
    
    const int TextureEffect::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void TextureEffect::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        
        // Write the Effect part of this object.
        writer->BeginBase ();
        Effect::Write ( writer );
        writer->EndBase ();
        
        // Write the texture.
        writer->WriteChild ( this->GetTexture () );
        writer->EndObject ();
    }
    
    void TextureEffect::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        
        // Read the Effect part of this object.
        reader->BeginBase ();
        Effect::Read ( reader );
        reader->EndBase ();
        
        // Read the texture.
        reader->ReadChild ( this->texture );
        reader->EndObject ();
    }

}
