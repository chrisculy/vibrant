/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworkendpoint.h
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

#ifndef VIBRANT_NETWORKENDPOINT_H
#define VIBRANT_NETWORKENDPOINT_H

#include "vstring.h"
#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a network "endpoint" or an IP address with a specific port.
     * 
     * @author Chris Culy
     */
    class VAPI NetworkEndpoint
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param address The IP address or domain name.
             * @param port The port number.
             */
            NetworkEndpoint ( String address, unsigned short port = 0 );

            /**
             * @brief Constructor.
             * 
             * @param address The IP address.
             * @param port The port number.
             */
            NetworkEndpoint ( unsigned long address = INADDR_ANY, unsigned short port = 0 );

            /**
             * @brief Constructor.
             * 
             * @param socketAddress The endpoint information stored
             *      in a system-specific socket Internet address object.
             */
            NetworkEndpoint ( SystemSocketInternetAddress* socketAddress );

            /**
             * @brief Copy constructor.
             * 
             * @param endpoint The network endpoint to copy.
             */
            NetworkEndpoint ( const NetworkEndpoint& endpoint );

            /**
             * @brief Retrieves the network endpoint's IP address.
             * 
             * @return The IP address (as a long integer).
             */
            unsigned long GetAddress ();

            /**
             * @brief Retrieves the network endpoint's IP
             * address as a human readable string.
             * 
             * @return The IP address (as a string).
             */
            String GetAddressAsString ();

            /**
             * @brief Retrieves the network endpoint's hostname.
             * 
             * @return The hostname.
             */
            String GetHostname ();

            /**
             * @brief Retrieves the network endpoint's port number.
             * 
             * @return The port number.
             */
            unsigned short GetPort ();

            /**
             * @brief Retrieves the corresponding system-specific
             * socket Internet address object.
             * 
             * @return The system-specific socket address object.
             */
            SystemSocketInternetAddress GetSocketAddress ();

            /**
             * @brief Sets the network endpoint's IP address.
             * 
             * @param ipAddress The IP address.
             */
            void SetAddress ( const unsigned long& ipAddress );

            /**
             * @brief Sets the network endpoint's IP address
             * by resolving the given address (given as a domain
             * or a normal IP address).
             * 
             * @param address The address (as a domain or IP address).
             */
            void SetAddress ( const String& address );

            /**
             * @brief Sets the network endpoint's port number.
             * 
             * @param port The port number.
             */
            void SetPort ( const unsigned short& port );

            /**
             * @brief Retrieves whether the given network endpoints are equal.
             * 
             * @param endpoint The endpoint to compare to.
             * @return <code>true</code> if the endpoints are equal;
             *      <code>false</code> otherwise.
             */
            bool operator== ( const NetworkEndpoint& endpoint );

            /**
             * @brief Retrieves whether the given network endpoints are equal.
             * 
             * @param endpoint The endpoint to compare to.
             * @return <code>true</code> if the endpoints are equal;
             *      <code>false</code> otherwise.
             */
            bool operator== ( const NetworkEndpoint& endpoint ) const;

            /**
             * @brief Retreives whether the given network endpoint is less than
             * this network endpoint.
             * 
             * @param endpoint The endpoint to compare to.
             * @return <code>true</code> if the given endpoint is
             *      less than this endpoint;<code>false</code> otherwise.
             */
            bool operator< ( const NetworkEndpoint& endpoint );

            /**
             * @brief Retreives whether the given network endpoint is less than
             * this network endpoint.
             * 
             * @param endpoint The endpoint to compare to.
             * @return <code>true</code> if the given endpoint is
             *      less than this endpoint;<code>false</code> otherwise.
             */
            bool operator< ( const NetworkEndpoint& endpoint ) const;

            //************************ General Interface ***********************//

        private:
            
            /**
             * @brief Sets the network endpoint's address from
             * a system-specific socket Internet address object.
             * 
             * @param socketAddress The address information stored
             *      in a system-specific socket Internet address object.
             */
            void SetAddress ( SystemSocketInternetAddress* socketAddress );

            /** @brief Holds the IP address. */
            unsigned long address;

            /** @brief Holds the port number. */
            unsigned short port;
    };

}

#endif
