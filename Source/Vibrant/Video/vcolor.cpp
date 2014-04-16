/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcolor.cpp
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

#include "vcolor.h"
#include "vstream.h"

namespace Vibrant
{
    
    Color::Color ( float r, float g, float b, float a )
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    
    Color::Color ( const Color& color )
    {
        this->r = color.GetRed ();
        this->g = color.GetGreen ();
        this->b = color.GetBlue ();
        this->a = color.GetAlpha ();
    }
    
    Color::~Color ()
    {
        /* stub function */
    }
    
    float Color::GetRed () const
    {
        return r;
    }
    
    float Color::GetGreen () const
    {
        return g;
    }
    
    float Color::GetBlue () const
    {
        return b;
    }
    
    float Color::GetAlpha () const
    {
        return a;
    }
    
    const Color& Color::operator= ( const Color &color )
    {
        this->r = color.GetRed ();
        this->g = color.GetGreen ();
        this->b = color.GetBlue ();
        this->a = color.GetAlpha ();
        
        return *this;
    }
    
    const int Color::GetDiskSize () const
    {
        return 4 * sizeof(float);
    }
    
    void Color::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "color" );
        writer->WriteProperty ( "red", this->r );
        writer->WriteProperty ( "green", this->g );
        writer->WriteProperty ( "blue", this->b );
        writer->WriteProperty ( "alpha", this->a );
        writer->EndObject ();
    }
    
    void Color::Read ( Reader* reader )
    {
        reader->BeginObject ( "color" );
        reader->ReadProperty ( "red", &this->r );
        reader->ReadProperty ( "green", &this->g );
        reader->ReadProperty ( "blue", &this->b );
        reader->ReadProperty ( "alpha", &this->a );
        reader->EndObject ();
    }

}
