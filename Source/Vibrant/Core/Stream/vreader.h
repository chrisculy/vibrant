/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vreader.h
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

#ifndef VIBRANT_READER_H
#define VIBRANT_READER_H

#include "vserializable.h"
#include "vstream.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Provides an interface for reading objects from a stream.
     * 
     * <p>
     * <br>Example usage:<br><br>
     * <pre>
     *  &lt;Implementation of an object's Read () function&gt;
     *  {
     *      // Start an element.
     *      reader->BeginObject ( &lt;object's type&gt; );
     *      
     *      reader->BeginBase ();
     *      &lt;base class&gt;::Read ( reader );
     *      reader->EndBase ();
     *      
     *      // Read in the elements properties.
     *          ...
     *          // For each property.
     *          int objectProperty;
     *          reader->ReadProperty ( &lt;property's name&gt;, &objectProperty ) );
     *          this->set&lt;property's name&gt; ( objectProperty );
     *          ...
     *      
     *      // Read in the children (this can be 
     *      // skipped if there are no children).
     *          ...
     *          // For each child.
     *          reader->ReadChild ( this->child );
     *          ...
     *      
     *      // End an element.
     *      reader->EndObject ();
     *  }
     * </pre>
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI Reader
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param stream The stream to use when reading.
             * @throws NullPointerException If <code>stream</code>
             *      is <code>null</code>.
             */
            Reader ( Stream* stream );

            /**
             * @brief Destructor.
             */
            virtual ~Reader ();

            /**
             * @brief Begins reading an object with the given type.
             * 
             * @param type The type of the object (can be <code>null</code>).
             * @throws ReadException If an object of the given type is
             *      not available to be read.
             */
            virtual void BeginObject ( const String& type ) = 0;

            /**
             * @brief Prepares to read the data from the base class of an object.
             */
            virtual void BeginBase () = 0;

            /**
             * @brief Reads the given child of the object.
             * 
             * @param child The child to be read.
             * @throws NullPointerException If <code>child</code>
             *      is <code>null</code>.
             */
            virtual void ReadChild ( Serializable* child ) = 0;

            /**
             * @brief Cleans up after reading the data from the base class of an object.
             */
            virtual void EndBase () = 0;

            /**
             * @brief Finishes reading the object.
             */
            virtual void EndObject () = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned short* val ) = 0;
            
            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned short* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, short* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, short* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned int* val ) = 0;
            
            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned int* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, int* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, int* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned long* val ) = 0;
            
            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, unsigned long* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, long* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, long* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, float* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, float* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, double* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @param size The value's size (number of elements).
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, double* val, const int size ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, bool* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, char* val ) = 0;

            /**
             * @brief Reads the given property of the object.
             * 
             * @param name The property's name.
             * @param val A reference to store the property's value in.
             * @throws NullPointerException If <code>val</code>
             *      is <code>null</code>.
             * @throws ReadException If the given property cannot be read.
             */
            virtual void ReadProperty ( const String& name, String* val ) = 0;

            //************************ General Interface ***********************//

        private:
            
            /**
             * @brief Begins reading an array property.
             * 
             * @param name The name of the array property.
             */
            virtual void BeginArrayProperty ( const String& name ) = 0;

            /**
             * @brief Finishes reading an array property.
             */
            virtual void EndArrayProperty () = 0;

            /**
             * @brief Represents the different reader modes:
             * 
             * <p>
             * The reader modes:
             * <ul>
             *  <li>READ_OBJECT</li>
             *  <li>READ_BASE</li>
             *  <li>READ_CHILD</li>
             *  <li>READ_PROPERTY</li>
             * </ul>
             * </p>
             */
            enum ReaderMode
            {
                READ_OBJECT,
                READ_BASE,
                READ_CHILD,
                READ_PROPERTY
            };

            /** @brief Holds the reader's stream. */
            Stream* stream;
    };

}

#endif
