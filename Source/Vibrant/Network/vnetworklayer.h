/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworklayer.h
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

#ifndef VIBRANT_NETWORKLAYER_H
#define VIBRANT_NETWORKLAYER_H

#include "vlinkedlist.h"
#include "vsockettype.h"
#include "vstring.h"
#include "vsystem.h"

namespace Vibrant
{
    
    // Forward class declarations.
    class NetworkEndpoint;
    class Socket;
    
    /**
     * @brief Provides low-level cross-platform network socket functionality.
     * 
     * <p>
     * Note: This is designed to be used very closely with {@link Socket}.
     * </p>
     * 
     * @see Socket
     * @author Chris Culy
     */
    class VAPI NetworkLayer
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Retrieves the latest error.
             * 
             * @return The latest error.
             */
            static inline String Error ();

            /**
             * @brief Creates a socket of the given type (or protocol).
             * 
             * @param type The type or protocol of the socket.
             * @return The system socket handle or descriptor.
             */
            static inline SystemSocket CreateSocket ( SocketType type );

            /**
             * @brief Closes the given socket.
             * 
             * @param socketDescriptor The system socket handle or descriptor of the socket to be closed.
             * @return <code>true</code> if the socket was closed successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool CloseSocket ( SystemSocket socketDescriptor );

            /**
             * @brief Retrieves the network address info for the given address.
             * 
             * @param address The address (an IP address as a string or any domain or host name).
             * @param addressInfo The address info (filled by the function).
             * @return <code>true</code> if the address info was retrieved successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool GetAddressInfo ( String address, SystemAddressInfo** addressInfo );

            /**
             * @brief Retrieves the hostname (or domain name) for the given internet address.
             * 
             * @param address The system internet address to retrieve a hostname for.
             * @param hostname The hostname (filled by the function).
             * @return <code>true</code> if the hostname was retrieved successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool GetHostname ( SystemSocketInternetAddress address, String* hostname );

            /**
             * @brief Retrieves the given socket option's value.
             * 
             * @param socket The socket to retrieve the socket option for.
             * @param option The option to retrieve.
             * @param value The option's value (filled by the function).
             * @return <code>true</code> if the socket option is retrieved successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool GetSocketOption ( Socket* socket, int option, int& value );

            /**
             * @brief Sets the given socket option.
             * 
             * @param socket The socket to set the socket option for.
             * @param option The option to set.
             * @param value The option's value.
             * @return <code>true</code> if the socket option was set succesfully;
             *      <code>false</code> otherwise.
             */
            static inline bool SetSocketOption ( Socket* socket, int option, const int value );

            /**
             * @brief Accepts a socket for the given socket.
             * 
             * @param socket The socket to accept a socket for.
             * @return The accepted socket or <code>null</code> if an error
             *      occurred or there is no socket to accept.
             */
            static inline Socket* Accept ( Socket* socket );

            /**
             * @brief Binds the given socket to the given network endpoint.
             * 
             * @param socket The socket to bind.
             * @param endpoint The network endpoint to bind the socket to.
             * @return <code>true</code> if the socket is bound successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool Bind ( Socket* socket, NetworkEndpoint* endpoint );

            /**
             * @brief Connects the given socket to the given network endpoint.
             * 
             * @param socket The socket to connect.
             * @param endpoint The network endpoint to connect the socket to.
             * @return <code>true</code> if the socket is connected successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool Connect ( Socket* socket, NetworkEndpoint* endpoint );

            /**
             * @brief Listens on the given socket on its bound port/network endpoint.
             * 
             * @param socket The socket to listen on.
             * @param connectionCapacity The number of connections to allow
             *      to "back-up" before accepting them.
             */
            static inline bool Listen ( Socket* socket, const unsigned short connectionCapacity );

