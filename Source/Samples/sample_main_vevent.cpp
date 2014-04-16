#include <iostream>
#include <map>
#include <string>

#include "sample_mysender.h"
#include "sample_mylistener.h"
#include "veventsystem.h"
#include "vevent.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    SampleSender sender;
    SampleListener listener;
    
    std::cout << "Expected output is 'Handled SampleSender event with arg = 2'\n\n";
    
    sender.senderEvent.Subscribe ( EventSystem::MakeListener ( listener, &SampleListener::OnSenderEvent ) );
    sender.senderEvent.Fire ( &sender, 2 );
    
    std::cout << "\n";
    system ( "pause" );
    return 0;
}
