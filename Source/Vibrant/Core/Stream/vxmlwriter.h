/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vxmlwriter.h
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

#ifndef VIBRANT_XMLWRITER_H
#define VIBRANT_XMLWRITER_H

#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Provides a writer for XML files.
     * 
     * @author Chris Culy
     * @see Writer
     */
    class VAPI XMLWriter : public Writer
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param stream The stream to use when writing.
             * @throws NullPointerException If <code>stream</code>
             *      is <code>null</code>.
             */
            XMLWriter ( Stream* stream );

            /**
             * @see Writer#BeginObject(String)
             */
            void BeginObject ( const String& type );

            /**
             * @see Writer#BeginBase()
             */
            void BeginBase ();

            /**
             * @see Writer#WriteChild(Serializable*)
             */
            void WriteChild ( const Serializable* child );

            /**
             * @see Writer#EndBase()
             */
            void EndBase ();

            /**
             * @see Writer#EndObject()
             */
            void EndObject ();

            /**
             * @see Writer#WriteProperty(String, unsigned short)
             */
            void WriteProperty ( const String& name, const unsigned short& val );

            /**
             * @see Writer#WriteProperty(String, unsigned short*, int)
             */
            void WriteProperty ( const String& name, const unsigned short* val, const int size );
            
            /**
             * @see Writer#WriteProperty(String, short)
             */
            void WriteProperty ( const String& name, const short& val );

            /**
             * @see Writer#WriteProperty(String, short*, int)
             */
            void WriteProperty ( const String& name, const short* val, const int size );

            /**
             * @see Writer#WriteProperty(String, unsigned int)
             */
            void WriteProperty ( const String& name, const unsigned int& val );

            /**
             * @see Writer#WriteProperty(String, unsigned int*, int)
             */
            void WriteProperty ( const String& name, const unsigned int* val, const int size );
            
            /**
             * @see Writer#WriteProperty(String, int)
             */
            void WriteProperty ( const String& name, const int& val );

            /**
             * @see Writer#WriteProperty(String, int*, int)
             */
            void WriteProperty ( const String& name, const int* val, const int size );

            /**
             * @see Writer#WriteProperty(String, unsigned long)
             */
            void WriteProperty ( const String& name, const unsigned long& val );

            /**
             * @see Writer#WriteProperty(String, unsigned long*, int)
             */
            void WriteProperty ( const String& name, const unsigned long* val, const int size );
            
            /**
             * @see Writer#WriteProperty(String, long)
             */
            void WriteProperty ( const String& name, const long& val );

            /**
             * @see Writer#WriteProperty(String, long*, int)
             */
            void WriteProperty ( const String& name, const long* val, const int size );

            /**
             * @see Writer#WriteProperty(String, float)
             */
            void WriteProperty ( const String& name, const float& val );

            /**
             * @see Writer#WriteProperty(String, float*, int)
             */
            void WriteProperty ( const String& name, const float* val, const int size );

            /**
             * @see Writer#WriteProperty(String, double)
             */
            void WriteProperty ( const String& name, const double& val );

            /**
             * @see Writer#WriteProperty(String, double*, int)
             */
            void WriteProperty ( const String& name, const double* val, const int size );

            /**
             * @see Writer#WriteProperty(String, bool)
             */
            void WriteProperty ( const String& name, const bool& val );

            /**
             * @see Writer#WriteProperty(String, char)
             */
            void WriteProperty ( const String& name, const char& val );

            /**
             * @see Writer#WriteProperty(String, String)
             */
            void WriteProperty ( const String& name, const String& val );

            //************************ General Interface ***********************//

        protected:
            
            /**
             * @see Writer#BeginArrayProperty(String)
             */
            void BeginArrayProperty ( const String& name );

            /**
             * @see Writer#EndArrayProperty()
             */
            void EndArrayProperty ( const String& name );

            /**
             * @brief Performs the appropriate indentation.
             */
            void DoIndentation ();

            /**
             * @brief Writes the opening tag for a property.
             * 
             * @param name The property's name.
             */
            void BeginProperty ( const String& name );

            /**
             * @brief Writes the end tag for a property.
             * 
             * @param name The property's name.
             */
            void EndProperty ( const String& name );

        private:
            
            /** @brief Holds the current indentation (in number of tabs). */
            unsigned short indentation;

            /** @brief Holds the writer's mode. */
            Stack< WriterMode > mode;

            /** @brief Holds the type of the object currently being written. */
            Stack< String > currentObjectType;

            // XML Output Formatting Constants.
            static const int XML_OUTPUT_ARRAY_ELEMENTS_PER_LINE = 25;

            // XML Output Character Constants.
            static const vchar XML_OUTPUT_SLASH = '/';
            static const vchar XML_OUTPUT_OPEN_TAG = '<';
            static const vchar XML_OUTPUT_END_TAG = '>';
            static const vchar XML_OUTPUT_COLON = ':';
            static const vchar XML_OUTPUT_SPACE = ' ';
            static const vchar XML_OUTPUT_EQUALS = '=';
            static const vchar XML_OUTPUT_LEFT_BRACE = '{';
            static const vchar XML_OUTPUT_RIGHT_BRACE = '}';
            static const vchar XML_OUTPUT_COMMA = ',';
            static const vchar XML_OUTPUT_QUOTE = '\"';
            static const vchar XML_OUTPUT_INDENT = '\t';
            static const vchar XML_OUTPUT_NEWLINE = '\n';
    };

}

#endif
