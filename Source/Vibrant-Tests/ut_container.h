/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_container.h
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

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <string>
#include <vector>

#include "ut_runner.h"
#include "ut_vstring.h"

/**
 * @brief Runs unit tests on the Container classes.
 * 
 * @see UT_Array
 * @see UT_ArrayList
 * @see UT_HashTable
 * @see UT_IndexBuffer
 * @see UT_LinkedList
 * @see UT_Queue
 * @see UT_Runner
 * @see UT_Stack
 * @see UT_String
 * @see UT_VertexBuffer
 * @author Chris Culy
 */
class UT_Container
{
    public:
        
        /**
         * @brief Runs the unit tests.
         * 
         * @param runner The unit test runner.
         */
        static void run_tests ( CppUnit::TextUi::TestRunner* runner );
};
