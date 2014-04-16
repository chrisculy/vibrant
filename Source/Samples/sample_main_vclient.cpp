// Include Precompiled Header.
#include "vprecompiled.h"

#include "sample_vclient.h"
#include "vsockettype.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    // Create and run the server.
    SampleClient* client = new SampleClient ( SOCKET_UDP );
    client->Run ();
    
    system ( "pause" );
    return 0;
}
