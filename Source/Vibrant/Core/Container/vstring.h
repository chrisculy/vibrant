/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vstring.h
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

#ifndef VIBRANT_STRING_H
#define VIBRANT_STRING_H

#include "vprecompiled.h"

#ifdef UNICODE
typedef wchar_t vchar;
#else
typedef char vchar;
#endif

// ------------------------------------------------------------------------- //
// ---- Disable warning about std::string not being exported to the DLL. --- //

#if defined (_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

// --------------------------------- Begin --------------------------------- //
// ------------------------------------------------------------------------- //

namespace Vibrant
{
    
    /**
     * @brief Implements the string data type.
     * 
     * @author Chris Culy
     */
    class VAPI String
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param val The value of the string.
             */
            String ( const vchar* val = null );

            /**
             * @brief Copy constructor.
             * 
             * @param string The string to copy into this string.
             */
            String ( const String& string );

            /**
             * @brief Destructor.
             */
            ~String ();

            /**
             * @brief Returns the C-style string representation of the string.
             * 
             * @returns The C-style string representation.
             */
            const vchar* CString () const;

            /**
             * @brief The capacity of the string.
             * 
             * @returns The capacity of this string.
             */
            const int Capacity ();

            /**
             * @brief Clears the string.
             */
            void Clear ();

            /**
             * @brief Finds the first occurance of the given string.
             * 
             * @param searchString The string to find.
             * @returns The index of the position where the
             *      given string was first found or INVALID_INDEX
             *      if it was not found.
             */
            const int Find ( const String& searchString );

            /**
             * @brief Finds the first occurance of the given string
             * starting at the given index.
             * 
             * @param searchString The string to find.
             * @param index The index to start searching at.
             * @returns The index of the position where the
             *      given string was first found or INVALID_INDEX
             *      if it was not found.
             */
            const int Find ( const String& searchString, int index );

            /**
             * @brief Retrieves whether the string is empty or not.
             * 
             * @return <code>true</code> if the string is empty;
             *      <code>false</code> otherwise.
             */
            bool IsEmpty () const;

            /**
             * @brief Retrieves the length of the string.
             * 
             * @returns The length of the string.
             */
            const int Length () const;

            /**
             * @brief Replaces all occurances of the given search string
             * with the given replace string.
             * 
             * @param searchString The string to find.
             * @param replaceString The string to replace the search string with.
             */
            void Replace ( const String& searchString, const String& replaceString );

            /**
             * @brief Replaces the given section of the string
             * with the given replace string.
             * 
             * @param start The starting index of the section to replace.
             * @param end The ending index of the section to replace (inclusive).
             * @param replaceString The string to replace the specified section with.
             */
            void Replace ( int start, int end, const String& replaceString );

            /**
             * @brief Retrieves the size of the string (number of characters).
             * 
             * @return The size of the string.
             */
            const int Size () const;

            /**
             * @brief Retrieves the given substring of the string.
             * 
             * @param start The starting index of the wanted substring.
             * @param end The ending index of the wanted substring (inclusive).
             */
            String Substring ( int start, int end = -1 );

            /**
             * @brief Retrieves whether the given character is whitespace or not.
             * 
             * @param character The character to test.
             * @return <code>true</code> if the character is whitespace;
             *      <code>false</code> otherwise.
             */
            static bool IsWhitespace ( const vchar& character );

            /**
             * @brief Constant used to indicate an invalid index within the string.
             * 
             * @see String#find(String)
             */
            static const int INVALID_INDEX = -1;

            //************************ General Interface ***********************//
            

            //**************************** Operators ***************************//

            /**
             * @brief Retrieves the specified character within the string.
             * 
             * @param index The index of the wanted character.
             */
            vchar& operator[] ( int index );

            /**
             * @brief Retrieves whether the string is equal to the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if the two strings are
             *      equal;<code>false</code> otherwise.
             */
            bool operator== ( const String& string ) const;

            /**
             * @brief Retrieves whether the string is not equal to the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if the two strings are
             *      not equal;<code>false</code> otherwise.
             */
            bool operator!= ( const String& string ) const;

            /**
             * @brief Retrieves whether the string is less
             * than or equal to the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if this string is less than
             *      or equal to the given string;<code>false</code> otherwise.
             */
            bool operator<= ( const String& string ) const;

            /**
             * @brief Retrieves whether the string is greater
             * than or equal to the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if this string is greater than
             *      or equal to the given string;<code>false</code> otherwise.
             */
            bool operator>= ( const String& string ) const;

            /**
             * @brief Retrieves whether the string is less than the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if this string is less than
             *      the given string;<code>false</code> otherwise.
             */
            bool operator< ( const String& string ) const;

            /**
             * @brief Retrieves whether the string is greater than the given string.
             * 
             * @param string The string to compare to.
             * @return <code>true</code> if this string is greater than
             *      the given string;<code>false</code> otherwise.
             */
            bool operator> ( const String& string ) const;

            /**
             * @brief Retrieves the concatenation of this string with the given string.
             * 
             * @param string The string to concatenate.
             * @return The concatenation of this string with the given string.
             */
            String operator+ ( const String& string ) const;

            /**
             * @brief Assigns the given string to this string.
             * 
             * @param string The string to assign to this string.
             * @return This string after it has been assigned to the given string.
             */
            String& operator= ( const String& string );

            /**
             * @brief Appends the given string to this string.
             * 
             * @param string The string to append.
             * @return This string after it has been assigned to the given string.
             */
            String& operator+= ( const String& string );

            //**************************** Operators ***************************//

        private:
            
            /** @brief Holds the value of the string. */
            std::basic_string< vchar, std::char_traits< vchar >, std::allocator< vchar > > val;
    };
    
    /**
     * @brief Retrieves the concatenation of the first string with the second string.
     * 
     * @param firstString The first string.
     * @param secondString The second string.
     * @return The concatenation of the first string with the second string.
     */
    String VAPI operator+ ( const vchar* firstString, const String& secondString );
    /**
     * @brief Writes a string to a standard output stream.
     * 
     * @param os The stream to write out to.
     * @param val The string to write out.
     * @return The output stream.
     */
    VAPI std::ostream& operator<< ( std::ostream& os, const String& val );
    /**
     * @brief Reads a string from a standard input stream.
     * 
     * @param is The stream to read into from.
     * @param val The string to read into.
     * @return The input stream.
     */
    VAPI std::istream& operator>> ( std::istream& is, String& val );

}

// ------------------------------------------------------------------------- //
// ---- Disable warning about std::string not being exported to the DLL. --- //

#if defined (_MSC_VER)
#pragma warning(pop)
#endif

// ---------------------------------- End ---------------------------------- //
// ------------------------------------------------------------------------- //

#endif
