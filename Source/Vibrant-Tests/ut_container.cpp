/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_container.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "ut_container.h"

void UT_Container :: run_tests ( CppUnit::TextUi::TestRunner* runner )
{
    // Holds the test suite for each set of unit tests.
    CppUnit::TestSuite* suite = null;
    
    // *** String *** //
    suite = UT_String::suite ();
    runner->addTest ( UT_String::suite () );
    std::cout << "---- Unit Tests : String ----\n\n";
    UT_Runner::run_tests ( runner, suite );
}
