/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_vqueue.h
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

#ifndef UT_VQUEUE_H
#define UT_VQUEUE_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "vqueue.h"

using namespace Vibrant;

/**
 * @brief Provides unit tests for Queue.
 * 
 * @see Queue
 * @author Chris Culy
 */
class UT_Queue : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE ( UT_Queue );
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
