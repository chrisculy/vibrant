/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworkendpoint.cpp
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

#include "vnetworklayer.h"
#include "vnetworkendpoint.h"

namespace Vibrant
{
    
    NetworkEndpoint::NetworkEndpoint ( String address, unsigned short port )
    {
        this->SetAddress ( address );
        this->SetPort ( port );
    }
    
    NetworkEndpoint::NetworkEndpoint ( unsigned long address, unsigned short port )
    {
        this->SetAddress ( address );
        this->SetPort ( port );
    }
    
    NetworkEndpoint::NetworkEndpoint ( SystemSocketInternetAddress* socketAddress )
    {
        this->SetAddress ( socketAddress );
        this->port = socketAddress->sin_port;
    }
    
    NetworkEndpoint::NetworkEndpoint ( const NetworkEndpoint& endpoint )
    {
        this->address = endpoint.address;
        this->port = endpoint.port;
    }
    
    unsigned long NetworkEndpoint::GetAddress ()
    {
        return ntohl ( this->address );
    }
    
    String NetworkEndpoint::GetAddressAsString ()
    {
        return ::inet_ntoa ( this->GetSocketAddress ().sin_addr );
    }
    
    String NetworkEndpoint::GetHostname ()
    {
        String hostname;
        if ( NetworkLayer::GetHostname ( this->GetSocketAddress (), &hostname ) )
        {
            return hostname;
        }
        return null;
    }
    
    unsigned short NetworkEndpoint::GetPort ()
    {
        return ntohs ( this->port );
    }
    
    SystemSocketInternetAddress NetworkEndpoint::GetSocketAddress ()
    {
        SystemSocketInternetAddress socketAddress;
        socketAddress.sin_family = AF_INET;
#ifdef WIN32
        socketAddress.sin_addr.S_un.S_addr = this->address;
#else
        socketAddress.sin_addr.s_addr = this->address;
#endif
        socketAddress.sin_port = this->port;
        memset ( socketAddress.sin_zero, '\0', sizeof( socketAddress.sin_zero ) );
        
        return socketAddress;
    }
    
    void NetworkEndpoint::SetAddress ( const unsigned long& ipAddress )
    {
        this->address = htonl ( address );
    }
    
    void NetworkEndpoint::SetAddress ( const String& address )
    {
        SystemAddressInfo* addressInfo = null;
        
        // Attempt to resolve the address as a domain or IP address.
        // Note: This should not fail (unless the network itself
        // is not working-i.e. no connection).
        if ( NetworkLayer::GetAddressInfo ( address, &addressInfo ) )
        {
            this->SetAddress ( (SystemSocketInternetAddress*) addressInfo->ai_addr );
        }
        else
        {
            // Attempt to resolve the address as an IP address.
            this->address = inet_addr ( address.CString () );
            
            // If the address is not the broadcast address and we get
            // -1 as the address, vlog an error.
            if ( address != "255.255.255.255" && this->address == INADDR_NONE )
            {
                //vlog << "NetworkEndpoint::setAddress - Could not resolve IP address.\n";
                this->address = htonl ( INADDR_ANY );
            }
        }
    }
    
    void NetworkEndpoint::SetPort ( const unsigned short& port )
    {
        this->port = htons ( port );
    }
    
    bool NetworkEndpoint::operator== ( const NetworkEndpoint& endpoint )
    {
        return this->address == endpoint.address && this->port == endpoint.port;
    }
    
    bool NetworkEndpoint::operator== ( const NetworkEndpoint& endpoint ) const
    {
        return this->address == endpoint.address && this->port == endpoint.port;
    }
    
    bool NetworkEndpoint::operator< ( const NetworkEndpoint& endpoint )
    {
        return this->address < endpoint.address && this->port < endpoint.port;
    }
    
    bool NetworkEndpoint::operator< ( const NetworkEndpoint& endpoint ) const
    {
        return this->address < endpoint.address && this->port < endpoint.port;
    }
    
    void NetworkEndpoint::SetAddress ( SystemSocketInternetAddress* socketAddress )
    {
#ifdef WIN32
        this->address = socketAddress->sin_addr.S_un.S_addr;
#elif
        this->address = socketAddress->sin_addr.s_addr;
#endif
    }

}
