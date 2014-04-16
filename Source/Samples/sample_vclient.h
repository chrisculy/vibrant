#ifndef VIBRANT_SAMPLE_CLIENT_H
#define VIBRANT_SAMPLE_CLIENT_H

#include "vnetworklayer.h"
#include "vsocket.h"
#include "vsockettype.h"

using namespace Vibrant;

/**
 * @brief Sample client used to demonstrate the Socket class.
 * 
 * @author Chris Culy
 */
class SampleClient
{
    public:
        
        SampleClient ( SocketType type )
        {
            NetworkEndpoint serverAddress ( "127.0.0.1", 9712 );
            this->socket = new Socket ( type );
            this->socket->Connect ( &serverAddress );
        }
        
        ~SampleClient ()
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
            String message;
            bool done = false;
            while ( !done )
            {
                // Get a message to send until the user says "Disconnect".
                std::cout << "Enter a message to send (\'Disconnect\' to disconnect and quit):\n";
                std::string stringBuffer;
                getline ( std::cin, stringBuffer );
                message = stringBuffer.c_str ();
                
                // Check if we should quit.
                if ( message == "Disconnect" )
                {
                    done = true;
                }

                unsigned short messageSize = message.Size ();
                // Attempt to send a message.
                if ( this->socket->Send ( (const unsigned char*) &messageSize, 0, sizeof(unsigned short) ) && this->socket->Send (
                    (const unsigned char*) message.CString (), 0, message.Size () ) )
                {
                    unsigned short bufferSize = 0;
                    
                    // Receive confirmation that the message was received.
                    if ( this->socket->Receive ( (unsigned char*) &bufferSize, 0, sizeof(unsigned short) ) )
                    {
                        unsigned char* receiveBuffer = new unsigned char[ bufferSize ];
                        if ( this->socket->Receive ( receiveBuffer, 0, bufferSize ) )
                        {
                            message = (const char*) receiveBuffer;
                            std::cout << "Server: " << message << "\n";
                        }
                        else
                        {
                            std::cout << "Failed to receive confirmation message:" << NetworkLayer::Error () << "\n";
                        }
                        delete receiveBuffer;
                        receiveBuffer = null;
                    }
                    else
                    {
                        std::cout << "Failed to receive confirmation message:" << NetworkLayer::Error () << "\n";
                    }
                }
                // Message failed to send.
                else
                {
                    std::cout << "Failed to send message:" << NetworkLayer::Error () << "\n";
                }
            }
        }
        
        void RunUDP ()
        {
            static unsigned short connectionMessage = 24776;
            // Attempt to connect to the server.
            if ( this->socket->Send ( (const unsigned char*) &connectionMessage, 0, sizeof(unsigned short) ) )
            {
                String message;
                bool done = false;
                while ( !done )
                {
                    // Get a message to send until the user says "Disconnect".
                    std::cout << "Enter a message to send (\'Disconnect\' to disconnect and quit):\n";
                    std::string stringBuffer;
                    getline ( std::cin, stringBuffer );
                    message = stringBuffer.c_str ();
                    
                    // Check if we should quit.
                    if ( message == "Disconnect" )
                    {
                        done = true;
                    }

                    // Attempt to send a message.
                    unsigned short messageSize = message.Size ();
                    if ( this->socket->Send ( (const unsigned char*) &messageSize, 0, sizeof(unsigned short) ) && this->socket->Send (
                        (const unsigned char*) message.CString (), 0, message.Size () ) )
                    {
                        unsigned short bufferSize = 0;
                        
                        // Receive confirmation that the message was received.
                        NetworkEndpoint source ( INADDR_ANY );
                        if ( this->socket->Receive ( (unsigned char*) &bufferSize, 0, sizeof(unsigned short) ) )
                        {
                            unsigned char* receiveBuffer = new unsigned char[ bufferSize ];
                            if ( this->socket->Receive ( receiveBuffer, 0, bufferSize ) )
                            {
                                message = (const char*) receiveBuffer;
                                std::cout << "Server: " << message << "\n";
                            }
                            else
                            {
                                std::cout << "Failed to receive confirmation message:" << NetworkLayer::Error () << "\n";
                            }
                            delete receiveBuffer;
                            receiveBuffer = null;
                        }
                        else
                        {
                            std::cout << "Failed to receive confirmation message:" << NetworkLayer::Error () << "\n";
                        }
                    }
                    // Message failed to send.
                    else
                    {
                        std::cout << "Failed to send message:" << NetworkLayer::Error () << "\n";
                    }
                }
            }
        }
        
    private:
        Socket* socket;
};

#endif
