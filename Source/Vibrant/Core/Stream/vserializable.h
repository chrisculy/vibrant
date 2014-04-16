/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vserializable.h
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

#ifndef VIBRANT_SERIALIZABLE_H
#define VIBRANT_SERIALIZABLE_H

#include "vsystem.h"

namespace Vibrant
{
    
    // Declare needed classes.
    class Writer;
    class Reader;
    
    /**
     * @brief Provides an interface for objects that can
     * be written to or read from using a Writer or Reader.
     * 
     * @author Chris Culy
     */
    class VAPI Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Gets the size of memory used to write 
             * the object to disk or RAM.
             * 
             * @return The amount of memory used to stream the object.
             */
            virtual const int GetDiskSize () const = 0;

            /**
             * @brief Writes the object using the given writer.
             * 
             * @param writer The writer to use.
             * @throws WriteException If any error
             *      occurs while writing the object.
             */
            virtual void Write ( Writer* writer ) const = 0;

            /**
             * @brief Reads the object using the given reader.
             * 
             * @param reader The reader to use.
             * @throws ReadException If any error
             *      occurs while reading the object.
             */
            virtual void Read ( Reader* reader ) = 0;
            
            //************************ General Interface ***********************//
    };

}

#endif
