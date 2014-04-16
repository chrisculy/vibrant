/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: ut_vstring.cpp
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

#include "ut_vstring.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION ( UT_String, UT_String::GetSuiteName () );

void UT_String :: setUp ()
{
    
}

void UT_String :: tearDown ()
{

}

void UT_String :: test_class_instantiation ()
{
    String str1;
    String str2 = "Vibrant";
    String* str3 = new String ();
    String* str4 = new String ( "Vibrant Engine" );
}

void UT_String :: test_length ()
{
    String a;
    String b = "Vibrant";
    String* c = new String ();
    String* d = new String ( "Vibrant Engine" );
    
    CPPUNIT_ASSERT_EQUAL ( a.Length (), 0 );
    CPPUNIT_ASSERT_EQUAL ( b.Length (), 7 );
    CPPUNIT_ASSERT_EQUAL ( c->Length (), 0 );
    CPPUNIT_ASSERT_EQUAL ( d->Length (), 14 );
}

std::string UT_String :: GetSuiteName ()
{
    return "UT_String";
}
