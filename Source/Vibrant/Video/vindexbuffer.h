/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vindexbuffer.h
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

#ifndef VIBRANT_INDEXBUFFER_H
#define VIBRANT_INDEXBUFFER_H

#include "varray.h"
#include "vpointable.h"
#include "vpointer.h"
#include "vreader.h"
#include "vserializable.h"
#include "vwriter.h"

namespace Vibrant
{
    /** @brief Represents the system graphics handle to a index buffer. */
    typedef unsigned int IndexBufferHandle;
    
    /**
     * @brief Represents an index buffer.
     * 
     * @author Chris Culy
     */
    class VAPI IndexBuffer : public Pointable, public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param indices The index data.
             * @param count The number of indices.
             */
            IndexBuffer ( unsigned short* indices, unsigned int count );
            /**
             * @brief Destructor.
             */
            ~IndexBuffer ();

            /**
             * @brief Binds the vertex buffer to be used for rendering.
             */
            void Bind ();
            /**
             * @brief Unbinds the vertex buffer.
             */
            void Unbind ();
            /**
             * @brief Retrieves the size of the index buffer.
             * 
             * @return The size of the index buffer.
             */
            const int Size () const;

            //************************ General Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            virtual const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            virtual void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            virtual void Read ( Reader* reader );

            //************************ Streaming system ************************//

        private:
            /** @brief Holds the index data. */
            Array< unsigned short > buffer;

            /** @brief Holds the system graphics handle to the index buffer. */
            IndexBufferHandle handle;
    };
    
    typedef Pointer< IndexBuffer > IndexBufferPtr;
}

#endif
