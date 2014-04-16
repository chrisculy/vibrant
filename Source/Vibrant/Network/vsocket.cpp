/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsocket.cpp
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

#include "vlinkedlist.h"
#include "vnetworklayer.h"
#include "vsocket.h"
#include "vsystem.h"
#include "vsystemmanager.h"
#include "vthread.h"
#include "vtime.h"

namespace Vibrant
{
    
    Socket::Socket ( SocketType type )
    {
        this->type = type;
        this->socketDescriptor = NetworkLayer::CreateSocket ( this->type );
        this->boundEndpoint = null;
        this->connectedEndpoint = null;
        if ( type == SOCKET_RELIABLE_UDP )
        {
            this->connectionStates = new Hashtable< NetworkEndpoint*, Socket::ReliableUDPConnectionState* > ();
        }
        else
        {
            this->connectionStates = null;
        }

        // Set static polling lists.
        thisReceiveList.PushBack ( this );
        thisSendList.PushBack ( this );
        thisErrorList.PushBack ( this );
    }
    
    Socket::~Socket ()
    {
        // Close all connections on the socket.
        this->Close ();
        
        // Clean up endpoint structures.
        if ( this->boundEndpoint != null )
        {
            delete this->boundEndpoint;
            this->boundEndpoint = null;
        }
        if ( this->connectedEndpoint != null )
        {
            delete this->connectedEndpoint;
            this->connectedEndpoint = null;
        }
    }
    
    const SocketType& Socket::GetSocketType ()
    {
        return this->type;
    }
    
    const SystemSocket& Socket::GetSocketDescriptor ()
    {
        return this->socketDescriptor;
    }
    
    const NetworkEndpoint* Socket::GetBoundEndpoint ()
    {
        return this->boundEndpoint;
    }
    
    const NetworkEndpoint* Socket::GetConnectedEndpoint ()
    {
        return this->connectedEndpoint;
    }
    
    bool Socket::IsBound ()
    {
        return this->bound;
    }
    
    bool Socket::IsConnected ()
    {
        return this->connected;
    }
    
    Socket* Socket::Accept ()
    {
        return NetworkLayer::Accept ( this );
    }
    
    bool Socket::Bind ( const NetworkEndpoint* endpoint )
    {
        bool result = NetworkLayer::Bind ( this, const_cast< NetworkEndpoint* > ( endpoint ) );
        if ( result )
        {
            this->bound = true;
            
            // Make sure we clean up the old bound endpoint.
            if ( this->boundEndpoint != null )
            {
                delete this->boundEndpoint;
                this->boundEndpoint = null;
            }
            this->boundEndpoint = new NetworkEndpoint ( *endpoint );
        }
        return result;
    }
    
    bool Socket::Connect ( const NetworkEndpoint* endpoint )
    {
        bool result = NetworkLayer::Connect ( this, const_cast< NetworkEndpoint* > ( endpoint ) );
        if ( result )
        {
            this->connected = true;
            
            // Make sure we clean up the old connected endpoint.
            if ( this->connectedEndpoint != null )
            {
                delete this->connectedEndpoint;
                this->connectedEndpoint = null;
            }
            this->connectedEndpoint = new NetworkEndpoint ( *endpoint );
        }
        return result;
    }
    
    bool Socket::Disconnect ( bool reuseSocket )
    {
        // Close all connections on the socket.
        this->Close ();
        
        // If we are going to be able to reuse the socket,
        // clear old state and make the socket usable again.
        if ( reuseSocket )
        {
            this->connected = false;
            this->bound = false;
            
            if ( this->connectedEndpoint != null )
            {
                delete this->connectedEndpoint;
                this->connectedEndpoint = null;
            }
            if ( this->boundEndpoint != null )
            {
                delete this->boundEndpoint;
                this->boundEndpoint = null;
            }
            
            // Recreate the socket's system socket handle.
            this->socketDescriptor = NetworkLayer::CreateSocket ( this->type );
        }
        return true;
    }
    
