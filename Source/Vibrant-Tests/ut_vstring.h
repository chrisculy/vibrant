/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_vstring.h
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

#ifndef UT_VSTRING_H
#define UT_VSTRING_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "vstring.h"

using namespace Vibrant;

/**
 * @brief Provides unit tests for String.
 * 
 * @see String
 * @author Chris Culy
 */
class UT_String : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE ( UT_String );
    CPPUNIT_TEST ( test_class_instantiation );
    CPPUNIT_TEST ( test_length );
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
        /**
         * @brief Tests {@link Vibrant#String#Length}.
         */
        void test_length ();
};

#endif
