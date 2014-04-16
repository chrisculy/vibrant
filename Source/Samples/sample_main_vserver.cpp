// Include Precompiled Header.
#include "vprecompiled.h"

#include "sample_vserver.h"
#include "vsockettype.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    // Create and run the server.
    SampleServer* server = new SampleServer ( SOCKET_UDP );
    server->Run ();
    
    system ( "pause" );
    return 0;
}
