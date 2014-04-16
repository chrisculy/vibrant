/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtextstream.cpp
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

#include <string>

#include "vexception.h"
#include "vtextstream.h"

namespace Vibrant
{
    
    TextStream::TextStream ()
    {
        this->closed = false;
    }
    
    TextStream::~TextStream ()
    {
        /* stub function */
    }
    
    bool TextStream::Read ( byte* buffer, const int& offset, const int& count )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return false;
        }

        // If the position is valid, read the bytes.
        if ( this->position + count < this->length )
        {
            this->stringStream.read ( (char*) buffer, count );
            this->position = (unsigned long)this->stringStream.tellg ();
            
            // Update the put position.
            this->stringStream.seekp ( this->position );
            return true;
        }
        return false;
    }
    
    bool TextStream::Read ( byte& data )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return false;
        }

        // If the position is valid, read a byte.
        if ( this->position < this->length )
        {
            this->stringStream.get ( (char&) data );
            this->position = (unsigned long)this->stringStream.tellg ();
            
            // Update the put position.
            this->stringStream.seekp ( this->position );
            return true;
        }
        return false;
    }
    
    bool TextStream::Write ( const byte* buffer, const int& offset, const int& count )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return false;
        }

        // If the position is valid, write the bytes.
        if ( this->position + count < this->length )
        {
            this->stringStream.write ( (char*) buffer, count );
            this->position = (unsigned long)this->stringStream.tellp ();
            
            // Update the get position.
            this->stringStream.seekg ( this->position );
            return true;
        }
        return false;
    }
    
    bool TextStream::Write ( const byte& data )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return false;
        }

        // If the position is valid, write a byte.
        if ( this->position < this->length )
        {
            this->stringStream.put ( (char) data );
            this->position = (unsigned long)this->stringStream.tellp ();
            
            // Update the get position.
            this->stringStream.seekg ( this->position );
            return true;
        }
        return false;
    }
    
    void TextStream::Flush ()
    {
        // Make sure the stream is not closed.
        if ( !this->closed )
        {
            this->stringStream.flush ();
        }
    }
    
    void TextStream::Close ()
    {
        this->Flush ();
        this->closed = true;
    }
    
    unsigned long TextStream::Seek ( const unsigned long& offset, const long& position )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return this->position;
        }

        // Passing -1 as the position means to use the current position.
        if ( position == -1 )
        {
            this->position += offset;
        }
        // Compute the new position normally.
        else
        {
            this->position = position + offset;
        }

        // TODO: Write Math::clamp(T value, T low, T high).
        if ( this->position > this->length )
        {
            this->position = this->length;
        }
        if ( this->position < 0 )
        {
            this->position = 0;
        }

        // Perform the actual seek.
        this->stringStream.seekg ( this->position );
        this->stringStream.seekp ( this->position );
        this->position = (unsigned long)this->stringStream.tellg ();
        
        return this->position;
    }
    
    void TextStream::SetPosition ( const unsigned long& position )
    {
        this->Seek ( position, 0 );
    }
    
    unsigned long TextStream::GetPosition ()
    {
        return this->position;
    }
    
    void TextStream::SetLength ( unsigned long length )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return;
        }

        // When the length has decreased, resize (and
        // truncate) the data appropriately.
        if ( length < this->length )
        {
            std::string data = this->stringStream.str ();
            data.resize ( length );
            this->stringStream.str ( data );
        }
        this->length = length;
    }
    
    unsigned long TextStream::GetLength ()
    {
        return this->length;
    }
    
    bool TextStream::CanSeek ()
    {
        return true;
    }
    
    bool TextStream::CanRead ()
    {
        return true;
    }
    
    bool TextStream::CanWrite ()
    {
        return true;
    }
    
    bool TextStream::CanTimeout ()
    {
        return false;
    }
    
    void TextStream::SetReadTimeout ( long timeout )
    {
        throw NotSupportedOperationException ( "TextStream::SetReadTimeout - Text streams cannot timeout." );
    }
    
    void TextStream::SetWriteTimeout ( long timeout )
    {
        throw NotSupportedOperationException ( "TextStream::SetWriteTimeout - Text streams cannot timeout." );
    }
    
    long TextStream::GetReadTimeout ()
    {
        throw NotSupportedOperationException ( "TextStream::GetReadTimeout - Text streams cannot timeout." );
    }
    
    long TextStream::GetWriteTimeout ()
    {
        throw NotSupportedOperationException ( "TextStream::GetWriteTimeout - Text streams cannot timeout." );
    }
    
    const char* TextStream::GetData ()
    {
        return this->stringStream.str ().c_str ();
    }
    
    Stream& TextStream::operator<< ( const unsigned short val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const short val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const unsigned int val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const int val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const unsigned long val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const long val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const float val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const double val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const bool val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const char val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator<< ( const String val )
    {
        this->stringStream << val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( unsigned short& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( short& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( unsigned int& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( int& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( unsigned long& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( long& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( float& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( double& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( bool& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( char& val )
    {
        this->stringStream >> val;
        return *this;
    }
    
    Stream& TextStream::operator>> ( String& val )
    {
        this->stringStream >> val;
        return *this;
    }

}
