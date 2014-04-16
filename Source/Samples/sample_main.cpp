#include <iostream>
#include <string>

#include "vnetworkendpoint.h"
#include "vnetworklayer.h"
#include "vsocket.h"
#include "vsockettype.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    // We do this to start the network system (NetworkLayer::start()).
    Socket* socket = new Socket ( SOCKET_UDP );
    
    NetworkEndpoint* endpoint = new NetworkEndpoint ( "www.google.com", 80 );
    String address = endpoint->GetAddressAsString ();
    unsigned long port = endpoint->GetPort ();
    String hostname = endpoint->GetHostname ();
    
    std::cout << NetworkLayer::Error () << "\n";
    std::cout << "Address: " << address << ", Port: " << port << "\n";
    std::cout << "Host name: " << hostname << "\n";
    
    delete endpoint;
    delete socket;
    
    std::cout << "\n";
    system ( "pause" );
    return 0;
}
