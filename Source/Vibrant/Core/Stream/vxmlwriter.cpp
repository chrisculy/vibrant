/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vxmlwriter.cpp
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

#include "vxmlwriter.h"

namespace Vibrant
{
    
    XMLWriter::XMLWriter ( Stream* stream ) :
        Writer ( stream )
    {
        this->indentation = 0;
        this->mode.Push ( WRITE_OBJECT );
    }
    
    void XMLWriter::BeginObject ( const String& type )
    {
        if ( this->mode.Top () != WRITE_BASE )
        {
            // Perform the indentation and write the opening tag and a newline.
            this->DoIndentation ();
            *( this->stream ) << XMLWriter::XML_OUTPUT_OPEN_TAG << type;
            *( this->stream ) << XMLWriter::XML_OUTPUT_END_TAG << XMLWriter::XML_OUTPUT_NEWLINE;
            
            this->currentObjectType.Push ( type );
            this->indentation++;
        }
        
        // Update the writer's state.
        this->mode.Push ( WRITE_OBJECT );
    }
    
    void XMLWriter::BeginBase ()
    {
        this->mode.Push ( WRITE_BASE );
    }
    
    void XMLWriter::EndBase ()
    {
        // This should always be true.
        if ( this->mode.Top () == WRITE_BASE )
        {
            this->mode.Pop ();
        }
    }
    
    void XMLWriter::EndObject ()
    {
        // This should always be true.
        if ( this->mode.Top () == WRITE_OBJECT )
        {
            this->mode.Pop ();
        }
        
        // If this is the actual class that is now finished being written
        // (i.e. not a base class) then decrease the indentation and write
        // out the closing tag and a newline.
        if ( this->mode.Top () != WRITE_BASE )
        {
            this->indentation--;
            this->DoIndentation ();
            *( this->stream ) << XMLWriter::XML_OUTPUT_OPEN_TAG << XMLWriter::XML_OUTPUT_SLASH;
            if ( !this->currentObjectType.Top ().IsEmpty () )
            {
                *( this->stream ) << this->currentObjectType.Top ();
            }
            *( this->stream ) << XMLWriter::XML_OUTPUT_END_TAG << XMLWriter::XML_OUTPUT_NEWLINE;
            this->currentObjectType.Pop ();
        }
    }
    
    void XMLWriter::WriteChild ( const Serializable* child )
    {
        child->Write ( this );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned short& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned short* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const short& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const short* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned int& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned int* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const int& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const int* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned long& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const unsigned long* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const long& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const long* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const float& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const float* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const double& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const double* val, const int size )
    {
        this->BeginArrayProperty ( name );
        for ( int i = 0; i < size - 1; i++ )
        {
            *( this->stream ) << val[ i ];
            *( this->stream ) << XMLWriter::XML_OUTPUT_COMMA << XMLWriter::XML_OUTPUT_SPACE;
        }
        *( this->stream ) << val[ size - 1 ];
        this->EndArrayProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const bool& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const char& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::WriteProperty ( const String& name, const String& val )
    {
        this->BeginProperty ( name );
        *( this->stream ) << val;
        this->EndProperty ( name );
    }
    
    void XMLWriter::BeginArrayProperty ( const String& name )
    {
        this->BeginProperty ( name );
        *( this->stream ) << XMLWriter::XML_OUTPUT_NEWLINE;
        this->indentation++;
        this->DoIndentation ();
    }
    
    void XMLWriter::EndArrayProperty ( const String& name )
    {
        this->indentation--;
        *( this->stream ) << XMLWriter::XML_OUTPUT_NEWLINE;
        this->DoIndentation ();
        this->EndProperty ( name );
    }
    
    void XMLWriter::DoIndentation ()
    {
        for ( int i = 0; i < this->indentation; i++ )
        {
            *( this->stream ) << XMLWriter::XML_OUTPUT_INDENT;
        }
    }
    
    void XMLWriter::BeginProperty ( const String& name )
    {
        // Write out the opening tag with the given property's name.
        this->DoIndentation ();
        *( this->stream ) << XMLWriter::XML_OUTPUT_OPEN_TAG << name;
        *( this->stream ) << XMLWriter::XML_OUTPUT_END_TAG;
    }
    
    void XMLWriter::EndProperty ( const String& name )
    {
        // Write out the closing tag with the given property's name and a newline.
        *( this->stream ) << XMLWriter::XML_OUTPUT_OPEN_TAG << XMLWriter::XML_OUTPUT_SLASH << name;
        *( this->stream ) << XMLWriter::XML_OUTPUT_END_TAG << XMLWriter::XML_OUTPUT_NEWLINE;
    }

}