    bool Socket::Listen ( const unsigned short connectionCapacity )
    {
        return NetworkLayer::Listen ( this, connectionCapacity );
    }
    
    Socket::SocketState Socket::Poll ()
    {
        if ( Socket::Select ( &this->thisReceiveList, &this->thisSendList, &this->thisErrorList ) )
        {
            if ( !this->thisReceiveList.IsEmpty () )
            {
                return Socket::SOCKET_RECEIVE_READY;
            }
            if ( !this->thisSendList.IsEmpty () )
            {
                return Socket::SOCKET_SEND_READY;
            }
            if ( !this->thisErrorList.IsEmpty () )
            {
                return Socket::SOCKET_HAS_ERROR;
            }
        }
        return Socket::SOCKET_HAS_ERROR;
    }
    
    bool Socket::Receive ( byte* buffer, const unsigned short offset, const unsigned short count )
    {
        switch ( this->type )
        {
            case SOCKET_TCP:
                return NetworkLayer::ReceiveTCP ( this, buffer, offset, count );
            case SOCKET_UDP:
                return NetworkLayer::ReceiveUDP ( this, buffer, offset, count );
            case SOCKET_RELIABLE_UDP:
                return this->ReceiveReliableUDP ( buffer, offset, count, null );
        }
        return false;
    }
    
    bool Socket::ReceiveFrom ( byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* source )
    {
        switch ( this->type )
        {
            case SOCKET_UDP:
                return NetworkLayer::ReceiveUDP ( this, buffer, offset, count, source );
            case SOCKET_RELIABLE_UDP:
                return this->ReceiveReliableUDP ( buffer, offset, count, source );
            case SOCKET_TCP:
            default:
                return false;
        }
    }
    
    bool Socket::Send ( const byte* buffer, const unsigned short offset, const unsigned short count )
    {
        switch ( this->type )
        {
            case SOCKET_TCP:
                return NetworkLayer::SendTCP ( this, buffer, offset, count );
            case SOCKET_UDP:
                return NetworkLayer::SendUDP ( this, buffer, offset, count );
            case SOCKET_RELIABLE_UDP:
                return this->SendReliableUDP ( buffer, offset, count, null );
        }
        return false;
    }
    
    bool Socket::SendTo ( const byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* destination )
    {
        switch ( this->type )
        {
            case SOCKET_UDP:
                return NetworkLayer::SendUDP ( this, buffer, offset, count, destination );
            case SOCKET_RELIABLE_UDP:
                return this->SendReliableUDP ( buffer, offset, count, destination );
            case SOCKET_TCP:
            default:
                return false;
        }
    }
    
    bool Socket::Shutdown ( Socket::ShutdownType shutdownType )
    {
        return NetworkLayer::Shutdown ( this, shutdownType );
    }
    
    bool Socket::Select ( LinkedList< Socket* >* checkReceiveReady, LinkedList< Socket* >* checkSendReady,
        LinkedList< Socket* >* checkHasError, unsigned int timeout )
    {
        return NetworkLayer::Select ( checkReceiveReady, checkSendReady, checkHasError, timeout );
    }
    
