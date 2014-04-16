/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgfloader.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "varmaturecontroller.h"
#include "varray.h"
#include "vexception.h"
#include "vgfloader.h"
#include "vlog.h"
#include "vmatrix.h"
#include "vstring.h"
#include "vtexture.h"
#include "vtextureeffect.h"

namespace Vibrant
{
    
    // Initialize static members.
    FILE* VGFLoader::inputFile = null;
    int VGFLoader::textureCount = 0;
    int VGFLoader::framesPerSecond = 0;
    int VGFLoader::uvImageCount = 0;
    int VGFLoader::armatureCount = 0;
    
    int VGFLoader::Load ( String filename, Mesh* mesh )
    {
        // Check to make sure mesh is valid.
        if ( mesh == null )
        {
            throw NullPointerException ( "VGFLoader::load - Mesh to load into was null." );
        }

        // Reset static members.
        inputFile = null;
        textureCount = 0;
        framesPerSecond = 0;
        uvImageCount = 0;
        armatureCount = 0;
        
        //vlog << INF << "Loading VGF file: " << filename << "...\n";
#ifdef _MSC_VER
        fopen_s ( &inputFile, filename.CString (), "rb" );
#else
        inputFile = fopen ( filename.CString (), "rb" );
#endif
        if ( inputFile == null )
        {
            throw IllegalArgumentException ( "VGFLoader::load - Invalid file path." );
        }

        if ( !GetHeader ( mesh ) )
        {
            //vlog << ERR << "Unexpected file type; not a valid vgf file.\n";
            return -1;
        }

        GetImageInfo ( mesh );
        GetObjects ( mesh );
        
        // Close the file.
        fclose ( inputFile );
        
        //vlog << INF << "VGF file loaded successfully.\n";
        return 0;
    }
    
    bool VGFLoader::GetHeader ( Mesh* mesh )
    {
        // Validate the file identifier.
        VGFHeader tmp;
        fread ( tmp.val, 1, sizeof(VGFHeader), inputFile );
        
        // Make sure this is a valid VGF file.
        if ( tmp.val[ 0 ] != 0x9999 )
        {
            return false;
        }

        // Load all the basic data for the model.
        textureCount = tmp.val[ 1 ];
        framesPerSecond = tmp.val[ 2 ];
        uvImageCount = tmp.val[ 3 ];
        armatureCount = tmp.val[ 4 ];
        return true;
    }
    
    void VGFLoader::GetImageInfo ( Mesh* mesh )
    {
        vchar *tmpName, *tmpFilename;
        int_2 tmpInt;
        
        // Get all the UV textures.
        for ( int i = 0; i < textureCount; i++ )
        {
            // Read in the length of the UV texture's name and filename.
            fread ( tmpInt.val, 1, sizeof(int_2), inputFile );
            tmpName = new vchar[ tmpInt.val[ 0 ] + 1 ];
            tmpFilename = new vchar[ tmpInt.val[ 1 ] + 1 ];
            
            // Read in the UV texture's name and filename.
            fread ( tmpName, 1, ( sizeof(vchar) * ( tmpInt.val[ 0 ] ) ), inputFile );
            fread ( tmpFilename, 1, ( sizeof(vchar) * ( tmpInt.val[ 1 ] ) ), inputFile );
            tmpName[ tmpInt.val[ 0 ] ] = '\0';
            tmpFilename[ tmpInt.val[ 1 ] ] = '\0';
            
            // Store the texture in mesh.
            mesh->AddEffect ( new TextureEffect ( new Texture ( tmpFilename ) ) );
            //vlog << INF << "VGFLoader: texture filename: " << tmpFilename << "\n";
            //vlog << INF << "VGFLoader: texture name: " << tmpName << "\n";
        }
    }
    
