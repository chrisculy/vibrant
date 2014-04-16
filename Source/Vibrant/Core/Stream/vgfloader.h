/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgfloader.h
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

#ifndef VIBRANT_VGFLOADER_H
#define VIBRANT_VGFLOADER_H

#include <fstream>

#include "vmesh.h"
#include "vstring.h"
#include "vvector.h"

namespace Vibrant
{
    
    /**
     * @brief Loads a VGF file into a mesh.
     * 
     * @author Chris Culy
     */
    class VAPI VGFLoader
    {
        public:
            
            //************************ General Interface ************************//

            /**
             * @brief Loads a VGF file into a mesh.
             *
             * @param filename The name of the vgf file to load.
             * @param mesh The mesh to load the vgf file into.
             * @throws NullPointerException If mesh is null.
             * @throws IllegalArgumentException If filename is not a valid file path.
             */
            static int Load ( String filename, Mesh* mesh );

            //************************ General Interface ************************//

        private:
            
            //************************* Input Structures ************************//

            /** @brief Holds a VGF file header. */
            struct VGFHeader
            {
                    int val[ 5 ];
            };

            /** @brief Holds a UV coordinate. */
            struct VGFUVCoord
            {
                    float val[ 2 ];
            };

            /** @brief Holds a vector. */
            struct VGFVector
            {
                    float val[ 3 ];
            };

            /** @brief Holds a matrix. */
            struct VGFMatrix
            {
                    float val[ 16 ];
            };

            /** @brief Holds a two integer array. */
            struct int_2
            {
                    int val[ 2 ];
            };

            /** @brief Holds a three integer array. */
            struct int_3
            {
                    int val[ 3 ];
            };

            /** @brief Holds a four integer array. */
            struct int_4
            {
                    int val[ 4 ];
            };

            //************************* Input Structures ************************//
            

            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             * 
             * <p>
             * Note: The constructor is made private to disallow instantiation of this class.
             * </p>
             */
            VGFLoader ();

            /**
             * @brief Loads the header and verifies the file is a *.vgf.
             */
            static bool GetHeader ( Mesh* mesh );

            /**
             * @brief Gets the image info.
             */
            static void GetImageInfo ( Mesh* mesh );

            /**
             * @brief Gets all the objects' data (the code for getting
             * animations is in this function as well.).
             */
            static void GetObjects ( Mesh* mesh );

            /**
             * @brief Processes the objects' faces and retrieves the needed information.
             */
            static void GetFace ( Mesh* mesh, Array< Vertex >& vertices, Array< unsigned short >& indices, int& indicesIndex, int indexCount );

            /**
             * @brief Gets all the armatures.
             */
            static void GetArmatures ( Mesh* mesh );

            /**
             * @brief Gets a vector from the file.
             */
            static Vector GetVector ();

            /** @brief Holds the input file. */
            static FILE* inputFile;

            /** @brief Holds the number of textures. */
            static int textureCount;

            /** @brief Holds the number of frames per second. */
            static int framesPerSecond;

            /** @brief Holds the number of UV images. */
            static int uvImageCount;

            /** @brief Holds the number of armatures (skeletons). */
            static int armatureCount;
            
            //************************ General Interface ************************//
    };

}

#endif
