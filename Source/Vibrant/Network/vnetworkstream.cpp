/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworkstream.cpp
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

#include "vexception.h"
#include "vnetworkstream.h"
#include "vstring.h"

namespace Vibrant
{
    
    NetworkStream::NetworkStream ()
    {
        /* stub function */
    }
    
    NetworkStream::~NetworkStream ()
    {
        /* stub function */
    }
    
    bool NetworkStream::Read ( byte* buffer, const int& offset, const int& count )
    {
        // TODO: Implement this.
        return false;
    }
    
    bool NetworkStream::Read ( byte& data )
    {
        // TODO: Implement this.
        return false;
    }
    
    bool NetworkStream::Write ( const byte* buffer, const int& offset, const int& count )
    {
        // TODO: Implement this.
        return false;
    }
    
    bool NetworkStream::Write ( const byte& data )
    {
        // TODO: Implement this.
        return false;
    }
    
    void NetworkStream::Flush ()
    {
        // TODO: Implement this.
    }
    
    void NetworkStream::Close ()
    {
        // TODO: Implement this (write out all remaining data and close the connection).
    }
    
    unsigned long NetworkStream::Seek ( const unsigned long& offset, const long& position )
    {
        throw NotSupportedOperationException ( "NetworkStream::Seek - Network streams do not support seeking." );
    }
    
    void NetworkStream::SetPosition ( const unsigned long& position )
    {
        throw NotSupportedOperationException ( "NetworkStream::SetPosition - Network streams do not support seeking." );
    }
    
    unsigned long NetworkStream::GetPosition ()
    {
        throw NotSupportedOperationException ( "NetworkStream::GetPosition - Network streams do not support seeking." );
    }
    
    void NetworkStream::SetLength ( unsigned long length )
    {
        throw NotSupportedOperationException ( "NetworkStream::SetLength - Network streams do not support seeking." );
    }
    
    unsigned long NetworkStream::GetLength ()
    {
        throw NotSupportedOperationException ( "NetworkStream::GetLength - Network streams do not support seeking." );
    }
    
    bool NetworkStream::CanSeek ()
    {
        return false;
    }
    
    bool NetworkStream::CanRead ()
    {
        return true;
    }
    
    bool NetworkStream::CanWrite ()
    {
        return true;
    }
    
    bool NetworkStream::CanTimeout ()
    {
        return true;
    }
    
    void NetworkStream::SetReadTimeout ( long timeout )
    {
        this->readTimeout = timeout;
    }
    
    void NetworkStream::SetWriteTimeout ( long timeout )
    {
        this->writeTimeout = timeout;
    }
    
    long NetworkStream::GetReadTimeout ()
    {
        return this->readTimeout;
    }
    
    long NetworkStream::GetWriteTimeout ()
    {
        return this->writeTimeout;
    }
    
    Stream& NetworkStream::operator<< ( const unsigned short val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const short val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const unsigned int val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const int val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const unsigned long val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const long val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const float val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const double val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const bool val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const char val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator<< ( const String val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( unsigned short& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( short& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( unsigned int& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( int& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( unsigned long& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( long& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( float& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( double& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( bool& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( char& val )
    {
        /* stub function */
        return *this;
    }
    
    Stream& NetworkStream::operator>> ( String& val )
    {
        /* stub function */
        return *this;
    }

}
