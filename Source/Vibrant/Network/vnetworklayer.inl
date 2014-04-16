/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworklayer.inl
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

#include "vnetworkendpoint.h"
#include "vsocket.h"

namespace Vibrant
{
    
    String NetworkLayer::Error ()
    {
        return NetworkLayer::errorMessage;
    }
    
    SystemSocket NetworkLayer::CreateSocket ( SocketType type )
    {
        // Initialize the network socket system if
        // this is the first socket being created.
        if ( NetworkLayer::activeSocketCount == 0 )
        {
            NetworkLayer::StartSystem ();
        }

        // Create the socket and update the active socket
        // count if the socket was created successfully.
        SystemSocket result = socket ( PF_INET, ( type == SOCKET_TCP ) ? SOCK_STREAM : SOCK_DGRAM, 0 );
        if ( result != NetworkLayer::NETWORK_INVALID_SOCKET )
        {
            NetworkLayer::activeSocketCount++;
        }
        else
        {
            // Set the error message.
            NetworkLayer::SetError ( "Failed to create socket: " );
        }
        
        return result;
    }
    
    bool NetworkLayer::CloseSocket ( SystemSocket socketDescriptor )
    {
        bool result = true;
        
        // Make sure we are not trying to close an invalid socket.
        if ( socketDescriptor != NetworkLayer::NETWORK_INVALID_SOCKET )
        {
#ifdef WIN32
            if ( closesocket ( socketDescriptor ) == 0 )
#elif
            if ( close ( socketDescriptor ) == 0 )
#endif
            {
                // The socket was successfully closed, so
                // update the number of active sockets.
                NetworkLayer::activeSocketCount--;
            }
            else
            {
                result = NetworkLayer::SetError ( "Failed to close socket: " );
            }
        }

        // Shut down the network socket system if
        // there are no more active sockets.
        if ( NetworkLayer::activeSocketCount == 0 )
        {
            NetworkLayer::ShutdownSystem ();
        }
        return result;
    }
    
