/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vconvert.h
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

#ifndef VIBRANT_CONVERT_H
#define VIBRANT_CONVERT_H

#include <sstream>

#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Converts a string to a value.
     * 
     * <p>
     * Note: This function assumes that
     * <code>result</code> is a valid pointer.
     * </p>
     * 
     * @param str The string to convert.
     * @param result The value to store the result in.
     */
    template< typename T > VAPI void StringToVal ( String str, T* result )
    {
        std::stringstream* stringStream = new std::stringstream ();
        *stringStream << str.CString ();
        *stringStream >> *result;
    }
    
    /**
     * @brief Converts a value to a string.
     * 
     * <p>
     * Note: This function assumes that
     * <code>result</code> is a valid pointer.
     * </p>
     * 
     * @param val The value to convert.
     * @param result The string to store the result in.
     */
    template< typename T > VAPI void ValToString ( T val, String* result )
    {
        std::stringstream* stringStream = new std::stringstream ();
        *stringStream << val;
        *result = stringStream->str ().c_str ();
    }

}

#endif
