#include <iostream>
#include <string>

#include "sample_vsingletontest.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    // You must create the singleton object before accessing it.
    try
    {
        SingletonTest* test = SingletonTest::GetInstance ();
    }
    catch ( NullPointerException e )
    {
        std::cout << "The following null pointer exception is expected:\n";
        std::cout << e.GetMessage () << "\n\n";
    }

    SingletonTest theSingleton ( 1, 2, 3 );
    
    // Get the singleton object.
    SingletonTest* test = SingletonTest::GetInstance ();
    
    // Do some stuff with it.
    std::cout << "x: " << test->GetX () << "; y: " << test->GetY () << "\n\n";
    
    // Attempt to create another object (this should fail).
    try
    {
        SingletonTest anotherSingleton ( 0, 0, 0 );
    }
    catch ( IllegalOperationException e )
    {
        std::cout << "The following illegal operation exception is expected:\n";
        std::cout << e.GetMessage () << "\n\n";
    }

    system ( "pause" );
    return 0;
}
