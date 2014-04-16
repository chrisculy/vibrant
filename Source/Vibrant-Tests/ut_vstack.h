/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_vstack.h
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

#ifndef UT_VSTACK_H
#define UT_VSTACK_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "vstack.h"

using namespace Vibrant;

/**
 * @brief Provides unit tests for Stack.
 * 
 * @see Stack
 * @author Chris Culy
 */
class UT_Stack : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE ( UT_Stack );
    CPPUNIT_TEST ( test_class_instantiation );
    CPPUNIT_TEST_SUITE_END ();
    
    public:
        
        /**
         * @brief Sets up the unit tests.
         */
        void setUp ();
        /**
         * @brief Cleans up the unit tests.
         */
        void tearDown ();
        /**
         * @brief Gets the name of the test suite.
         */
        static std::string GetSuiteName ();
        
    protected:
        
        /**
         * @brief Tests class instantiation.
         */
        void test_class_instantiation ();
};

#endif