            /**
             * @brief Receives data using the TCP protocol.
             * 
             * @param socket The socket to use when receiving the data.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @return <code>true</code> if the data was received successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the TCP protocol.
             * @throws IllegalArgumentException If the socket is not bound or connected.
             */
            static inline bool ReceiveTCP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Receives data using the UDP protocol from the bound/connected network endpoint.
             * 
             * @param socket The socket to use when receiving the data.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @return <code>true</code> if the data was received successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the UDP protocol.
             * @throws IllegalArgumentException If the socket is not bound or connected.
             */
            static inline bool ReceiveUDP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Receives data using the UDP protocol from an unknown source.
             * 
             * @param socket The socket to use when receiving the data.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @param source A network endpoint object to be filled with the source of the data.
             * @return <code>true</code> if the data was received successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the UDP protocol.
             * @throws NullPointerException If <code>source</code> is <code>null</code>.
             */
            static inline bool ReceiveUDP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count,
                NetworkEndpoint* source );

            /**
             * @brief Sends data using the TCP protocol.
             * 
             * @param socket The socket to use when sending the data.
             * @param buffer The buffer to send from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to send (<code>byte</code>s).
             * @return <code>true</code> if the data was sent successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the TCP protocol.
             * @throws IllegalArgumentException If the socket is not bound or connected.
             */
            static inline bool SendTCP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Sends data using the UDP protocol to the bound/connected network endpoint.
             * 
             * @param socket The socket to use when sending the data.
             * @param buffer The buffer to send from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to send (<code>byte</code>s).
             * @return <code>true</code> if the data was sent successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the UDP protocol.
             * @throws IllegalArgumentException If the socket is not bound or connected.
             */
            static inline bool SendUDP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Sends data using the UDP protocol to the given network endpoint.
             * 
             * @param socket The socket to use when sending the data.
             * @param buffer The buffer to send from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to send (<code>byte</code>s).
             * @param destination The destination network endpoint.
             * @return <code>true</code> if the data was sent successfully;
             *      <code>false</code> otherwise.
             * @throws IllegalArgumentException If the socket does not support the UDP protocol.
             * @throws NullPointerException If <code>destination</code> is <code>null</code>.
             */
            static inline bool SendUDP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count,
                NetworkEndpoint* destination );

            /**
             * @brief Checks the given lists of sockets for a specific state.
             * 
             * @param checkReceiveReady The list of sockets to check if
             *      they are ready to receive data.
             * @param checkSendReady The list of sockets to check if
             *      they are ready to send data.
             * @param checkHasError The list of sockets to check if
             *      they have errors.
             * @param timeout The amount of time to try checking the states
             *      of the sockets before giving up (in milliseconds).
             * @return <code>true</code> if the socket states were checked
             *      successfully;<code>false</code> if the request timed out.
             */
            static inline bool Select ( LinkedList< Socket* >* checkReceiveReady, LinkedList< Socket* >* checkSendReady, LinkedList<
                Socket* >* checkHasError, unsigned int timeout = 0 );

            /**
             * @brief Shuts down the connections in the given direction(s).
             * 
             * @param socket The socket to shut down.
             * @param shutdownType Whether the connection should be shut down
             *      so that not further data is 1) received, 2) sent, or 3) both.
             * @return <code>true</code> if the socket connections were shut down
             *      successfully;<code>false</code> otherwise.
             */
            static inline bool Shutdown ( Socket* socket, int shutdownType );

            //************************ General Interface ***********************//

        private:
            
            //************************ General Interface ***********************//

            /**
             * @brief Generically receives bytes.
             * 
             * @param socket The socket to use when receiving the packet.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @return <code>true</code> if the data was received successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool ReceiveBytes ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Generically sends bytes.
             * 
             * @param socket The socket to use when sending the packet.
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to write (<code>byte</code>s).
             * @return <code>true</code> if the data was sent successfully;
             *      <code>false</code> otherwise.
             */
            static inline bool SendBytes ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Stores the current error with the given
             * error message prefix if there is a noteworthy error.
             * 
             * @param errorMessagePrefix The error message prefix.
             * @return <code>true</code> if there was <b>no</b> noteworthy error
             *      that was stored;<code>false</code> otherwise. (This allows
             *      boolean functions to return like this: 
             *      <code>return error ("Error message...");</code> and still
             *      preserve the behavior that returning <code>true</code> 
             *      indicates a succesful function run.)
             */
            static inline bool SetError ( String errorMessagePrefix );

            /**
             * @brief Starts the network socket system
             * (initializes the OS socket layer).
             * 
             * @see NetworkLayer#ShutdownSystem()
             */
            static inline void StartSystem ();

            /**
             * @brief Shuts down the network socket system.
             * 
             * @see NetworkLayer#StartSystem()
             */
            static inline void ShutdownSystem ();

            /** @brief Holds the number of active sockets. */
            static int activeSocketCount;

            /** @brief Holds the latest error message. */
            static String errorMessage;

#ifdef WIN32
            // Winsock
            
            /** @brief Holds the invalid socket constant. */
            static const unsigned int NETWORK_INVALID_SOCKET = INVALID_SOCKET;

            /** @brief Represents the type of data sent across the network. */
            typedef char* NETWORK_DATA;
            
#else
            // BSD Sockets
            
            /** @brief Holds the invalid socket constant. */
            static const int NETWORK_INVALID_SOCKET = -1;

            /** @brief Represents the type of data sent across the network. */
            typedef void* NETWORK_DATA;

#endif
            
            //************************ General Interface ***********************//
    };

}

#include "vnetworklayer.inl"

#endif