    void Socket::BeginAccept ( Socket::AsynchSocketCallback callback )
    {
        // Set up the asynchronous state object.
        AcceptState* state = new AcceptState ();
        state->socket = this;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginAccept ( Socket::AsynchSocketCallback callback, AcceptState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginConnect ( Socket::AsynchSocketCallback callback, NetworkEndpoint* endpoint )
    {
        // Set up the asynchronous state object.
        ConnectState* state = new ConnectState ();
        state->socket = this;
        state->endpoint = endpoint;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginConnect ( Socket::AsynchSocketCallback callback, ConnectState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginDisconnect ( Socket::AsynchSocketCallback callback, bool reuseSocket )
    {
        // Set up the asynchronous state object.
        DisconnectState* state = new DisconnectState ();
        state->socket = this;
        state->reuseSocket = reuseSocket;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginDisconnect ( Socket::AsynchSocketCallback callback, DisconnectState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginReceive ( Socket::AsynchSocketCallback callback, byte* buffer, const unsigned short offset,
        const unsigned short count )
    {
        // Set up the asynchronous state object.
        ReceiveState* state = new ReceiveState ();
        state->socket = this;
        state->buffer = buffer;
        state->offset = offset;
        state->count = count;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginReceive ( Socket::AsynchSocketCallback callback, ReceiveState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginReceiveFrom ( Socket::AsynchSocketCallback callback, byte* buffer, const unsigned short offset,
        const unsigned short count, NetworkEndpoint* source )
    {
        // Set up the asynchronous state object.
        ReceiveFromState* state = new ReceiveFromState ();
        state->socket = this;
        state->buffer = buffer;
        state->offset = offset;
        state->count = count;
        state->source = source;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginReceiveFrom ( Socket::AsynchSocketCallback callback, ReceiveFromState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginSend ( Socket::AsynchSocketCallback callback, const byte* buffer, const unsigned short offset,
        const unsigned short count )
    {
        // Set up the asynchronous state object.
        SendState* state = new SendState ();
        state->socket = this;
        state->buffer = const_cast< byte* > ( buffer );
        state->offset = offset;
        state->count = count;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginSend ( Socket::AsynchSocketCallback callback, SendState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginSendTo ( Socket::AsynchSocketCallback callback, const byte* buffer, const unsigned short offset,
        const unsigned short count, NetworkEndpoint* destination )
    {
        // Set up the asynchronous state object.
        SendToState* state = new SendToState ();
        state->socket = this;
        state->buffer = const_cast< byte* > ( buffer );
        state->offset = offset;
        state->count = count;
        state->destination = destination;
        
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::BeginSendTo ( Socket::AsynchSocketCallback callback, SendToState* state )
    {
        Thread::Execute ( (AsynchCallback) callback, state );
    }
    
    void Socket::EndAccept ( Socket::AcceptState* state )
    {
        state->acceptedSocket = state->socket->Accept ();
        state->result = ( state->acceptedSocket != null );
    }
    
    void Socket::EndConnect ( Socket::ConnectState* state )
    {
        state->result = state->socket->Connect ( state->endpoint );
    }
    
    void Socket::EndDisconnect ( Socket::DisconnectState* state )
    {
        state->result = state->socket->Disconnect ( state->reuseSocket );
    }
    
    void Socket::EndReceive ( Socket::ReceiveState* state )
    {
        state->result = state->socket->Receive ( state->buffer, state->offset, state->count );
    }
    
    void Socket::EndReceiveFrom ( Socket::ReceiveFromState* state )
    {
        state->result = state->socket->ReceiveFrom ( state->buffer, state->offset, state->count, state->source );
    }
    
    void Socket::EndSend ( Socket::SendState* state )
    {
        state->result = state->socket->Send ( state->buffer, state->offset, state->count );
    }
    
    void Socket::EndSendTo ( Socket::SendToState* state )
    {
        state->result = state->socket->SendTo ( state->buffer, state->offset, state->count, state->destination );
    }
    
    bool Socket::GetSocketOption ( Socket::SocketOption option )
    {
        int value = 0;
        if ( !NetworkLayer::GetSocketOption ( this, option, value ) )
        {
            // Throw an exception with a specific error message.
            switch ( option )
            {
                case SOCKET_BROADCAST:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'broadcast\'." );
                case SOCKET_DEBUG:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'debug\'." );
                case SOCKET_DO_NOT_ROUTE:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'do not route\'." );
                case SOCKET_KEEP_ALIVE:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'keep alive\'." );
                case SOCKET_LINGER:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'linger\'." );
                case SOCKET_RECEIVE_OOB_DATA:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'receive out of band data\'." );
                case SOCKET_REUSE_ADDRESS:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option \'reuse address\'." );
                default:
                    throw NetworkException ( "Socket::GetSocketOption - Could not get socket option." );
            }
        }
        return value == 0 ? false : true;
    }
    
    int Socket::GetReceiveTimeout ()
    {
        int value = 0;
        if ( !NetworkLayer::GetSocketOption ( this, SO_RCVTIMEO, value ) )
        {
            throw NetworkException ( "Socket::GetReceiveTimeout - Could not get the receive timeout." );
        }
        return value;
    }
    
    int Socket::GetReceiveBufferSize ()
    {
        int value = 0;
        if ( !NetworkLayer::GetSocketOption ( this, SO_RCVBUF, value ) )
        {
            throw NetworkException ( "Socket::GetReceiveBufferSize - Could not get the receive buffer size." );
        }
        return value;
    }
    
    int Socket::GetSendTimeout ()
    {
        int value = 0;
        if ( !NetworkLayer::GetSocketOption ( this, SO_SNDTIMEO, value ) )
        {
            throw NetworkException ( "Socket::GetSendTimeout - Could not get the send timeout." );
        }
        return value;
    }
    
    int Socket::GetSendBufferSize ()
    {
        int value = 0;
        if ( !NetworkLayer::GetSocketOption ( this, SO_SNDBUF, value ) )
        {
            throw NetworkException ( "Socket::GetSendBufferSize - Could not get the send buffer size." );
        }
        return value;
    }
    
    void Socket::SetSocketOption ( Socket::SocketOption option, const bool value )
    {
        if ( !NetworkLayer::SetSocketOption ( this, option, value ? 1 : 0 ) )
        {
            // Throw an exception with a specific error message.
            switch ( option )
            {
                case SOCKET_BROADCAST:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'broadcast\'." );
                case SOCKET_DEBUG:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'debug\'." );
                case SOCKET_DO_NOT_ROUTE:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'do not route\'." );
                case SOCKET_KEEP_ALIVE:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'keep alive\'." );
                case SOCKET_LINGER:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'linger\'." );
                case SOCKET_RECEIVE_OOB_DATA:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'receive out of band data\'." );
                case SOCKET_REUSE_ADDRESS:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option \'reuse address\'." );
                default:
                    throw NetworkException ( "Socket::SetSocketOption - Could not set socket option." );
            }
        }
    }
    
    void Socket::SetReceiveTimeout ( const int timeout )
    {
        if ( !NetworkLayer::SetSocketOption ( this, SO_RCVTIMEO, timeout ) )
        {
            throw NetworkException ( "Socket::SetReceiveTimeout - Could not set the receive timeout." );
        }
    }
    
    void Socket::SetReceiveBufferSize ( const int size )
    {
        if ( !NetworkLayer::SetSocketOption ( this, SO_RCVBUF, size ) )
        {
            throw NetworkException ( "Socket::SetReceiveBufferSize - Could not set the receive buffer size." );
        }
    }
    
    void Socket::SetSendTimeout ( const int timeout )
    {
        if ( !NetworkLayer::SetSocketOption ( this, SO_SNDTIMEO, timeout ) )
        {
            throw NetworkException ( "Socket::SetSendTimeout - Could not set the send timeout." );
        }
    }
    
    void Socket::SetSendBufferSize ( const int size )
    {
        if ( !NetworkLayer::SetSocketOption ( this, SO_SNDBUF, size ) )
        {
            throw NetworkException ( "Socket::SetSendBufferSize - Could not set the send buffer size." );
        }
    }
    
    //******************************************************************//
    //****************** Private Reliable UDP Classes ******************//

    Socket::ReliableUDPPacket::ReliableUDPPacket ()
    {
        this->activatedTime = -1;
        this->timeout = ReliableUDPPacket::DEFAULT_TIMEOUT;
        
        this->packetUID = 0;
        this->data = null;
        this->size = 0;
    }
    
    const byte* Socket::ReliableUDPPacket::GetPacketData ()
    {
        // Get the address of the beginning of the 
        // section of memory that contains the packet
        // members that are to be sent or received into.
        return (byte*) &( this->size );
    }
    
    const unsigned short Socket::ReliableUDPPacket::GetPacketDataSize ()
    {
        // Holds the size of the part of the packet data that never changes
        // (the packet size variable and the packet UID).
        static const unsigned short constantSize = sizeof(unsigned short) + sizeof(unsigned int);
        
        return constantSize + this->size;
    }
    
    void Socket::ReliableUDPPacket::SetPacketData ( byte* data )
    {
        byte* bytePtr = data;
        
        // Set the packet's size.
        this->size = *( (unsigned short*) bytePtr );
        
        // Move the pointer forward and copy the actual data.
        bytePtr += ( sizeof(unsigned short) );
        this->data = new byte[ this->size ];
#ifdef _MSC_VER
        memcpy_s ( this->data, this->size, bytePtr, this->size );
#else
        memcpy ( this->data, bytePtr, this->size );
#endif
        
        // Move the pointer forward and set the packet's UID.
        bytePtr += this->size;
        this->packetUID = *( (unsigned short*) bytePtr );
    }
    
    unsigned int Socket::ReliableUDPPacket::GetNextUID ()
    {
        static unsigned int nextUID = UID_START;
        
        // Wrap around at the end.
        if ( nextUID == USHRT_MAX )
        {
            // Wrap around to 1 since 0 is used to indicate an ACK packet.
            nextUID = 1;
        }
        return nextUID++;
    }
    
    unsigned short Socket::ReliableUDPPacket::GetACKPacketSize ()
    {
        // The size variable, the UID that is being acknowledged, and the packet's UID (0).
        static const unsigned short constantSize = sizeof(unsigned short) + sizeof(unsigned int) + sizeof(unsigned int);
        
        return constantSize;
    }
    
    const unsigned short Socket::ReliableUDPPacket::GetPacketDataSize ( const unsigned short bufferSize )
    {
        // Holds the size of the part of the packet data that never changes
        // (the packet size variable and the packet UID).
        static const unsigned short constantSize = sizeof(unsigned short) + sizeof(unsigned int);
        
        return constantSize + bufferSize;
    }
    
    bool Socket::ReliableUDPPacket::IsAcknowledgmentPacket ( byte* data )
    {
        static ReliableUDPPacket packet;
        byte* bytePtr = data;
        
        // Set the packet's size.
        packet.size = *( (unsigned short*) bytePtr );
        
        // Set the packet's data (this doesn't technically need to be done).
        bytePtr += ( sizeof(unsigned short) );
        packet.data = bytePtr;
        
        // Set the packet's UID.
        bytePtr += ( sizeof(unsigned int) );
        packet.packetUID = *( (unsigned short*) bytePtr );
        
        return packet.size == sizeof(unsigned short) && packet.packetUID == 0;
    }
    
    Socket::ReliableUDPConnectionState::ReliableUDPConnectionState ()
    {
        this->sendQueue = new LinkedList< Socket::ReliableUDPPacket* > ();
        this->receiveQueue = new LinkedList< Socket::ReliableUDPPacket* > ();
    }
    
    Socket::ReliableUDPConnectionState::~ReliableUDPConnectionState ()
    {
        if ( this->sendQueue != null )
        {
            delete this->sendQueue;
            this->sendQueue = null;
        }
        if ( this->receiveQueue != null )
        {
            delete this->receiveQueue;
            this->receiveQueue = null;
        }
    }
    
    void Socket::ReliableUDPConnectionState::AcknowledgePacket ( unsigned int uid )
    {
        // Go through the queue of packets to be sent and remove the
        // packet with the given unique ID since it has been received.
        LinkedList< Socket::ReliableUDPPacket* >::Iterator< Socket::ReliableUDPPacket* > iter = this->sendQueue->StartIterator ();
        while ( iter != this->sendQueue->EndIterator () )
        {
            if ( iter.GetObject ()->packetUID == uid )
            {
                Socket::ReliableUDPPacket* packet = iter.GetObject ();
                sendQueue->Remove ( iter );
                Socket::ReleaseReliableUDPPacket ( packet );
                break;
            }
            iter.Next ();
        }
    }
    
    //****************** Private Reliable UDP Classes ******************//
    //******************************************************************//
    

    Socket::Socket ( SocketType type, SystemSocket systemSocket, SystemSocketInternetAddress* socketAddress )
    {
        this->type = type;
        this->socketDescriptor = systemSocket;
        this->connected = true;
        
        // Clean up the old connected endpoint.
        if ( this->connectedEndpoint != null )
        {
            delete this->connectedEndpoint;
            this->connectedEndpoint = null;
        }
        this->connectedEndpoint = new NetworkEndpoint ( socketAddress );
    }
    
    void Socket::Close ()
    {
        // Close all connections on the socket.
        NetworkLayer::CloseSocket ( this->socketDescriptor );
        if ( type == SOCKET_RELIABLE_UDP )
        {
            if ( this->connectionStates != null )
            {
                // Go through and delete all the keys and values in the connection states table.
                Hashtable< NetworkEndpoint*, Socket::ReliableUDPConnectionState* >::Iterator< > iter =
                    this->connectionStates->StartIterator ();
                while ( iter != this->connectionStates->EndIterator () )
                {
                    NetworkEndpoint* endpoint = iter.GetKey ();
                    Socket::ReliableUDPConnectionState* connectionState = iter.GetValue ();
                    
                    if ( endpoint != null )
                    {
                        if ( endpoint == this->connectedEndpoint )
                        {
                            delete endpoint;
                            endpoint = null;
                            
                            this->connectedEndpoint = null;
                        }
                        else
                        {
                            delete endpoint;
                            endpoint = null;
                        }
                    }
                    if ( connectionState != null )
                    {
                        delete connectionState;
                        connectionState = null;
                    }
                    
                    iter.Next ();
                }
                delete this->connectionStates;
                this->connectionStates = null;
            }
        }
    }
    
    bool Socket::ReceiveReliableUDP ( byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* source )
    {
        bool result = true;
        
        // Update the reliable UDP connection (this will
        // hopefully receive the message we want to receive).
        result = this->UpdateReliableUDP ( true );
        
        // Try to resolve the source if it is empty.
        if ( source == null )
        {
            // Use the connected endpoint as the source.
            source = const_cast< NetworkEndpoint* > ( this->GetConnectedEndpoint () );
        }

        // If the source is still empty, then we fail to receive.
        if ( source == null )
        {
            result = false;
        }
        else
        {
            // Get the connection state if it exists.
            Socket::ReliableUDPConnectionState* connectionState = null;
            if ( this->connectionStates->Contains ( source ) )
            {
                connectionState = this->connectionStates->Get ( source );
            }
            // Otherwise, we fail to receive.
            else
            {
                result = false;
            }

            // Check for a packet with the given size of data starting from the front of the queue.
            LinkedList< Socket::ReliableUDPPacket* >::Iterator< > iter = connectionState->receiveQueue->StartIterator ();
            Socket::ReliableUDPPacket* packet = null;
            while ( iter != connectionState->receiveQueue->EndIterator () )
            {
                packet = iter.GetObject ();
                // Check if we have found a packet of the correct size.
                if ( packet->size == count )
                {
                    // Copy the data into the receive buffer and release the packet.
#ifdef _MSC_VER
                    memcpy_s ( &buffer[ offset ], count, packet->data, count );
#else
                    memcpy ( &buffer[ offset ], packet->data, count );
#endif
                    Socket::ReleaseReliableUDPPacket ( packet );
                    packet = null;
                    
                    // The data was received successfully and we are now done.
                    result = true;
                    break;
                }
            }
        }
        
        return result;
    }
    
    bool Socket::SendReliableUDP ( const byte* buffer, const unsigned short offset, const unsigned short count,
        NetworkEndpoint* destination )
    {
        bool result = true;
        
        // Get a reliable packet from the data (this packet is
        // released when it is successfully sent or times out).
        Socket::ReliableUDPPacket* packet = Socket::GetReliableUDPPacket ( &buffer[ offset ], count );
        
        // Try to resolve the destination if it is empty.
        if ( destination == null )
        {
            // Use the connected endpoint as the destination.
            destination = const_cast< NetworkEndpoint* > ( this->GetConnectedEndpoint () );
        }

        // If the destination is still empty, then we fail to send.
        if ( destination == null )
        {
            result = false;
        }
        else
        {
            // Get the connection state, creating one for the given network endpoint if it doesn't exist.
            Socket::ReliableUDPConnectionState* connectionState = null;
            if ( this->connectionStates->Contains ( destination ) )
            {
                connectionState = this->connectionStates->Get ( destination );
            }
            else
            {
                connectionState = new Socket::ReliableUDPConnectionState ();
                this->connectionStates->Put ( destination, connectionState );
            }

            // Set the packet's activated time and then queue
            // the packet to be sent for the current connection.
            Time* time = SystemManager::GetTimeSystem ();
            packet->activatedTime = time->GetTime ();
            connectionState->sendQueue->PushBack ( packet );
        }

        // Update this reliable UDP socket (this will send the packet we just queued).
        result = this->UpdateReliableUDP ( false );
        
        return result;
    }
    
    bool Socket::UpdateReliableUDP ( bool returnReceiveStatus )
    {
        static unsigned short ackPacketSize = Socket::ReliableUDPPacket::GetACKPacketSize ();
        NetworkEndpoint* endpoint = null;
        bool receiveResult = true;
        bool sendResult = true;
        
        // Receive packets, removing acknowledged packets from the send queue
        // and adding received packets to the received queue after acknowledging them.
        while ( this->Poll () == Socket::SOCKET_RECEIVE_READY )
        {
            // Get a new packet to fill up and create a new buffer to hold received data.
            Socket::ReliableUDPPacket* packet = Socket::GetReliableUDPPacket ();
            byte* buffer = new byte[ ackPacketSize ];
            bool result = false;
            
            // Receive the packet and populate the network endpoint source.
            if ( this->IsConnected () )
            {
                result = NetworkLayer::ReceiveUDP ( this, buffer, 0, ackPacketSize );
                endpoint = const_cast< NetworkEndpoint* > ( this->GetConnectedEndpoint () );
            }
            else
            {
                endpoint = new NetworkEndpoint ();
                result = NetworkLayer::ReceiveUDP ( this, buffer, 0, ackPacketSize, endpoint );
            }

            // Get the connection state, creating one for the given network endpoint if it doesn't exist.
            Socket::ReliableUDPConnectionState* connectionState = null;
            if ( this->connectionStates->Contains ( endpoint ) )
            {
                connectionState = this->connectionStates->Get ( endpoint );
            }
            else
            {
                connectionState = new Socket::ReliableUDPConnectionState ();
                this->connectionStates->Put ( endpoint, connectionState );
            }

            // Make sure we received something successfully.
            if ( result )
            {
                // Check if the packet is an ACK packet.
                if ( Socket::ReliableUDPPacket::IsAcknowledgmentPacket ( buffer ) )
                {
                    // Get the packet data and then acknowledge the given packet.
                    packet->SetPacketData ( buffer );
                    connectionState->AcknowledgePacket ( *( (unsigned int*) packet->data ) );
                }
                // Otherwise, the packet is a normal data packet, so receive the rest of the data.
                else
                {
                    unsigned short bufferSize = *( (unsigned short*) buffer );
                    unsigned short dataBufferSize = Socket::ReliableUDPPacket::GetPacketDataSize ( bufferSize );
                    byte* dataBuffer = new byte[ dataBufferSize ];
#ifdef _MSC_VER
                    memcpy_s ( dataBuffer, dataBufferSize, buffer, dataBufferSize );
#else
                    memcpy ( dataBuffer, buffer, dataBufferSize );
#endif
                    if ( this->IsConnected () )
                    {
                        result = NetworkLayer::ReceiveUDP ( this, dataBuffer, ackPacketSize, dataBufferSize - ackPacketSize );
                    }
                    else
                    {
                        result = NetworkLayer::ReceiveUDP ( this, dataBuffer, ackPacketSize, dataBufferSize - ackPacketSize, endpoint );
                    }
                    packet->SetPacketData ( dataBuffer );
                    
                    // Push the packet onto the current connection state's queue.
                    connectionState->receiveQueue->PushBack ( packet );
                    
                    // Clean up allocated memory.
                    if ( dataBuffer != null )
                    {
                        delete dataBuffer;
                        dataBuffer = null;
                    }
                }
            }
            receiveResult |= result;
            
            // Clean up temporary buffer for receiving data.
            if ( buffer != null )
            {
                delete buffer;
                buffer = null;
            }
        }

        // Send all unacknowledged packets, removing packets that are expired.
        if ( this->Poll () == Socket::SOCKET_SEND_READY )
        {
            Time* time = SystemManager::GetTimeSystem ();
            Socket::ReliableUDPConnectionState* connectionState = null;
            Hashtable< NetworkEndpoint*, Socket::ReliableUDPConnectionState* >::Iterator< > connectionStateIter =
                this->connectionStates->StartIterator ();
            while ( connectionStateIter != this->connectionStates->EndIterator () )
            {
                connectionState = connectionStateIter.GetValue ();
                
                Socket::ReliableUDPPacket* packet = null;
                LinkedList< Socket::ReliableUDPPacket* >::Iterator< > packetIter = connectionState->sendQueue->StartIterator ();
                bool result = false;
                while ( packetIter != connectionState->sendQueue->EndIterator () )
                {
                    packet = packetIter.GetObject ();
                    
                    // Check if the packet is expired.
                    if ( packet->timeout > ( time->GetTime () - packet->activatedTime ) )
                    {
                        Socket::ReleaseReliableUDPPacket ( packet );
                        packet = null;
                    }
                    // The packet is valid and unacknowledged, so send it again.
                    else
                    {
                        if ( this->IsConnected () )
                        {
                            result = NetworkLayer::SendUDP ( this, packet->GetPacketData (), 0, packet->GetPacketDataSize () );
                        }
                        else
                        {
                            result = NetworkLayer::SendUDP ( this, packet->GetPacketData (), 0, packet->GetPacketDataSize (),
                                connectionStateIter.GetKey () );
                        }
                    }
                    sendResult |= result;
                    
                    packetIter.Next ();
                }
                
                connectionStateIter.Next ();
            }
        }
        
        return returnReceiveStatus ? receiveResult : sendResult;
    }
    
    Socket::ReliableUDPPacket* Socket::GetReliableUDPPacket ( const byte* data, const unsigned short size )
    {
        // Create the packet.
        Socket::ReliableUDPPacket* packet = new Socket::ReliableUDPPacket ();
        
        // Store the packet's data.
        if ( data != null && size > 0 )
        {
            packet->data = new byte[ size ];
#ifdef _MSC_VER
            memcpy_s ( packet->data, size, data, size );
#else
            memcpy ( packet->data, data, size );
#endif
            packet->size = size;
        }
        else
        {
            packet->data = null;
            packet->size = 0;
        }

        // Set the packet's UID.
        packet->packetUID = Socket::ReliableUDPPacket::GetNextUID ();
        
        return packet;
    }
    
    Socket::ReliableUDPPacket* Socket::GetReliableUDPPacketACK ( const unsigned short uid )
    {
        // Create the packet.
        Socket::ReliableUDPPacket* packet = new Socket::ReliableUDPPacket ();
        
        // Fill the packet.
        packet->size = sizeof(unsigned short);
        packet->data = (byte*) new unsigned short;
        *( (unsigned short*) packet->data ) = uid;
        
        // Set the packet's UID to 0 to indicate that it is an ACK packet.
        packet->packetUID = 0;
        
        return packet;
    }
    
    void Socket::ReleaseReliableUDPPacket ( Socket::ReliableUDPPacket* packet )
    {
        // Clean up the memory used by the packet.
        if ( packet != null )
        {
            if ( packet->data != null )
            {
                delete packet->data;
                packet->data = null;
            }
            delete packet;
            packet = null;
        }
    }

}
