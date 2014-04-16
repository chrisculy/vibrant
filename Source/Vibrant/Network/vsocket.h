/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsocket.h
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

#ifndef VIBRANT_SOCKET_H
#define VIBRANT_SOCKET_H

#include "varray.h"
#include "vasynchronous.h"
#include "vhashtable.h"
#include "vlinkedlist.h"
#include "vnetworkendpoint.h"
#include "vsockettype.h"
#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a network socket.
     * 
     * @see NetworkLayer
     * @author Chris Culy
     */
    class VAPI Socket
    {
        public:
            
            //*********************** Socket Enumerations **********************//

            /**
             * @brief Represents the different modes (directions) used
             * when shutting down a socket connection.
             * 
             * <p>
             * The shutdown modes (directions):
             * <ul>
             *  <li>SOCKET_RECEIVE (SD_RECEIVE for Winsock)</li>
             *  <li>SOCKET_SEND (SD_SEND for Winsock)</li>
             *  <li>SOCKET_BOTH (SD_BOTH for Winsock)</li>
             * </ul>
             * </p>
             * 
             * @see Socket#Shutdown(ShutdownType)
             */
            enum ShutdownType
            {
                SOCKET_RECEIVE = 0,
                SOCKET_SEND = 1,
                SOCKET_BOTH = 2
            };

            /**
             * @brief Represents the state of a socket.
             * 
             * <p>
             * The socket states:
             * <ul>
             *  <li>SOCKET_RECEIVE_READY</li>
             *  <li>SOCKET_SEND_READY</li>
             *  <li>SOCKET_HAS_ERROR</li>
             * </ul>
             * </p>
             * 
             * @see Socket#Poll()
             */
            enum SocketState
            {
                SOCKET_RECEIVE_READY,
                SOCKET_SEND_READY,
                SOCKET_HAS_ERROR
            };

            /**
             * @brief Represents the different socket options.
             * 
             * <p>
             * The socket options:
             * <ul>
             *  <li>SOCKET_DEBUG</li>
             *  <li>SOCKET_REUSE_ADDRESS</li>
             *  <li>SOCKET_KEEP_ALIVE</li>
             *  <li>SOCKET_DO_NOT_ROUTE</li>
             *  <li>SOCKET_LINGER</li>
             *  <li>SOCKET_BROADCAST</li>
             *  <li>SOCKET_RECEIVE_OOB_DATA</li>
             * </ul>
             * </p>
             * 
             * @see Socket#SetSocketOption(SocketOption, bool)
             * @see Socket#GetSocketOption(SocketOption)
             */
            enum SocketOption
            {
                SOCKET_DEBUG = SO_DEBUG,
                SOCKET_REUSE_ADDRESS = SO_REUSEADDR,
                SOCKET_KEEP_ALIVE = SO_KEEPALIVE,
                SOCKET_DO_NOT_ROUTE = SO_DONTROUTE,
                SOCKET_LINGER = SO_LINGER,
                SOCKET_BROADCAST = SO_BROADCAST,
                SOCKET_RECEIVE_OOB_DATA = SO_OOBINLINE
            };

            //*********************** Socket Enumerations **********************//
            

            //*********************** Asynchronous States **********************//

            /**
             * @brief Represents the state for an asynchronous socket operation.
             * 
             * @author Chris Culy
             */
            struct AsynchSocketState : public AsynchState
            {
                    /**
                     * @brief Constructor.
                     */
                    AsynchSocketState ()
                    {
                        this->result = false;
                        this->socket = null;
                    }
                    
                    /** 
                     * @brief Holds the result of the asynchronous operation; 
                     * <code>true</code> if successful;<code>false</code> otherwise.
                     */
                    bool result;

                    /** @brief Holds the socket associated
                     * with the asynchronous operation. */
                    Socket* socket;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>accept</code> operation.
             * 
             * @see Socket#BeginAccept(AsynchSocketCallback)
             * @see Socket#BeginAccept(AsynchSocketCallback, AcceptState*)
             * @see Socket#EndAccept(AcceptState*)
             * @author Chris Culy
             */
            struct AcceptState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    AcceptState ()
                    {
                        this->acceptedSocket = null;
                    }
                    
                    /** @brief Holds the accepted socket. */
                    Socket* acceptedSocket;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>connect</code> operation.
             * 
             * @see Socket#BeginConnect(AsynchSocketCallback, NetworkEndpoint*)
             * @see Socket#BeginConnect(AsynchSocketCallback, ConnectState*)
             * @see Socket#EndConnect(ConnectState*)
             * @author Chris Culy
             */
            struct ConnectState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    ConnectState ()
                    {
                        this->endpoint = null;
                    }
                    
                    /** @brief Holds the network endpoint to connect to. */
                    NetworkEndpoint* endpoint;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>disconnect</code> operation.
             * 
             * @see Socket#BeginDisconnect(AsynchSocketCallback)
             * @see Socket#BeginDisconnect(AsynchSocketCallback, DisconnectState*)
             * @see Socket#EndDisconnect(DisconnectState*)
             * @author Chris Culy
             */
            struct DisconnectState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor.
                     */
                    DisconnectState ()
                    {
                        this->reuseSocket = false;
                    }
                    
                    /** @brief Holds whether the socket can be reused after being disconnected. */
                    bool reuseSocket;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>receive</code> operation.
             * 
             * @see Socket#BeginReceive(AsynchSocketCallback, byte*, unsigned short, unsigned short)
             * @see Socket#BeginReceive(AsynchSocketCallback, ReceiveState*)
             * @see Socket#EndReceive(ReceiveState*)
             * @author Chris Culy
             */
            struct ReceiveState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    ReceiveState ()
                    {
                        this->buffer = null;
                        this->offset = 0;
                        this->count = 0;
                    }
                    
                    /** @brief Holds the buffer to receive data into. */
                    byte* buffer;

                    /** @brief Holds the offset into the buffer. */
                    unsigned short offset;

                    /** @brief Holds the number of bytes to receive. */
                    unsigned short count;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>receive from</code> operation.
             * 
             * @see Socket#BeginReceiveFrom(AsynchSocketCallback, byte*, unsigned short,
             *      unsigned short, NetworkEndpoint*)
             * @see Socket#BeginReceiveFrom(AsynchSocketCallback, ReceiveFromState*)
             * @see Socket#EndReceiveFrom(ReceiveFromState*)
             * @author Chris Culy
             */
            struct ReceiveFromState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    ReceiveFromState ()
                    {
                        this->buffer = null;
                        this->offset = 0;
                        this->count = 0;
                        this->source = null;
                    }
                    
                    /** @brief Holds the buffer to receive data into. */
                    byte* buffer;

                    /** @brief Holds the offset into the buffer. */
                    unsigned short offset;

                    /** @brief Holds the number of bytes to receive. */
                    unsigned short count;

                    /** @brief Holds the network endpoint source of the received data. */
                    NetworkEndpoint* source;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>send</code> operation.
             * 
             * @see Socket#BeginSend(AsynchSocketCallback, byte*, unsigned short, unsigned short)
             * @see Socket#BeginSend(AsynchSocketCallback, SendState*)
             * @see Socket#EndSend(SendState*)
             * @author Chris Culy
             */
            struct SendState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    SendState ()
                    {
                        this->buffer = null;
                        this->offset = 0;
                        this->count = 0;
                    }
                    
                    /** @brief Holds the buffer to send data from. */
                    byte* buffer;

                    /** @brief Holds the offset into the buffer. */
                    unsigned short offset;

                    /** @brief Holds the number of bytes to send. */
                    unsigned short count;
            };

            /**
             * @brief Represents the state for an asynchronous
             * socket <code>send to</code> operation.
             * 
             * @see Socket#BeginSendTo(AsynchSocketCallback, byte*, unsigned short, unsigned short,
             *      NetworkEndpoint*)
             * @see Socket#BeginSendTo(AsynchSocketCallback, SendToState*)
             * @see Socket#EndSendTo(SendToState*)
             * @author Chris Culy
             */
            struct SendToState : public AsynchSocketState
            {
                    /**
                     * @brief Constructor (sets all members to defaults).
                     */
                    SendToState ()
                    {
                        this->buffer = null;
                        this->offset = 0;
                        this->count = 0;
                        this->destination = null;
                    }
                    
                    /** @brief Holds the buffer to send data from. */
                    byte* buffer;

                    /** @brief Holds the offset into the buffer. */
                    unsigned short offset;

                    /** @brief Holds the number of bytes to send. */
                    unsigned short count;

                    /** @brief Holds the network endpoint destination for the sent data. */
                    NetworkEndpoint* destination;
            };

            //*********************** Asynchronous States **********************//
            

            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param type The socket's type({@link Vibrant#SocketType SocketType}).
             */
            Socket ( SocketType type );

            /**
             * @brief Destructor.
             */
            virtual ~Socket ();

            /**
             * @brief Retrieves the socket's type.
             * 
             * @return The socket's type.
             * @see SocketType
             */
            const SocketType& GetSocketType ();

            /**
             * @brief Retrieves the socket's corresponding system-level representation.
             * 
             * @return The socket's descriptor.
             * @see SystemSocket
             */
            const SystemSocket& GetSocketDescriptor ();

            /**
             * @brief Retrieves the endpoint the socket is bound to.
             * 
             * @return The endpoint the socket is bound to or <code>null</code>
             *      if it is not bound explicitly to an endpoint.
             */
            const NetworkEndpoint* GetBoundEndpoint ();

            /**
             * @brief Retrieves the endpoint the socket is connected to.
             * 
             * @return The endpoint the socket is connected to or <code>null</code>
             *      if it is not connected.
             */
            const NetworkEndpoint* GetConnectedEndpoint ();

            /**
             * @brief Retrieves whether the socket is bound or not.
             * 
             * @return <code>true</code> if the socket is bound;
             *      <code>false</code> otherwise.
             */
            bool IsBound ();

            /**
             * @brief Retrieves whether the socket is connected or not.
             * 
             * @return <code>true</code> if the socket is connected;
             *      <code>false</code> otherwise.
             */
            bool IsConnected ();

            /**
             * @brief Accepts a socket connection.
             * 
             * <p>
             * Note: This should only be called on
             * a socket that has been bound to a port
             * and is currently listening for connections.
             * </p>
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @return The accepted socket.
             * @see Socket#BeginAccept(AsynchSocketCallback)
             * @see Socket#BeginAccept(AsynchSocketCallback, AcceptState*)
             * @see Socket#EndAccept(AcceptState*)
             */
            Socket* Accept ();

            /**
             * @brief Binds the socket to the given network endpoint.
             * 
             * @param endpoint The endpoint to bind the socket to.
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             */
            bool Bind ( const NetworkEndpoint* endpoint );

            /**
             * @brief Connects the socket to the given network endpoint.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param endpoint The network endpoint to connect to.
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             * @see Socket#BeginConnect(AsynchSocketCallback, NetworkEndpoint*)
             * @see Socket#BeginConnect(AsynchSocketCallback, ConnectState*)
             * @see Socket#EndConnect(ConnectState*)
             */
            bool Connect ( const NetworkEndpoint* endpoint );

            /**
             * @brief Disconnects the socket from its current connection.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param reuseSocket Whether the socket should be allowed
             *      to be reused after disconnecting.
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             * @see Socket#BeginDisconnect(AsynchSocketCallback)
             * @see Socket#BeginDisconnect(AsynchSocketCallback, DisconnectState*)
             * @see Socket#EndDisconnect(DisconnectState*)
             */
            bool Disconnect ( bool reuseSocket = true );

            /**
             * @brief Listens on the bound port with the given
             * connection capacity (the socket should
             * be bound to a port before calling this).
             * 
             * @param connectionCapacity The number of connections to allow
             *      to queue at one time before they are accepted.
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             */
            bool Listen ( const unsigned short connectionCapacity = 10 );

            /**
             * @brief Retrieves the state of the socket.
             * 
             * @return The state of the socket.
             * @see SocketState
             */
            SocketState Poll ();

            /**
             * @brief Reads bytes from the socket.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to read.
             * @return <code>true</code> if the bytes were read successfully;
             *      <code>false</code> otherwise.
             * @see Socket#BeginReceive(AsynchSocketCallback, byte*, unsigned short, unsigned short)
             * @see Socket#BeginReceive(AsynchSocketCallback, ReceiveState*)
             * @see Socket#EndReceive(ReceiveState*)
             */
            bool Receive ( byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Reads bytes from the socket.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to read.
             * @param source A network endpoint that is
             *      set to the remote source of the data.
             * @return <code>true</code> if the bytes were read successfully;
             *      <code>false</code> otherwise.
             * @see Socket#BeginReceiveFrom(AsynchSocketCallback, byte*, unsigned short,
             *      unsigned short, NetworkEndpoint*)
             * @see Socket#BeginReceiveFrom(AsynchSocketCallback, ReceiveFromState*)
             * @see Socket#EndReceiveFrom(ReceiveFromState*)
             */
            bool ReceiveFrom ( byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* source );

            /**
             * @brief Writes bytes to the socket.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to write.
             * @return <code>true</code> if the bytes were written successfully;
             *      <code>false</code> otherwise.
             * @see Socket#BeginSend(AsynchSocketCallback, byte*, unsigned short, unsigned short)
             * @see Socket#BeginSend(AsynchSocketCallback, SendState*)
             * @see Socket#EndSend(SendState*)
             */
            bool Send ( const byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Writes bytes to the socket.
             * 
             * <p>
             * Note: This call is blocking.
             * </p>
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to write.
             * @param destination A network endpoint representing
             *      the remote destination of the data.
             * @return <code>true</code> if the bytes were written successfully;
             *      <code>false</code> otherwise.
             * @see Socket#BeginSendTo(AsynchSocketCallback, byte*, unsigned short, unsigned short,
             *      NetworkEndpoint*)
             * @see Socket#BeginSendTo(AsynchSocketCallback, SendToState*)
             * @see Socket#EndSendTo(SendToState*)
             */
            bool SendTo ( const byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* destination );

            /**
             * @brief Shuts down the socket's connection in the given directions.
             * 
             * @param shutdownType The shutdown type (the direction(s)
             *      in which to shut down the connection).
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             */
            bool Shutdown ( ShutdownType shutdownType = SOCKET_BOTH );

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
            static bool Select ( LinkedList< Socket* >* checkReceiveReady, LinkedList< Socket* >* checkSendReady,
                LinkedList< Socket* >* checkHasError, unsigned int timeout = 0 );

            //************************ General Interface ***********************//
            

            //********************** Asynchronous Interface ********************//

            /**
             * @brief Defines the function interface for asynchronous
             * socket operation callbacks.
             * 
             * @param state The state of the asynchronous operation.
             */
            typedef void (*AsynchSocketCallback) ( Socket::AsynchSocketState* state );

            /**
             * @brief Asynchronously starts an <code>accept</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>accept</code>
             *      operation has begun asynchronously.
             */
            void BeginAccept ( AsynchSocketCallback callback );

            /**
             * @brief Asynchronously starts an <code>accept</code> operation.
             * 
             * @param callback The function to call once the <code>accept</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>accept</code> operation.
             */
            void BeginAccept ( AsynchSocketCallback callback, AcceptState* state );

            /**
             * @brief Asynchronously starts a <code>connect</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>connect</code>
             *      operation has begun asynchronously.
             * @param endpoint The network endpoint to connect to.
             */
            void BeginConnect ( AsynchSocketCallback callback, NetworkEndpoint* endpoint );

            /**
             * @brief Asynchronously starts a <code>connect</code> operation.
             * 
             * @param callback The function to call once the <code>connect</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>connect</code> operation.
             */
            void BeginConnect ( AsynchSocketCallback callback, ConnectState* state );

            /**
             * @brief Asynchronously starts a <code>disconnect</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>disconnect</code>
             *      operation has begun asynchronously.
             * @param reuseSocket Whether the socket should be allowed
             *      to be reused after disconnecting.
             */
            void BeginDisconnect ( AsynchSocketCallback callback, bool reuseSocket );

            /**
             * @brief Asynchronously starts a <code>disconnect</code> operation.
             * 
             * @param callback The function to call once the <code>disconnect</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>disconnect</code> operation.
             */
            void BeginDisconnect ( AsynchSocketCallback callback, DisconnectState* state );

            /**
             * @brief Asynchronously starts a <code>receive</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>receive</code>
             *      operation has begun asynchronously.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to read.
             */
            void BeginReceive ( AsynchSocketCallback callback, byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Asynchronously starts a <code>receive</code> operation.
             * 
             * @param callback The function to call once the <code>receive</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>receive</code> operation.
             */
            void BeginReceive ( AsynchSocketCallback callback, ReceiveState* state );

            /**
             * @brief Asynchronously starts a <code>receive from</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>receive from</code>
             *      operation has begun asynchronously.
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to read.
             * @param source A network endpoint that is
             *      set to the remote source of the data.
             */
            void BeginReceiveFrom ( AsynchSocketCallback callback, byte* buffer, const unsigned short offset, const unsigned short count,
                NetworkEndpoint* source );

            /**
             * @brief Asynchronously starts a <code>receive from</code> operation.
             * 
             * @param callback The function to call once the <code>receive from</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>receive from</code> operation.
             */
            void BeginReceiveFrom ( AsynchSocketCallback callback, ReceiveFromState* state );

            /**
             * @brief Asynchronously starts a <code>send</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>send</code>
             *      operation has begun asynchronously.
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to write.
             */
            void BeginSend ( AsynchSocketCallback callback, const byte* buffer, const unsigned short offset, const unsigned short count );

            /**
             * @brief Asynchronously starts a <code>send</code> operation.
             * 
             * @param callback The function to call once the <code>send</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>send</code> operation.
             */
            void BeginSend ( AsynchSocketCallback callback, SendState* state );

            /**
             * @brief Asynchronously starts a <code>send to</code> operation.
             * 
             * <p>
             * Note: The user is responsible for destroying the asynchronous
             * object received in the callback when it is no longer used.
             * </p>
             * 
             * @param callback The function to call once the <code>send to</code>
             *      operation has begun asynchronously.
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to write.
             * @param destination A network endpoint representing
             *      the remote destination of the data.
             */
            void BeginSendTo ( AsynchSocketCallback callback, const byte* buffer, const unsigned short offset, const unsigned short count,
                NetworkEndpoint* destination );

            /**
             * @brief Asynchronously starts a <code>send to</code> operation.
             * 
             * @param callback The function to call once the <code>send to</code>
             *      operation has begun asynchronously.
             * @param state The state of the <code>send to</code> operation.
             */
            void BeginSendTo ( AsynchSocketCallback callback, SendToState* state );

            /**
             * @brief Completes the asynchronous <code>accept</code> operation
             * (should be called from within the <code>BeginAccept</code>'s callback).
             * 
             * @param state The state of the <code>accept</code> operation.
             */
            void EndAccept ( AcceptState* state );

            /**
             * @brief Completes the asynchronous <code>connect</code> operation
             * (should be called from within the <code>BeginConnect</code>'s callback).
             * 
             * @param state The state of the <code>connect</code> operation.
             */
            void EndConnect ( ConnectState* state );

            /**
             * @brief Completes the asynchronous <code>disconnect</code> operation
             * (should be called from within the <code>BeginDisconnect</code>'s callback).
             * 
             * @param state The state of the <code>disconnect</code> operation.
             */
            void EndDisconnect ( DisconnectState* state );

            /**
             * @brief Completes the asynchronous <code>receive</code> operation
             * (should be called from within the <code>BeginReceive</code>'s callback).
             * 
             * @param state The state of the <code>receive</code> operation.
             */
            void EndReceive ( ReceiveState* state );

            /**
             * @brief Completes the asynchronous <code>receive from</code> operation
             * (should be called from within the <code>BeginReceiveFrom</code>'s callback).
             * 
             * @param state The state of the <code>receive from</code> operation.
             */
            void EndReceiveFrom ( ReceiveFromState* state );

            /**
             * @brief Completes the asynchronous <code>send</code> operation
             * (should be called from within the <code>BeginSend</code>'s callback).
             * 
             * @param state The state of the <code>send</code> operation.
             */
            void EndSend ( SendState* state );

            /**
             * @brief Completes the asynchronous <code>send to</code> operation
             * (should be called from within the <code>BeginSendTo</code>'s callback).
             * 
             * @param state The state of the <code>send to</code> operation.
             */
            void EndSendTo ( SendToState* state );

            //********************** Asynchronous Interface ********************//
            

            //************************* Socket Options *************************//

            /**
             * @brief Retrieves the given socket option.
             * 
             * @param option The socket option to retrieve.
             * @return <code>true</code> if the option is on;
             *      <code>false</code> if the option is off.
             */
            bool GetSocketOption ( SocketOption option );

            /**
             * @brief Retrieves the socket's receive timeout.
             * 
             * @return The receive timeout (in milliseconds).
             */
            int GetReceiveTimeout ();

            /**
             * @brief Retrieves the socket's receive buffer size.
             * 
             * @return The buffer size (in bytes).
             */
            int GetReceiveBufferSize ();

            /**
             * @brief Retrieves the socket's send timeout.
             * 
             * @return The send timeout (in milliseconds).
             */
            int GetSendTimeout ();

            /**
             * @brief Retrieves the socket's send buffer size.
             * 
             * @return The buffer size (in bytes).
             */
            int GetSendBufferSize ();

            /**
             * @brief Sets the given socket option.
             * 
             * @param option The socket option to set.
             * @param value Whether the option is on(<code>true</code>)
             *      or off(<code>false</code>).
             */
            void SetSocketOption ( SocketOption option, const bool value );

            /**
             * @brief Sets the socket's receive timeout.
             * 
             * @param timeout The timeout (in milliseconds).
             */
            void SetReceiveTimeout ( const int timeout );

            /**
             * @brief Sets the socket's receive buffer size.
             * 
             * @param size The buffer size (in bytes).
             */
            void SetReceiveBufferSize ( const int size );

            /**
             * @brief Sets the socket's send timeout.
             * 
             * @param timeout The timeout (in milliseconds).
             */
            void SetSendTimeout ( const int timeout );

            /**
             * @brief Sets the socket's send buffer size.
             * 
             * @param size The buffer size (in bytes).
             */
            void SetSendBufferSize ( const int size );

            //************************* Socket Options *************************//

        private:
            
            /**
             * @brief Encapsulates data to be sent using reliable UDP.
             * 
             * @author Chris Culy
             */
            struct ReliableUDPPacket
            {
                    /**
                     * @brief Constructor (initializes members to defaults).
                     */
                    ReliableUDPPacket ();

                    /**
                     * @brief Retrieves the packet data to be sent.
                     * 
                     * @return The packet data.
                     */
                    const byte* GetPacketData ();

                    /**
                     * @brief Retrieves the size of the packet data to be sent.
                     * 
                     * @return The size of the packet data.
                     */
                    const unsigned short GetPacketDataSize ();

                    /**
                     * @brief Sets the packet's data (used when receiving a packet).
                     * 
                     * @param data The packet data.
                     */
                    void SetPacketData ( byte* data );

                    /** @brief Holds when the packet was first queued for being sent. */
                    long activatedTime;

                    /** @brief Holds the amount of time (in ms) that must pass before
                     * discarding this packet if it has not yet been acknowledged. */
                    long timeout;

                    // -
                    // Note: The following three members are the packet's send data.
                    // See ReliableUDPPacket#getPacketSendData().
                    // -

                    /** @brief Holds the size of the packet's data. */
                    unsigned short size;

                    /** @brief Holds the packet's data. */
                    byte* data;

                    /** @brief Holds the packet's unique identifier. */
                    unsigned int packetUID;

                    //************************ General Interface ***********************//
                    

                    //************************* Static Members *************************//

                    /**
                     * @brief Retrieves the next valid unique identifier.
                     * 
                     * @return The next valid UID.
                     */
                    static unsigned int GetNextUID ();

                    /**
                     * @brief Retrieves the size of an ACK packet.
                     * 
                     * @return The size of an ACK packet.
                     */
                    static unsigned short GetACKPacketSize ();

                    /** 
                     * @brief Retrieves the size of the packet data
                     * to be received given the size of the buffer.
                     * 
                     * @return The size of the packet data.
                     */
                    static const unsigned short GetPacketDataSize ( const unsigned short bufferSize );

                    /**
                     * @brief Retrieves whether the given byte array
                     * is the memory representation of an acknowledgment packet.
                     * 
                     * @return <code>true</code> if the data is an acknowledgment
                     *      packet;<code>false</code> otherwise.
                     */
                    static bool IsAcknowledgmentPacket ( byte* data );

                    /** @brief Holds the start value for UIDs. */
                    static const int UID_START = 7427;

                    /** @brief Holds the default timeout for Reliable UDP packets. */
                    static const int DEFAULT_TIMEOUT = 1000;
                    
                    //************************* Static Members *************************//
            };

            /**
             * @brief Represents the state of a reliable UDP connection.
             * 
             * @author Chris Culy
             */
            struct ReliableUDPConnectionState
            {
                    /**
                     * @brief Constructor.
                     */
                    ReliableUDPConnectionState ();
                    /**
                     * @brief Destructor.
                     */
                    ~ReliableUDPConnectionState ();

                    /** @brief Holds the queue of packets to be sent. */
                    LinkedList< ReliableUDPPacket* >* sendQueue;

                    /** @brief Holds the queue of packets to be received. */
                    LinkedList< ReliableUDPPacket* >* receiveQueue;

                    /**
                     * @brief Acknowledges that the given packet has been received
                     * (and removes it from the send queue).
                     * 
                     * @param uid The unique ID of the packet to acknowledge.
                     */
                    void AcknowledgePacket ( unsigned int uid );
            };

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief NetworkLayer is a friend class to allow it
             * to create a socket from the information it
             * receives when accepting a system-level socket.
             */
            friend class NetworkLayer;

            /**
             * @brief Special constructor used to create a socket
             * from a system-level socket returned from an
             * <code>accept</code> operation.
             * 
             * @param type The socket's type({@link Vibrant#SocketType SocketType}).
             * @param systemSocket The system socket descriptor/handle.
             * @param socketAddress The system level socket Internet address.
             */
            Socket ( SocketType type, SystemSocket systemSocket, SystemSocketInternetAddress* socketAddress );

            /**
             * @brief Closes all connections for the socket and closes the system socket handle.
             */
            void Close ();

            /**
             * @brief Receives data from the given source.
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @param source The network endpoint to receive data from.
             * @return <code>true</code> if the data was received successfully;
             *      <code>false</code> otherwise.
             */
            bool ReceiveReliableUDP ( byte* buffer, const unsigned short offset, const unsigned short count, NetworkEndpoint* source );

            /**
             * @brief Sends data to the given destination.
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to write (<code>byte</code>s).
             * @param destination The network endpoint to send data to.
             * @return <code>true</code> if the data was sent successfully;
             *      <code>false</code> otherwise.
             */
            bool SendReliableUDP ( const byte* buffer, const unsigned short offset, const unsigned short count,
                NetworkEndpoint* destination );

            /**
             * @brief Manages the sending and receiving of data
             * using the reliable UDP protocol.
             * 
             * @param returnReceiveStatus If <code>true</code> then the function will
             *      return whether all receive calls returned successfully; otherwise,
             *      the function will return whether all send calls returned successfully.
             * @return <code>true</code> if successful;<code>false</code> otherwise.
             */
            bool UpdateReliableUDP ( bool returnReceiveStatus );

            /**
             * @brief Creates and retrieves a reliable UDP packet with
             * all members initialized properly except for the
             * last sent time, because we want the time to be as
             * accurate as possible.
             * 
             * <p>
             * <b>Note:</b> The packet returned from this function must
             * be released with a call to {@link Socket#ReleaseReliableUDPPacket(ReliableUDPPacket*) ReleaseReliableUDPPacket}.
             * </p>
             * 
             * @param data The data to be sent.
             * @param size The size of the data (# of bytes).
             * @return A new, initialized reliable UDP packet.
             */
            static ReliableUDPPacket* GetReliableUDPPacket ( const byte* data = null, const unsigned short size = 0 );

            /**
             * @brief Creates and retrieves a reliable UDP acknowledgment packet.
             * 
             * @param uid The unique identifier of the packet to be acknowledged.
             * @return A reliable UDP 'ack' packet.
             */
            static ReliableUDPPacket* GetReliableUDPPacketACK ( const unsigned short uid );

            /**
             * @brief Releases (and cleans up after) a reliable UDP packet.
             * 
             * @param packet The packet to release. (This is not valid after calling this function.)
             */
            static void ReleaseReliableUDPPacket ( ReliableUDPPacket* packet );

            //************************ General Interface ***********************//

        private:
            
            /** @brief The socket's type. */
            SocketType type;

            /** @brief The socket's system socket descriptor. */
            SystemSocket socketDescriptor;

            /** @brief Holds the network endpoint the socket is bound to. */
            NetworkEndpoint* boundEndpoint;

            /** @brief Holds the network endpoint the socket is connected to. */
            NetworkEndpoint* connectedEndpoint;

            /** @brief Whether the socket is connected or not. */
            bool connected;

            /** @brief Whether the socket is bound or not. */
            bool bound;

            /** @brief Holds a static (per instance) list of sockets that contains
             * only this socket (used for polling) and is used to check whether the
             * socket is ready to receive. */
            LinkedList< Socket* > thisReceiveList;

            /** @brief Holds a static (per instance) list of sockets that contains
             * only this socket (used for polling) and is used to check whether the
             * socket is ready to send. */
            LinkedList< Socket* > thisSendList;

            /** @brief Holds a static (per instance) list of sockets that contains
             * only this socket (used for polling) and is used to check whether the
             * socket has any errors. */
            LinkedList< Socket* > thisErrorList;

            /** @brief Holds all the connection states. */
            Hashtable< NetworkEndpoint*, ReliableUDPConnectionState* >* connectionStates;
    };

}

#endif
