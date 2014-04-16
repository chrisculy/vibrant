/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwriter.h
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

#ifndef VIBRANT_WRITER_H
#define VIBRANT_WRITER_H

#include "vserializable.h"
#include "vstack.h"
#include "vstream.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Provides an interface for writing objects to a stream.
     * 
     * <p>
     * <br>Example usage:<br><br>
     * <pre>
     *  &lt;Implementation of an object's Write () function&gt;
     *  {
     *      // Start an element.
     *      writer->BeginObject ( &lt;object's type&gt; );
     *      
     *      writer->BeginBase ();
     *      &lt;base class&gt;::Write ( writer );
     *      writer->EndBase ();
     *      
     *      // Write out the elements properties.
     *          ...
     *          // For each property.
     *          writer->WriteProperty ( &lt;property's name&gt;, &lt;property's value&gt; );
     *          ...
     *      
     *      // Write out the children (this can be 
     *      // skipped if there are no children).
     *          ...
     *          // For each child.
     *          writer->WriteChild ( this->child );
     *          ...
     *      
     *      // End an element.
     *      writer->EndObject ();
     *  }
     * </pre>
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI Writer
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
            Writer ( Stream* stream );

            /**
             * @brief Destructor.
             */
            virtual ~Writer ();

            /**
             * @brief Begins writing an object with the given type.
             * 
             * @param type The type of the object.
             */
            virtual void BeginObject ( const String& type ) = 0;

            /**
             * @brief Prepares to write the data from the base class of an object.
             */
            virtual void BeginBase () = 0;

            /**
             * @brief Writes the given child of the object.
             * 
             * @param child The child to be written.
             * @throws NullPointerException If <code>child</code>
             *      is <code>null</code>.
             */
            virtual void WriteChild ( const Serializable* child ) = 0;

            /**
             * @brief Cleans up after writing the data from the base class of an object.
             */
            virtual void EndBase () = 0;

            /**
             * @brief Finishes writing the object.
             */
            virtual void EndObject () = 0;

            /**
             * @brief Writes all currently written data to the stream.
             */
            virtual void Write ();

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const unsigned short& val ) = 0;
            
            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const unsigned short* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const short& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const short* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const unsigned int& val ) = 0;
            
            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const unsigned int* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const int& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const int* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const unsigned long& val ) = 0;
            
            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const unsigned long* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const long& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const long* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const float& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const float* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const double& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             * @param size The value's size (number of elements).
             */
            virtual void WriteProperty ( const String& name, const double* val, const int size ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const bool& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const char& val ) = 0;

            /**
             * @brief Writes the given property of the object.
             * 
             * @param name The property's name.
             * @param val The property's value.
             */
            virtual void WriteProperty ( const String& name, const String& val ) = 0;

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Begins writing an array property.
             * 
             * @param name The name of the array property.
             */
            virtual void BeginArrayProperty ( const String& name ) = 0;

            /**
             * @brief Finishes writing an array property.
             */
            virtual void EndArrayProperty ( const String& name ) = 0;

            /**
             * @brief Represents the different writer modes.
             * 
             * <p>
             * The writer modes:
             * <ul>
             *  <li>WRITER_OBJECT</li>
             *  <li>WRITER_BASE</li>
             *  <li>WRITER_CHILD</li>
             *  <li>WRITER_PROPERTY</li>
             * </ul>
             * </p>
             */
            enum WriterMode
            {
                WRITE_OBJECT,
                WRITE_BASE,
                WRITE_CHILD,
                WRITE_PROPERTY
            };

            /** Holds the writer's stream. */
            Stream* stream;
            
            //************************ General Interface ***********************//
    };

}

#endif
