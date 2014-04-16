// Include Precompiled Header.
#include "vprecompiled.h"

#include "vasynchronous.h"
#include "vsystem.h"
#include "vthread.h"

#include VIBRANT_TIME_INCLUDE_FILE

using namespace Vibrant;

/**
 * @brief Sample asynchronous state class.
 * 
 * @author Chris Culy
 */
class AsynchTestState : public AsynchState
{
    public:
        
        /** @brief Holds a test variable. */
        int test;
};

/**
 * @brief Sample test function to be executed asynchronously.
 * 
 * @param state The asynchronous state for the sample operation.
 */
void TestFunction ( AsynchState* state )
{
    AsynchTestState* testState = (AsynchTestState*) state;
    std::cout << "Test variable: " << testState->test << "\n";
}

int main ( int argc, char** argv )
{
    // Create the time system.
    Time* time = new VIBRANT_TIME ();
    
    AsynchCallback callback = &TestFunction;
    AsynchTestState testState;
    testState.test = 42;
    
    std::cout << "Expected output is \'Test variable: 42\'\n\n";
    Thread* thread = Thread::Execute ( callback, &testState );
    
    std::cout << "\n";
    system ( "pause" );
    delete thread;
    
    // Clean up the time system.
    delete time;
    
    return 0;
}