    bool NetworkLayer::GetAddressInfo ( String address, SystemAddressInfo** addressInfo )
    {
        if ( ::getaddrinfo ( address.CString (), null, null, addressInfo ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to retrieve address info: " );
        }
        return true;
    }
    
    bool NetworkLayer::GetHostname ( SystemSocketInternetAddress address, String* hostname )
    {
        static const int HOSTNAME_LENGTH = 256;
        char hostnameCString[ HOSTNAME_LENGTH ];
        
        if ( ::getnameinfo ( (SystemSocketAddress*) &address, sizeof(SystemSocketInternetAddress), hostnameCString, HOSTNAME_LENGTH, null,
            null, null ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to retrieve name info: " );
        }
        ( *hostname ) = hostnameCString;
        return true;
    }
    
    bool NetworkLayer::GetSocketOption ( Socket* socket, int option, int& value )
    {
        int valueSize = sizeof(int);
        if ( ::getsockopt ( socket->GetSocketDescriptor (), SOL_SOCKET, option, (char*) &value, &valueSize ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to get socket option: " );
        }
        return true;
    }
    
    bool NetworkLayer::SetSocketOption ( Socket* socket, int option, const int value )
    {
        if ( ::setsockopt ( socket->GetSocketDescriptor (), SOL_SOCKET, option, (char*) &value, sizeof(int) ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to set socket option: " );
        }
        return true;
    }
    
    Socket* NetworkLayer::Accept ( Socket* socket )
    {
        // If we are using a UDP protocol, then return null
        // because we don't need to accept a socket to get the packets.
        if ( socket->GetSocketType () == SOCKET_UDP || socket->GetSocketType () == SOCKET_RELIABLE_UDP )
        {
            return null;
        }

        static int sockAddrSize = sizeof(SystemSocketAddress);
        SystemSocketInternetAddress socketAddress;
        SystemSocket acceptedSystemSocket =
            ::accept ( socket->GetSocketDescriptor (), (SystemSocketAddress*) &socketAddress, &sockAddrSize );
        if ( acceptedSystemSocket == NetworkLayer::NETWORK_INVALID_SOCKET )
        {
            NetworkLayer::SetError ( "Failed to accept: " );
            return null;
        }
        
        return new Socket ( socket->GetSocketType (), acceptedSystemSocket, &socketAddress );
    }
    
    bool NetworkLayer::Bind ( Socket* socket, NetworkEndpoint* endpoint )
    {
        SystemSocketInternetAddress systemSocketAddress = endpoint->GetSocketAddress ();
        if ( ::bind ( socket->GetSocketDescriptor (), (SystemSocketAddress*) &systemSocketAddress, sizeof(SystemSocketAddress) ) == -1 )
        {
            return NetworkLayer::SetError ( "Failed to bind a socket: " );
        }
        return true;
    }
    
    bool NetworkLayer::Connect ( Socket* socket, NetworkEndpoint* endpoint )
    {
        SystemSocketInternetAddress systemSocketAddress = endpoint->GetSocketAddress ();
        if ( ::connect ( socket->GetSocketDescriptor (), (SystemSocketAddress*) &systemSocketAddress, sizeof(SystemSocketAddress) ) == -1 )
        {
            return NetworkLayer::SetError ( "Failed to connect: " );
        }
        return true;
    }
    
    bool NetworkLayer::Listen ( Socket* socket, const unsigned short connectionCapacity )
    {
        // If we are using a UDP protocol, then return
        // because we don't need to listen on a port to
        // get a socket to send to and receive from.
        if ( socket->GetSocketType () == SOCKET_UDP || socket->GetSocketType () == SOCKET_RELIABLE_UDP )
        {
            return true;
        }

        if ( ::listen ( socket->GetSocketDescriptor (), connectionCapacity ) == -1 )
        {
            return NetworkLayer::SetError ( "Failed to listen: " );
        }
        return true;
    }
    
    bool NetworkLayer::ReceiveTCP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_TCP )
        {
            throw IllegalArgumentException ( "NetworkLayer::ReceiveTCP - Attempted to receive using TCP on a non-TCP socket." );
        }

        // Make sure the socket is either bound or connected.
        if ( !( socket->IsBound () || socket->IsConnected () ) )
        {
            throw IllegalArgumentException (
                "NetworkLayer::ReceiveTCP - Attempted to receive using a socket that has not been connected or bound." );
        }
        
        return NetworkLayer::ReceiveBytes ( socket, buffer, offset, count );
    }
    
    bool NetworkLayer::ReceiveUDP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_UDP && socket->GetSocketType () != SOCKET_RELIABLE_UDP )
        {
            throw IllegalArgumentException ( "NetworkLayer::ReceiveUDP - Attempted to receive using UDP on a non-UDP socket" );
        }

        // Make sure the socket is either bound or connected.
        if ( !( socket->IsBound () || socket->IsConnected () ) )
        {
            throw IllegalArgumentException (
                "NetworkLayer::ReceiveUDP - Attempted to receive using a socket that has not been connected or bound." );
        }
        
        return NetworkLayer::ReceiveBytes ( socket, buffer, offset, count );
    }
    
