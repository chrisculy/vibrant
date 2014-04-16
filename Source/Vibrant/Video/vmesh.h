/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmesh.h
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

#ifndef VIBRANT_MESH_H
#define VIBRANT_MESH_H

#include "vscenenode.h"
#include "vindexbuffer.h"
#include "vpointer.h"
#include "vreader.h"
#include "vvertexbuffer.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the functionality of a mesh.
     * 
     * <p>
     * Holds vertices (and all their properties) as
     * well as indices into the vertex array and the
     * type of mesh to draw using those vertices and indices.
     * </p>
     * 
     * @see SceneNode
     * @see IndexBuffer
     * @see VertexBuffer
     * @author Chris Culy
     */
    class VAPI Mesh : public SceneNode
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Mesh ();

            /**
             * @brief Constucts a Mesh from the given vertices and
             * indices (protected to make this class abstract).
             * 
             * @param vertices The vertices to build this mesh
             *  from, including positions, normals, colors, etc.
             * @param indices The indices into the vertices for this mesh.
             * @throws NullPointerException If vertices or indices is null.
             */
            Mesh ( VertexBufferPtr vertices, IndexBufferPtr indices );

            /**
             * @brief Destructor.
             */
            virtual ~Mesh ();

            /**
             * @brief Enumeration to define the different mesh
             * types supported by the renderer.
             * 
             * <p>
             * Consider supporting more types such as POLYGON.
             * </p>
             */
            enum MeshType
            {
                TRIANGLE,
                TRIANGLE_FAN,
                TRIANGLE_STRIP,
                LINE_SEGMENT,
                LINE_OPEN,
                LINE_CLOSED,
                POINT,
                QUAD,
                QUAD_STRIP
            };

            /**
             * @brief Retrieves the mesh's vertex information.
             * 
             * <p>
             * (This is used especially by controllers
             * such as {@link ArmatureController}.)
             * </p>
             * 
             * @return The mesh's vertices.
             */
            VertexBufferPtr GetVertices () const;

            /**
             * @brief Retrieves the indices into the mesh's vertices.
             * 
             * @return The mesh's indices.
             */
            IndexBufferPtr GetIndices () const;

            /**
             * @brief Retrieves the mesh's type (used to draw the mesh).
             * 
             * @return The mesh's type.
             */
            const MeshType& GetMeshType () const;

            /**
             * @brief Sets the mesh's vertex information.
             * 
             * @param vertices The mesh's new vertices.
             */
            void SetVertices ( VertexBufferPtr vertices );

            /**
             * @brief Sets the indices into the mesh's vertices.
             * 
             * @param indices The mesh's new indices.
             */
            void SetIndices ( IndexBufferPtr indices );

            /**
             * @brief Sets the mesh's type (used to draw the mesh).
             * 
             * @param type The mesh's new type.
             */
            void SetMeshType ( MeshType type );

            //************************ General Interface ***********************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all meshes.
             * 
             * @return The Mesh RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//
            

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

        protected:
            
            //************************ Update Interface ************************//

            /**
             * @brief Updates down the hierarchy.
             * 
             * <p>
             * Updates controllers, global and lighting states,
             * and world transformation, and all children.
             * </p>
             * 
             * @param time The current system time in milliseconds.
             * @see SceneNode#UpdateDown
             */
            virtual void UpdateDown ( long time );

            /**
             * @brief Updates up the hierarchy.
             * 
             * <p>
             * Updates bounding volumes based upon the node
             * and its children (and their bounding volumes).
             * </p>
             * 
             * @see SceneNode#UpdateUp
             */
            virtual void UpdateUp ();

            /**
             * @brief Updates the mesh's vertices' normals.
             */
            virtual void UpdateNormals ();

            //************************ Update Interface ************************//

        protected:
            
            /** @brief Holds the mesh's type. */
            MeshType type;

            /** @brief Holds the mesh's vertices. */
            VertexBufferPtr vertices;

            /** @brief Holds the mesh's indices. */
            IndexBufferPtr indices;
    };
    
    typedef Pointer< Mesh > MeshPtr;

}

#endif
