/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvertexbuffer.h
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

#ifndef VIBRANT_VERTEXBUFFER_H
#define VIBRANT_VERTEXBUFFER_H

#include "varray.h"
#include "vpointable.h"
#include "vpointer.h"
#include "vreader.h"
#include "vserializable.h"
#include "vvertex.h"
#include "vwriter.h"

namespace Vibrant
{
    /** @brief Represents the system graphics handle to a vertex buffer. */
    typedef unsigned int VertexBufferHandle;
    
    /**
     * @brief Represents a vertex buffer.
     * 
     * @author Chris Culy
     */
    class VAPI VertexBuffer : public Pointable, public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param vertices The vertex data.
             * @param count The number of vertices.
             */
            VertexBuffer ( Vertex* vertices, unsigned int count );
            /**
             * @brief Destructor.
             */
            ~VertexBuffer ();

            /**
             * @brief Binds the vertex buffer to be used for rendering.
             */
            void Bind ();
            /**
             * @brief Unbinds the vertex buffer.
             */
            void Unbind ();

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
            /** @brief Holds the vertex data. */
            Array< Vertex::VertexData > buffer;

            /** @brief Holds the system graphics handle to the vertex buffer. */
            VertexBufferHandle handle;
    };
    
    typedef Pointer< VertexBuffer > VertexBufferPtr;
}

#endif