    bool NetworkLayer::ReceiveUDP ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count,
        NetworkEndpoint* source )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_UDP && socket->GetSocketType () != SOCKET_RELIABLE_UDP )
        {
            throw IllegalArgumentException ( "NetworkLayer::ReceiveUDP - Attempted to receive using UDP on a non-UDP socket" );
        }

        // Validate the source network endpoint object.
        if ( source == null )
        {
            throw NullPointerException ( "NetworkLayer::ReceiveUDP - Attempted to receive data using UDP with a null source." );
        }

        unsigned short bytesReceived = 0;
        byte* bytePtr = &buffer[ offset ];
        int result = 0;
        int size = sizeof(SystemSocketInternetAddress);
        SystemSocketInternetAddress socketAddress;
        while ( bytesReceived < count )
        {
            result = ::recvfrom ( socket->GetSocketDescriptor (), (NetworkLayer::NETWORK_DATA) bytePtr, count - bytesReceived, 0,
                (SystemSocketAddress*) &socketAddress, &size );
            // Check for errors receiving.
            if ( result == -1 )
            {
                return NetworkLayer::SetError ( "Failed to receive: " );
            }
            bytesReceived += result;
            bytePtr += result;
        }
        // Fill the network endpoint information.
        *source = NetworkEndpoint ( &socketAddress );
        return true;
    }
    
    bool NetworkLayer::SendTCP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_TCP )
        {
            throw IllegalArgumentException ( "NetworkLayer::SendTCP - Attempted to send using TCP on a non-TCP socket." );
        }

        // Make sure the socket is connected.
        if ( !socket->IsConnected () )
        {
            throw IllegalArgumentException ( "NetworkLayer::SendTCP - Attempted to send using an unconnected socket." );
        }
        
        return NetworkLayer::SendBytes ( socket, buffer, offset, count );
    }
    
    bool NetworkLayer::SendUDP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_UDP && socket->GetSocketType () != SOCKET_RELIABLE_UDP )
        {
            throw IllegalArgumentException ( "NetworkLayer::SendUDP - Attempted to send using UDP on a non-UDP socket." );
        }

        // Make sure the socket is connected.
        if ( !socket->IsConnected () )
        {
            throw IllegalArgumentException ( "NetworkLayer::SendUDP - Attempted to send using an unconnected socket." );
        }
        
        return NetworkLayer::SendBytes ( socket, buffer, offset, count );
    }
    
    bool NetworkLayer::SendUDP ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count,
        NetworkEndpoint* destination )
    {
        // Validate the socket's type.
        if ( socket->GetSocketType () != SOCKET_UDP && socket->GetSocketType () != SOCKET_RELIABLE_UDP )
        {
            throw IllegalArgumentException ( "NetworkLayer::SendUDP - Attempted to send using UDP on a non-UDP socket." );
        }

        // Validate the data's destination.
        if ( destination == null )
        {
            throw NullPointerException ( "NetworkLayer::SendUDP - Attempted to send data using UDP to a null destination." );
        }

        unsigned short bytesSent = 0;
        byte* bytePtr = const_cast< byte* > ( &buffer[ offset ] );
        int result = 0;
        while ( bytesSent < count )
        {
            SystemSocketInternetAddress destinationSystemSocketAddress = destination->GetSocketAddress ();
            result = ::sendto ( socket->GetSocketDescriptor (), (NetworkLayer::NETWORK_DATA) bytePtr, count - bytesSent, 0,
                (SystemSocketAddress*) &destinationSystemSocketAddress, sizeof(SystemSocketInternetAddress) );
            // Check for errors sending.
            if ( result == -1 )
            {
                return NetworkLayer::SetError ( "Failed to send: " );
            }
            bytePtr += result;
            bytesSent += result;
        }
        return true;
    }
    
    bool NetworkLayer::Select ( LinkedList< Socket* >* checkReceiveReady, LinkedList< Socket* >* checkSendReady,
        LinkedList< Socket* >* checkHasError, unsigned int timeout )
    {
        // Holds the socket sets and the pointers to them.
        fd_set receiveSet;
        fd_set sendSet;
        fd_set errorSet;
        
        fd_set* receiveSetPtr = null;
        fd_set* sendSetPtr = null;
        fd_set* errorSetPtr = null;
        
        // Holds the highest socket handle.
        SystemSocket socketHandle = 0;
        
        // Fill the sets and set the socket set pointers appropriately.
        if ( checkReceiveReady != null )
        {
            FD_ZERO ( &receiveSet );
            
            LinkedList< Socket* >::Iterator< Socket* > iter = checkReceiveReady->StartIterator ();
            while ( iter != checkReceiveReady->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                FD_SET ( currentSocket, &receiveSet );
                if ( currentSocket > socketHandle )
                {
                    socketHandle = currentSocket;
                }
                iter.Next ();
            }
            
            receiveSetPtr = &receiveSet;
        }
        if ( checkSendReady != null )
        {
            FD_ZERO ( &sendSet );
            
            LinkedList< Socket* >::Iterator< Socket* > iter = checkSendReady->StartIterator ();
            while ( iter != checkSendReady->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                FD_SET ( currentSocket, &sendSet );
                if ( currentSocket > socketHandle )
                {
                    socketHandle = currentSocket;
                }
                iter.Next ();
            }
            
            sendSetPtr = &sendSet;
        }
        if ( checkHasError != null )
        {
            FD_ZERO ( &errorSet );
            
            LinkedList< Socket* >::Iterator< Socket* > iter = checkHasError->StartIterator ();
            while ( iter != checkHasError->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                FD_SET ( currentSocket, &errorSet );
                if ( currentSocket > socketHandle )
                {
                    socketHandle = currentSocket;
                }
                iter.Next ();
            }
            
            errorSetPtr = &errorSet;
        }

        // Set the timeout (converting from milliseconds to microseconds).
        timeval timeoutValue;
        timeoutValue.tv_sec = 0;
        timeoutValue.tv_usec = timeout * 1000;
        
        // Poll the socket sets with the given socket sets.
        if ( ::select ( socketHandle + 1, receiveSetPtr, sendSetPtr, errorSetPtr, &timeoutValue ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to poll socket state (select): " );
        }

        // Adjust the lists passed in to match with the socket sets returned from select().
        if ( checkReceiveReady != null )
        {
            LinkedList< Socket* >::Iterator< Socket* > iter = checkReceiveReady->StartIterator ();
            while ( iter != checkReceiveReady->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                if ( !FD_ISSET ( currentSocket, &receiveSet ) )
                {
                    checkReceiveReady->Remove ( iter );
                }
                iter.Next ();
            }
        }
        if ( checkSendReady != null )
        {
            LinkedList< Socket* >::Iterator< Socket* > iter = checkSendReady->StartIterator ();
            while ( iter != checkSendReady->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                if ( !FD_ISSET ( currentSocket, &sendSet ) )
                {
                    checkSendReady->Remove ( iter );
                }
                iter.Next ();
            }
        }
        if ( checkHasError != null )
        {
            LinkedList< Socket* >::Iterator< Socket* > iter = checkHasError->StartIterator ();
            while ( iter != checkHasError->EndIterator () )
            {
                SystemSocket currentSocket = iter.GetObject ()->GetSocketDescriptor ();
                if ( !FD_ISSET ( currentSocket, &errorSet ) )
                {
                    checkHasError->Remove ( iter );
                }
                iter.Next ();
            }
        }
        
        return true;
    }
    
    bool NetworkLayer::Shutdown ( Socket* socket, int shutdownType )
    {
        if ( ::shutdown ( socket->GetSocketDescriptor (), shutdownType ) != 0 )
        {
            return NetworkLayer::SetError ( "Failed to shutdown socket connection: " );
        }
        return true;
    }
    
    bool NetworkLayer::ReceiveBytes ( Socket* socket, byte* buffer, const unsigned short offset, const unsigned short count )
    {
        unsigned short bytesReceived = 0;
        byte* bytePtr = &buffer[ offset ];
        int result = 0;
        while ( bytesReceived < count )
        {
            result = ::recv ( socket->GetSocketDescriptor (), (NetworkLayer::NETWORK_DATA) bytePtr, count - bytesReceived, 0 );
            // Check for errors receiving.
            if ( result == -1 )
            {
                return NetworkLayer::SetError ( "Failed to receive: " );
            }
            bytesReceived += result;
            bytePtr += result;
        }
        return true;
    }
    
    bool NetworkLayer::SendBytes ( Socket* socket, const byte* buffer, const unsigned short offset, const unsigned short count )
    {
        unsigned short bytesSent = 0;
        byte* bytePtr = const_cast< byte* > ( &buffer[ offset ] );
        int result = 0;
        while ( bytesSent < count )
        {
            result = ::send ( socket->GetSocketDescriptor (), (NetworkLayer::NETWORK_DATA) bytePtr, count - bytesSent, 0 );
            // Check for errors sending.
            if ( result == -1 )
            {
                return NetworkLayer::SetError ( "Failed to send: " );
            }
            bytesSent += result;
            bytePtr += result;
        }
        return true;
    }
    
// Windows network errors (Winsock).
#ifdef WIN32
    
    bool NetworkLayer::SetError ( String errorMessagePrefix )
    {
        // If there is an error worth noting, then
        // store it with the given prefix.
        if ( WSAGetLastError () != 0 )
        {
            NetworkLayer::errorMessage = errorMessagePrefix;
            
            // Append the appropriate error message.
            int winsockError = WSAGetLastError ();
            switch ( winsockError )
            {
                case WSAEINTR:
                    NetworkLayer::errorMessage += "Interrupted system call.";
                    break;
                case WSAEBADF:
                    NetworkLayer::errorMessage += "Bad file number.";
                    break;
                case WSAEACCES:
                    NetworkLayer::errorMessage += "Permission denied.";
                    break;
                case WSAEFAULT:
                    NetworkLayer::errorMessage += "Bad address.";
                    break;
                case WSAEINVAL:
                    NetworkLayer::errorMessage += "Invalid argument.";
                    break;
                case WSAEMFILE:
                    NetworkLayer::errorMessage += "Too many open sockets.";
                    break;
                case WSAEWOULDBLOCK:
                    NetworkLayer::errorMessage += "Operation would block.";
                    break;
                case WSAEINPROGRESS:
                    NetworkLayer::errorMessage += "Operation now in progress.";
                    break;
                case WSAEALREADY:
                    NetworkLayer::errorMessage += "Operation already in progress.";
                    break;
                case WSAENOTSOCK:
                    NetworkLayer::errorMessage += "Socket operation on non-socket.";
                    break;
                case WSAEDESTADDRREQ:
                    NetworkLayer::errorMessage += "Destination address required.";
                    break;
                case WSAEMSGSIZE:
                    NetworkLayer::errorMessage += "Message too long.";
                    break;
                case WSAEPROTOTYPE:
                    NetworkLayer::errorMessage += "Protocol wrong type for socket.";
                    break;
                case WSAENOPROTOOPT:
                    NetworkLayer::errorMessage += "Bad protocol option.";
                    break;
                case WSAEPROTONOSUPPORT:
                    NetworkLayer::errorMessage += "Protocol not supported.";
                    break;
                case WSAESOCKTNOSUPPORT:
                    NetworkLayer::errorMessage += "Socket type not supported.";
                    break;
                case WSAEOPNOTSUPP:
                    NetworkLayer::errorMessage += "Operation not supported on socket.";
                    break;
                case WSAEPFNOSUPPORT:
                    NetworkLayer::errorMessage += "Protocol family not supported.";
                    break;
                case WSAEAFNOSUPPORT:
                    NetworkLayer::errorMessage += "Address family not supported.";
                    break;
                case WSAEADDRINUSE:
                    NetworkLayer::errorMessage += "Address already in use.";
                    break;
                case WSAEADDRNOTAVAIL:
                    NetworkLayer::errorMessage += "Can't assign requested address.";
                    break;
                case WSAENETDOWN:
                    NetworkLayer::errorMessage += "Network is down.";
                    break;
                case WSAENETUNREACH:
                    NetworkLayer::errorMessage += "Network is unreachable.";
                    break;
                case WSAENETRESET:
                    NetworkLayer::errorMessage += "Net connection reset.";
                    break;
                case WSAECONNABORTED:
                    NetworkLayer::errorMessage += "Software caused connection abort.";
                    break;
                case WSAECONNRESET:
                    NetworkLayer::errorMessage += "Connection reset by peer.";
                    break;
                case WSAENOBUFS:
                    NetworkLayer::errorMessage += "No buffer space available.";
                    break;
                case WSAEISCONN:
                    NetworkLayer::errorMessage += "Socket is already connected.";
                    break;
                case WSAENOTCONN:
                    NetworkLayer::errorMessage += "Socket is not connected.";
                    break;
                case WSAESHUTDOWN:
                    NetworkLayer::errorMessage += "Can't send after socket shutdown.";
                    break;
                case WSAETOOMANYREFS:
                    NetworkLayer::errorMessage += "Too many references, can't splice.";
                    break;
                case WSAETIMEDOUT:
                    NetworkLayer::errorMessage += "Connection timed out.";
                    break;
                case WSAECONNREFUSED:
                    NetworkLayer::errorMessage += "Connection refused.";
                    break;
                case WSAELOOP:
                    NetworkLayer::errorMessage += "Too many levels of symbolic links.";
                    break;
                case WSAENAMETOOLONG:
                    NetworkLayer::errorMessage += "File name too long.";
                    break;
                case WSAEHOSTDOWN:
                    NetworkLayer::errorMessage += "Host is down.";
                    break;
                case WSAEHOSTUNREACH:
                    NetworkLayer::errorMessage += "No route to host.";
                    break;
                case WSAENOTEMPTY:
                    NetworkLayer::errorMessage += "Directory not empty.";
                    break;
                case WSAEPROCLIM:
                    NetworkLayer::errorMessage += "Too many processes.";
                    break;
                case WSAEUSERS:
                    NetworkLayer::errorMessage += "Too many users.";
                    break;
                case WSAEDQUOT:
                    NetworkLayer::errorMessage += "Disc quota exceeded.";
                    break;
                case WSAESTALE:
                    NetworkLayer::errorMessage += "Stale NFS file handle.";
                    break;
                case WSAEREMOTE:
                    NetworkLayer::errorMessage += "Too many levels of remote in path.";
                    break;
                case WSASYSNOTREADY:
                    NetworkLayer::errorMessage += "Network system is unavailable.";
                    break;
                case WSAVERNOTSUPPORTED:
                    NetworkLayer::errorMessage += "Winsock version out of range.";
                    break;
                case WSANOTINITIALISED:
                    NetworkLayer::errorMessage += "WSAStartup not yet called.";
                    break;
                case WSAEDISCON:
                    NetworkLayer::errorMessage += "Graceful shutdown in progress.";
                    break;
                case WSAHOST_NOT_FOUND:
                    NetworkLayer::errorMessage += "Host not found.";
                    break;
                case WSANO_DATA:
                    NetworkLayer::errorMessage += "No host data of that type was found.";
                    break;
                default:
                    NetworkLayer::errorMessage += "Unknown error.";
                    break;
            }

            NetworkLayer::errorMessage += "\n";
            return false;
        }
        
        return true;
    }
    
// BSD Sockets
#else
    
#include <errno.h>
    
    bool NetworkLayer :: SetError ( String errorMessagePrefix )
    {
        // If there is an error worth noting, then
        // store it with the given prefix.
        if ( true /* errno != 0 */)
        {
            NetworkLayer::errorMessage = errorMessagePrefix;

            // Append the appropriate error message.
            NetworkLayer::errorMessage += strerror ( errno );
            NetworkLayer::errorMessage += "\n";
            return false;
        }

        return true;
    }

#endif
    
    void NetworkLayer::StartSystem ()
    {
#ifdef WIN32
        // Use version 2.2 of Winsock.
        WSAData wsaData;
        if ( WSAStartup ( MAKEWORD ( 2, 2 ), &wsaData ) != 0 )
        {
            throw NetworkException ( "NetworkLayer::StartSystem - Winsock could not be initialized.\n" );
        }
#else   // BSD Sockets
#endif
    }
    
    void NetworkLayer::ShutdownSystem ()
    {
#ifdef WIN32
        // Shut down Winsock.
        if ( WSACleanup () != 0 )
        {
            throw NetworkException ( "NetworkLayer::ShutdownSystem - Winsock could not clean up properly.\n" );
        }
#else   // BSD Sockets
#endif
    }

}
