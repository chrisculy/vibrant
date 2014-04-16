/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vstring.cpp
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

#include "vstring.h"

namespace Vibrant
{
    
    String::String ( const vchar* val )
    {
        if ( val == null )
        {
            this->val = "";
        }
        else
        {
            this->val = val;
        }
    }
    
    String::String ( const String& string )
    {
        this->val = string.val;
    }
    
    String::~String ()
    {
        /* stub function */
    }
    
    const vchar* String::CString () const
    {
        return this->val.c_str ();
    }
    
    const int String::Capacity ()
    {
        return this->val.capacity ();
    }
    
    void String::Clear ()
    {
        this->val.clear ();
    }
    
    const int String::Find ( const String& searchString )
    {
        unsigned int index = this->val.find ( searchString.val );
        return ( index == std::string::npos ) ? String::INVALID_INDEX : (int) index;
    }
    
    const int String::Find ( const String& searchString, int index )
    {
        unsigned int resultIndex = this->val.find ( searchString.val, index );
        return ( resultIndex == std::string::npos ) ? String::INVALID_INDEX : (int) resultIndex;
    }
    
    bool String::IsEmpty () const
    {
        return this->val.empty ();
    }
    
    const int String::Length () const
    {
        return this->val.length ();
    }
    
    void String::Replace ( const String& searchString, const String& replaceString )
    {
        unsigned int index = val.find ( searchString.val );
        while ( index != std::string::npos )
        {
            this->val.erase ( index, searchString.Length () );
            this->val.insert ( index, replaceString.val );
            index += replaceString.Length ();
            index = this->val.find ( searchString.val, index );
        }
    }
    
    void String::Replace ( int start, int end, const String& replaceString )
    {
        this->val.erase ( start, end - start + 1 );
        this->val.insert ( start, replaceString.val );
    }
    
    const int String::Size () const
    {
        return this->val.size ();
    }
    
    String String::Substring ( int start, int end )
    {
        return ( end == -1 ) ? this->val.substr ( start ).c_str () : this->val.substr ( start, end + 1 ).c_str ();
    }
    
    bool String::IsWhitespace ( const vchar& character )
    {
        // Test against whitespace characters
        // in approximate order of frequency.
        if ( character == ' ' || character == '\n' || character == '\t' || character == '\r' || character == '\f' || character == '\v' )
        {
            return true;
        }
        return false;
    }
    
    vchar& String::operator[] ( int index )
    {
        return this->val[ index ];
    }
    
    bool String::operator== ( const String& string ) const
    {
        return this->val == string.val;
    }
    
    bool String::operator!= ( const String& string ) const
    {
        return this->val != string.val;
    }
    
    bool String::operator<= ( const String& string ) const
    {
        return this->val <= string.val;
    }
    
    bool String::operator>= ( const String& string ) const
    {
        return this->val >= string.val;
    }
    
    bool String::operator< ( const String& string ) const
    {
        return this->val < string.val;
    }
    
    bool String::operator> ( const String& string ) const
    {
        return this->val > string.val;
    }
    
    String String::operator+ ( const String& string ) const
    {
        return ( this->val + string.val ).c_str ();
    }
    
    String& String::operator= ( const String& string )
    {
        this->val = string.val;
        return *this;
    }
    
    String& String::operator+= ( const String& string )
    {
        this->val.append ( string.val );
        return *this;
    }
    
    String operator+ ( const vchar* firstString, const String& secondString )
    {
        String str = firstString;
        return str + secondString;
    }
    
    std::ostream& operator<< ( std::ostream& os, const String& val )
    {
        return os << val.CString ();
    }
    
    std::istream& operator>> ( std::istream& is, String& val )
    {
        std::string tmp;
        is >> tmp;
        val = tmp.c_str ();
        return is;
    }

}