    void VGFLoader::GetObjects ( Mesh* mesh )
    {
        bool usesUV = false;
        int vertexCount = 0;
        int indexCount = 0;
        int faceCount = 0;
        int_4 tmp;
        
        // Get the mesh.
        fread ( tmp.val, 1, sizeof(int_4), inputFile );
        usesUV = ( tmp.val[ 0 ] == 0 ) ? false : true;
        vertexCount = tmp.val[ 1 ];
        indexCount = tmp.val[ 2 ];
        faceCount = tmp.val[ 3 ];
        
        // Initialze mesh variables.
        Array< Vertex > vertices ( vertexCount );
        Array< unsigned short > indices ( indexCount );
        
        // Get all the vertices.
        for ( int j = 0; j < vertexCount; j++ )
        {
            // Store vertex position.
            vertices[ j ].SetPosition ( GetVector () );
            
            // Store vertex normal.
            vertices[ j ].SetNormal ( GetVector () );
        }

        int indicesIndex = 0;
        // Get all the face data.
        for ( int j = 0; j < faceCount; j++ )
        {
            GetFace ( mesh, vertices, indices, indicesIndex, indexCount );
        }

        // Store the loaded vertices and indices.
        VertexBufferPtr vertexBuffer = new VertexBuffer ( vertices, vertexCount );
        IndexBufferPtr indexBuffer = new IndexBuffer ( indices, indexCount );
        mesh->SetVertices ( vertexBuffer );
        mesh->SetIndices ( indexBuffer );
        
        // Get all the armature data.
        GetArmatures ( mesh );
    }
    
    void VGFLoader::GetFace ( Mesh* mesh, Array< Vertex >& vertices, Array< unsigned short >& indices, int& indicesIndex, int indexCount )
    {
        int_2 faceInfo;
        int faceVertexCount;
        unsigned int uvImageID = 0;
        
        // Get the number of vertices in this face.
        fread ( &faceInfo, 1, sizeof(int_2), inputFile );
        faceVertexCount = faceInfo.val[ 0 ];
        uvImageID = faceInfo.val[ 1 ];
        
        //DEBUG:
        //vlog << INF << "# of Face Vertices: " << faceVertexCount << "\n";

        // Load the face's vertices.
        for ( int counter = 0; counter < faceVertexCount; counter++, indicesIndex++ )
        {
            // Load the vertex's index (within the mesh).
            int vertexIndex = -1;
            fread ( &vertexIndex, 1, sizeof(int), inputFile );
            if ( indicesIndex < indexCount )
            {
                indices[ indicesIndex ] = vertexIndex;
            }
            else
            {
                //vlog << ERR << "Attempted to store more indices than the mesh has.\n";
            }
            if ( vertexIndex < 0 )
            {
                //vlog << ERR << "Vertex index is invalid (less than zero).\n";
                continue;
            }

            // Load the vertex's UV coordinates.
            VGFUVCoord uvCoords;
            fread ( &uvCoords, 1, sizeof(VGFUVCoord), inputFile );
            vertices[ vertexIndex ].SetTextureCoord ( *( new TextureCoord ( uvCoords.val[ 0 ], uvCoords.val[ 1 ], uvImageID ) ) );
            
            // Get the number of bones that influence the vertex.
            int boneCount = 0;
            fread ( &boneCount, 1, sizeof(int), inputFile );
            
            // Get the vertex's bone influences and prepare
            // them to store the new vertex influences.
            Array< VertexInfluence >* vertexInfluences = vertices[ vertexIndex ].GetVertexInfluences ();
            vertexInfluences->Clear ();
            
            // Read in the vertex influences and store them.
            for ( int boneIndex = 0; boneIndex < boneCount; boneIndex++ )
            {
                // Get the length of the bone's name.
                int boneNameLength = 0;
                fread ( &boneNameLength, 1, sizeof(int), inputFile );
                
                // Get the bone's name.
                vchar* boneName = new vchar[ boneNameLength + 1 ];
                fread ( boneName, 1, sizeof(vchar) * boneNameLength, inputFile );
                boneName[ boneNameLength ] = '\0';
                
                // Get the bone's weight.
                float boneWeight = 0.0;
                fread ( &boneWeight, 1, sizeof(float), inputFile );
                
                // Store the bone influence data.
                VertexInfluence boneInfluence;
                boneInfluence.boneName = boneName;
                boneInfluence.boneWeight = boneWeight;
                vertexInfluences->Push ( boneInfluence );
            }
        }
    }
    
