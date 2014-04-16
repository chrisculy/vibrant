#ifndef VIBRANT_SAMPLE_SERVER_H
#define VIBRANT_SAMPLE_SERVER_H

#include "vnetworklayer.h"
#include "vsocket.h"
#include "vsockettype.h"

using namespace Vibrant;

/**
 * @brief Sample server used to demonstrate the Socket class.
 * 
 * @author Chris Culy
 */
class SampleServer
{
    public:
        
        SampleServer ( SocketType type )
        {
            this->socket = new Socket ( type );
            
            this->socket->SetSocketOption ( Socket::SOCKET_REUSE_ADDRESS, true );
            this->socket->Bind ( &( NetworkEndpoint ( "127.0.0.1", 9712 ) ) );
            this->socket->Listen ();
        }
        
        ~SampleServer ()
        {
            delete this->socket;
            this->socket = null;
        }
        
        void Run ()
        {
            if ( this->socket->GetSocketType () == SOCKET_TCP )
            {
                RunTCP ();
            }
            else if ( this->socket->GetSocketType () == SOCKET_UDP )
            {
                RunUDP ();
            }
            else
            {
                std::cout << "The chosen network protocol is not currently supported.\n";
            }
        }
        
        void RunTCP ()
        {
            char inputChar;
            while ( true )
            {
                std::cout << "Accept a connection? (y/n) ";
                std::cin >> inputChar;
                if ( inputChar == 'n' || inputChar == 'N' )
                {
                    break;
                }
                else
                {
                    // Accept a connection and do stuff with it
                    // until it releases itself.
                    Socket* clientSocket = this->socket->Accept ();
                    ReceiveMessages ( clientSocket );
                }
            }
        }
        
        void RunUDP ()
        {
            char inputChar;
            while ( true )
            {
                std::cout << "Accept a connection? (y/n) ";
                std::cin >> inputChar;
                if ( inputChar == 'n' || inputChar == 'N' )
                {
                    break;
                }
                else
                {
                    // Accept a connection and do stuff with it
                    // until it releases itself.
                    NetworkEndpoint source ( INADDR_ANY );
                    unsigned short connectionRequest = 0;
                    while ( true )
                    {
                        if ( this->socket->ReceiveFrom ( (unsigned char*) &connectionRequest, 0, sizeof(unsigned short), &source ) )
                        {
                            break;
                        }
                        else
                        {
                            std::cout << NetworkLayer::Error ();
                        }
                    }
                    if ( connectionRequest == connectionMessage )
                    {
                        ReceiveMessagesFrom ();
                    }
                }
            }
        }
        
    private:
        
        void ReceiveMessages ( Socket* clientSocket )
        {
            if ( clientSocket != null )
            {
                unsigned short messageSize = 0;
                char* messageBuffer = null;
                String message;
                
                while ( true )
                {
                    // Receive information and print it until
                    // we receive a "Disconnect" message.
                    if ( clientSocket->Receive ( (unsigned char*) &messageSize, 0, sizeof(unsigned short) ) )
                    {
                        messageBuffer = new char[ messageSize + 1 ];
                        if ( clientSocket->Receive ( (unsigned char*) messageBuffer, 0, messageSize ) )
                        {
                            messageBuffer[ messageSize ] = '\0';
                            message = (const char*) messageBuffer;
                            std::cout << "Received: \'" << message << "\'\n";
                            
                            // Tell the client we have received the message.
                            if ( !( clientSocket->Send ( (const unsigned char*) &receivedMessageSize, 0, sizeof(unsigned short) )
                                && clientSocket->Send ( (const unsigned char*) receivedMessageData, 0, receivedMessageSize ) ) )
                            {
                                std::cout << "Could not send confirmation message.\n";
                            }
                            
                            // Check if we should disconnect from the client.
                            if ( message == "Disconnect" )
                            {
                                break;
                            }
                        }

                        // Clean up the allocated memory.
                        delete[] messageBuffer;
                        messageBuffer = null;
                    }
                    else
                    {
                        // Quit if we fail too many times.
                        static int failedCount = 0;
                        failedCount++;
                        //system ( "pause" );
                        if ( failedCount > 10 )
                        {
                            std::cout << NetworkLayer::Error () << "\n";
                        }
                    }
                }
            }
        }
        
        void ReceiveMessagesFrom ()
        {
            unsigned short messageSize = 0;
            char* messageBuffer = null;
            String message;
            NetworkEndpoint source ( "127.0.0.1" );
            
            while ( true )
            {
                // Receive information and print it until
                // we receive a "Disconnect" message.
                if ( this->socket->ReceiveFrom ( (unsigned char*) &messageSize, 0, sizeof(unsigned short), &source ) )
                {
                    messageBuffer = new char[ messageSize + 1 ];
                    if ( this->socket->ReceiveFrom ( (unsigned char*) messageBuffer, 0, messageSize, &source ) )
                    {
                        messageBuffer[ messageSize ] = '\0';
                        message = (const char*) messageBuffer;
                        std::cout << "Received: \'" << message << "\'\n";
                        
                        // Tell the client we have received the message.
                        if ( !( this->socket->SendTo ( (const unsigned char*) &receivedMessageSize, 0, sizeof(unsigned short), &source )
                            && this->socket->SendTo ( (const unsigned char*) receivedMessageData, 0, receivedMessageSize, &source ) ) )
                        {
                            std::cout << "Could not send confirmation message.\n";
                        }
                        
                        // Check if we should disconnect from the client.
                        if ( message == "Disconnect" )
                        {
                            break;
                        }
                    }

                    // Clean up the allocated memory.
                    delete[] messageBuffer;
                    messageBuffer = null;
                }
                else
                {
                    // Quit if we fail too many times.
                    static int failedCount = 0;
                    failedCount++;
                    //system ( "pause" );
                    if ( failedCount > 10 )
                    {
                        std::cout << NetworkLayer::Error () << "\n";
                    }
                }
            }
        }
        
        Socket* socket;
        static unsigned short receivedMessageSize;
        static unsigned char* receivedMessageData;
        static unsigned short connectionMessage;
};

unsigned short SampleServer::receivedMessageSize = 27;
unsigned char* SampleServer::receivedMessageData = (unsigned char*) "Message has been received.\0";
unsigned short SampleServer::connectionMessage = 24776;

#endif
