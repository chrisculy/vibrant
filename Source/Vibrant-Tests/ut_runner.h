/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_runner.h
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

#ifndef UT_RUNNER_H
#define UT_RUNNER_H

#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Generic utility for running unit tests.
 * 
 * <p>
 * Note: This doesn't necessarily need to
 * be an entire-it could just be a utility
 * function, so consider doing that instead.
 * </p>
 * 
 * @author Chris Culy
 */
class UT_Runner
{
    public:
        
        /**
         * @brief Runs the unit tests specified
         * by the given list of test names.
         * 
         * @param runner The unit test runner.
         * @param suite The set (or suite) of unit tests to run.
         */
        static void run_tests ( CppUnit::TextUi::TestRunner* runner, CppUnit::TestSuite* suite )
        {
            for ( int i = 0; i < suite->getChildTestCount (); i++ )
            {
                std::cout << "Running unit test: " << suite->getChildTestAt ( i )->getName ();
                // Only display the results on the last test of the test suite.
                if ( i == suite->getChildTestCount () - 1 )
                {
                    runner->run ( suite->getChildTestAt ( i )->getName () );
                }
                else
                {
                    runner->run ( suite->getChildTestAt ( i )->getName (), false, false );
                }
            }
        }
};

#endif
