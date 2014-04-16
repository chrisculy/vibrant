/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvertex.h
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

#ifndef VIBRANT_VERTEX_H
#define VIBRANT_VERTEX_H

#include "varray.h"
#include "vcolor.h"
#include "vhashtable.h"
#include "vobject.h"
#include "vpointer.h"
#include "vreader.h"
#include "vserializable.h"
#include "vstring.h"
#include "vtexturecoord.h"
#include "vvector.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /** 
     * @brief Encapsulates the influence of a bone
     * on a vertex (used for animations).
     */
    struct VAPI VertexInfluence : public Serializable
    {
        public:
            
            /**
             * @brief Destructor.
             */
            virtual ~VertexInfluence ();

            /** @brief Holds the name of the bone. */
            String boneName;

            /** @brief Holds the weight of the bone's
             * influence on the vertex (between 0.0 and 1.0). */
            float boneWeight;

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );
    };
    
    /**
     * @brief Encapsulates the various attributes of a vertex in
     * three-dimensional space, including the vertex's position,
     * normal vector, color, and texture coordinate.
     * 
     * @see Vector
     * @see TextureCoord
     * @see Color
     * @author Chris Culy
     */
    class VAPI Vertex : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs a vertex using the specified parameters.
             * 
             * @param position The position of the vertex.
             * @param normal The normal vector of the vertex.
             * @param textureCoord The UV texture coordinate for the vertex.
             * @param color The color of the vertex.
             */
            Vertex ( Vector position = Vector ( 0.0, 0.0, 0.0 ), Vector normal = Vector ( 0.0, 0.0, 0.0 ), TextureCoord textureCoord =
                TextureCoord ( 0.0, 0.0 ), Color color = Color ( 0.0, 0.0, 0.0, 1.0 ) );

            /**
             * @brief Constructs a vertex using the specified parameters.
             * 
             * @param position The position of the vertex.
             * @param normal The normal vector of the vertex.
             * @param textureCoords The UV texture coordinates for the vertex.
             * @param color The color of the vertex.
             */
            Vertex ( Vector position, Vector normal, Hashtable< int, TextureCoord > textureCoords, Color color );

            /**
             * @brief Constructs a vertex from another vertex.
             * 
             * @param vertex The vertex to construct this vertex from.
             */
            Vertex ( const Vertex& vertex );

            /**
             * @brief Destructor.
             */
            ~Vertex ();

            /**
             * @brief Retrieves the vertex's position.
             * 
             * @return The vertex's position.
             */
            const Vector& GetPosition () const;

            /**
             * @brief Retrieves the vertex's normal.
             * 
             * @return The vertex's normal.
             */
            const Vector& GetNormal () const;

            /**
             * @brief Retrieves the vertex's texture coordinate for the given image.
             * 
             * @param uvImageID The ID of the UV image that
             *      the texture coordinate corresponds to.
             * @return The vertex's texture coordinate for the
             *      given image, or the texture coordinate for
             *      the default image if the texture coordinate
             *      for the given image does not exist.
             * @throws EmptyContainerException If there are
             *      no texture coordinates for the vertex.
             */
            const TextureCoord& GetTextureCoord ( int uvImageID = 0 ) const;

            /**
             * @brief Retrieves the vertex's texture coordinates for all images.
             * 
             * @return The vertex's texture coordinates.
             */
            const Hashtable< int, TextureCoord >& GetTextureCoords () const;

            /**
             * @brief Retrieves the vertex's color.
             * 
             * @return The vertex's color.
             */
            const Color& GetColor () const;

            /**
             * @brief Sets the vertex's position.
             * 
             * @param position The vertex's new position.
             */
            void SetPosition ( const Vector& position );

            /**
             * @brief Sets the vertex's normal.
             * 
             * @param normal The vertex's new normal.
             */
            void SetNormal ( const Vector& normal );

            /**
             * @brief Sets the vertex's texture coordinate
             * for the given image.
             * 
             * <p>
             * If the texture coordinate for the given image
             * does not exist, it is created.
             * Note: The UV image ID that is used to set
             * the texture coordinate is the one returned
             * from textureCoord.GetUVImageID () so the
             * UV image ID within the texture coordinate
             * object needs to be correct.
             * </p>
             * 
             * @param textureCoord The vertex's new texture coordinate.
             */
            void SetTextureCoord ( const TextureCoord& textureCoord );

            /**
             * @brief Sets the vertex's texture coordinates for all images.
             * 
             * @param textureCoords The vertex's new texture coordinates.
             */
            void SetTextureCoords ( const Hashtable< int, TextureCoord >& textureCoords );

            /**
             * @brief Sets the vertex's color.
             * 
             * @param color The vertex's new color.
             */
            void SetColor ( const Color& color );

            /**
             * @brief Retrieves the vertex's (bone) influences.
             * 
             * @return The vertex's influences.
             */
            Array< VertexInfluence >* GetVertexInfluences () const;

            /**
             * @brief Represents the data used to represent a vertex in vertex buffers.
             * 
             * @author Chris Culy
             */
            struct VertexData
            {
                public:
                    // Position.
                    float x, y, z;
                    // Normal.
                    float nx, ny, nz;
                    // Color.
                    float r, g, b, a;
                    // Texture Coordinates.
                    float s0, t0;
                    float s1, t1;
                    float s2, t2;
            };

            /**
             * @brief Used to stream VertexData objects.
             * 
             * @author Chris Culy
             */
            class VertexDataSerializer : public Serializable
            {
                public:
                    
                    //************************ General Interface ***********************//

                    /**
                     * @brief Creates a VertexDataSerializer that can be used to read into the given VertexData object.
                     * 
                     * @param data The vertex data object to read into.
                     */
                    static VertexDataSerializer* MakeReadable ( VertexData* data );
                    /**
                     * @brief Creates a VertexDataSerializer that can be used to write out the given VertexData object.
                     * 
                     * @param data The vertex data object to write out.
                     */
                    static VertexDataSerializer* MakeWritable ( const VertexData* data );

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
                    /**
                     * @brief Constructor (made private to prevent normal construction-use the static methods instead).
                     */
                    VertexDataSerializer ();

                    /** Holds the vertex data to be read in. */
                    VertexData* readData;

                    /** Holds the vertex data to be written out. */
                    const VertexData* writeData;
            };

            /** @brief Holds the size of a VertexData structure
             * 
             * This should always be a multiple of 32 bytes (for ATI cards).
             * (See http://www.opengl.org/wiki/Vertex_Buffer_Objects)
             * 
             * @see VertexBuffer
             */
            static const unsigned int DATA_SIZE = sizeof(VertexData);

            /** Holds the offset within the VertexData structure to the position data. */
            static const unsigned int POSITION_OFFSET = 0;
            /** Holds the offset within the VertexData structure to the normal data. */
            static const unsigned int NORMAL_OFFSET = 12;
            /** Holds the offset within the VertexData structure to the color data. */
            static const unsigned int COLOR_OFFSET = 24;
            /** Holds the offset within the VertexData structure to the first texture coordinates data. */
            static const unsigned int TEXTURE_COORDS_0_OFFSET = 40;
            /** Holds the offset within the VertexData structure to the second texture coordinates data. */
            static const unsigned int TEXTURE_COORDS_1_OFFSET = 48;
            /** Holds the offset within the VertexData structure to the third texture coordinates data. */
            static const unsigned int TEXTURE_COORDS_2_OFFSET = 56;

            /**
             * @brief Retrieves the vertex's data (used to represent the vertex in a vertex buffer).
             * 
             * @return The vertex's data.
             */
            VertexData GetVertexData ();

            //************************ General Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );

            //************************ Streaming system ************************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all vertices.
             * 
             * @return The Vertex RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Retrieves the number of texture
             * coordinates the vertex has.
             * 
             * @return The number of texture coordinates.
             */
            int TextureCoordCount () const;

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the vertex's position. */
            Vector position;

            /** @brief Holds the vertex's normal vector. */
            Vector normal;

            /** @brief Holds the vertex's color. */
            Color color;

            /** @brief Holds the vertex's texture coordinates
             * referenced by the corresponding texture
             * index (same as textureCoord.GetUVImageID ()). */
            Hashtable< int, TextureCoord > textureCoords;

            /** @brief Holds the bone influences for the vertex. */
            Array< VertexInfluence >* vertexInfluences;
    };
    
    typedef Pointer< Vertex > VertexPtr;

}

#endif