    void VGFLoader::GetArmatures ( Mesh* mesh )
    {
        int boneCount = 0;
        int actionCount = 0;
        int_2 armatureInfo;
        
        //DEBUG
        //vlog << "Armatures: \n";

        // Get all armatures.
        for ( int armatureIndex = 0; armatureIndex < armatureCount; armatureIndex++ )
        {
            //DEBUG
            //vlog << "Armature " << armatureIndex << ": \n";

            // Get the number of bones and the number of actions.
            fread ( &armatureInfo, 1, sizeof(int_2), inputFile );
            boneCount = armatureInfo.val[ 0 ];
            actionCount = armatureInfo.val[ 1 ];
            
            //DEBUG
            //vlog << "Number of Bones: " << boneCount << "\n";
            //vlog << "Number of Actions: " << actionCount << "\n";

            // Initialize variables to hold the
            // bones and actions for this armature.
            Array< Bone >* bones = new Array< Bone > ();
            Array< Action >* actions = new Array< Action > ();
            
            // Get all the actions.
            int_3 actionInfo;
            int keyframeCount = 0;
            int* keyframes = null;
            for ( int actionIndex = 0; actionIndex < actionCount; actionIndex++ )
            {
                // Read the action's start and end
                // frame and the number of keyframes.
                fread ( &actionInfo, 1, sizeof(int_3), inputFile );
                keyframeCount = actionInfo.val[ 2 ];
                keyframes = new int[ keyframeCount ];
                
                // Read the action's keyframes.
                fread ( keyframes, 1, sizeof(int) * keyframeCount, inputFile );
                
                // Store the action.
                Action action;
                action.startFrame = actionInfo.val[ 0 ];
                action.endFrame = actionInfo.val[ 1 ];
                action.keyframeCount = keyframeCount;
                action.keyframes = keyframes;
                actions->Push ( action );
            }

            // Get all the bones.
            for ( int boneIndex = 0; boneIndex < boneCount; boneIndex++ )
            {
                // Get the length of the bone's name.
                int boneNameLength = 0;
                fread ( &boneNameLength, 1, sizeof(int), inputFile );
                
                // Get the bone's name.
                vchar* boneName = new vchar[ boneNameLength + 1 ];
                fread ( boneName, 1, sizeof(vchar) * boneNameLength, inputFile );
                boneName[ boneNameLength ] = '\0';
                
                // Initialize the bone to hold the keyframe matrices.
                Matrix* matrix = new Matrix[ keyframeCount ];
                
                // Get the matrices for each keyframe
                for ( int keyframeIndex = 0; keyframeIndex < keyframeCount; keyframeIndex++ )
                {
                    // Read the matrix.
                    VGFMatrix matrixValues;
                    fread ( &matrixValues, 1, sizeof(VGFMatrix), inputFile );
                    
                    // Store the matrix.
                    matrix[ keyframeIndex ] = new Array< float > ( 16, matrixValues.val );
                }

                // Store the bone.
                Bone bone;
                bone.name = boneName;
                bone.keyframeCount = keyframeCount;
                bone.matrix = matrix;
                bones->Push ( bone );
            }
            
            // Store the armature.
            mesh->AddController ( new ArmatureController ( mesh, bones, actions ) );
        }
    }
    
    Vector VGFLoader::GetVector ()
    {
        VGFVector tmp;
        
        fread ( tmp.val, 1, sizeof(VGFVector), inputFile );
        return Vector ( tmp.val[ 0 ], tmp.val[ 1 ], tmp.val[ 2 ] );
    }

}
