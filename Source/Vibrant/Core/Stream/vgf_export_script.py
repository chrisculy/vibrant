##
 # =======================================
 # =============== Vibrant ===============
 # =======================================
 #
 # 
 # File: vgf_export_script.py
 # 
 # 
 # --  Copyright (c) 2007-2008 Alterr.  --
 # ---------------------------------------
 # 
 # Last changed:
 # $Revision$
 # $Author$
 # $Date$
## 


#!BPY

"""
Name: 'VGF Exporter'
Blender: 244
Group: 'Export'
Tooltip: 'Exports to a VGF (Vibrant Graphics Format) file, used in the Vibrant game engine.'
"""

import Blender
from Blender import Object, Mesh, Material, Armature
import struct

##### Reasonable Number of Frames in One Model - GLOBAL VARIABLE
reasonableNumberOfFrames = 450

#vars used to initialize global vars
scene = Blender.Scene.GetCurrent ()
renderContext = scene.getRenderingContext ()

#global vars
globalEndFrame = renderContext.endFrame ()
fps = renderContext.framesPerSec ()

def write ( filename ) :
    global globalEndFrame
    
    #open file for binary output
    outputFile = file ( filename, "wb" )
    #debugging purpose
    #tmpFile = open ( "C:/Documents and Settings/Admin/My Documents/Fel'Nara/Programming/vgftext.txt", "w" )
    
    #get all the mesh objects
    meshes = [ob for ob in scene.objects if ob.type == 'Mesh']
    #get all armatures
    armatures = [ob for ob in scene.objects if ob.type == "Armature" ]
    
    #create variables to fill the file header
    numMeshes = len ( meshes )
    materials = Material.Get ()
    images = Blender.Image.Get ()
    #armatures = Armature.Get ()
    
    tmp = [ 0 ] * 5
    tmp [ 0 ] = 0x9999
    tmp [ 1 ] = len ( materials )
    tmp [ 2 ] = fps
    tmp [ 3 ] = len ( images )
    tmp [ 4 ] = len ( armatures )
    #write out the File Header (see VGF File Format Description for details)
    data = struct.pack ( "5I", tmp [ 0 ], tmp [ 1 ], tmp [ 2 ], tmp [ 3 ], tmp [ 4 ] )
    outputFile.write ( data )
    #tmpFile.write ( str ( tmp [ 0 ] ) + " " + str ( tmp [ 1 ] ) + " " + str ( tmp [ 2 ] ) + " " + str ( tmp [ 3 ] ) + " " +
    #                str ( tmp [ 4 ] ) + "\n" )
    
    #write out the UV Image Data (see VGF File Format Description for details)
    numImages = len ( images )
    i = 0
    tmpStr = [ 0 ] * 2
    while ( i < numImages ) :
        tmpStr [ 0 ] = images [ i ].getName ()
        tmpStr [ 1 ] = images [ i ].getFilename ()
        lenName = len ( tmpStr [ 0 ] )
        lenFilename = len ( tmpStr [ 1 ] )
        fmt1 = "%ds" % lenName
        fmt2 = "%ds" % lenFilename
        outputFile.write ( struct.pack ( "2I",  lenName, lenFilename ) )
        outputFile.write ( struct.pack ( fmt1, tmpStr [ 0 ] ) )
        outputFile.write ( struct.pack ( fmt2, tmpStr [ 1 ] ) )
        #tmpFile.write ( str ( lenName ) + " " + str ( lenFilename ) + " " )
        #tmpFile.write ( str ( tmpStr [ 0 ] ) + " " )
        #tmpFile.write ( str ( tmpStr [ 1 ] ) + "\n" )
        i += 1
    
    #write out the Mesh Data (see VGF File Format Description for details)
    x = 0
    while ( x < numMeshes ) :
        #load data into variables
        currentMesh = meshes [ x ].getData ()
        meshFaces = currentMesh.faces
        numFaces = len ( meshFaces )
        numVerts = len ( currentMesh.verts )
        
        #link current mesh to its proper Blender object (and vice versa)
        objects = Blender.Object.Get ()
        currentObj = 0
        for obj in objects:
            if obj.getData ( 1 ) == currentMesh.name:
                obj.link ( currentMesh )
                currentObj = obj
                break
        
        #calculate the number of indices
        i = 0
        numIndices = 0
        while ( i < numFaces ) :
            numIndices += len ( meshFaces [ i ].v )
            i += 1            

        tmp [ 0 ] = currentMesh.hasFaceUV ()
        tmp [ 1 ] = numVerts
        tmp [ 2 ] = numIndices
        tmp [ 3 ] = numFaces
        data = struct.pack ( "4I", tmp [ 0 ], tmp [ 1 ], tmp [ 2 ], tmp [ 3 ] )
        outputFile.write ( data )
        #tmpFile.write ( "HasFaceUV; # of Vertices; # of Indices; # of Faces\n" )
        #tmpFile.write ( str ( tmp [ 0 ] ) + "; " + str ( tmp [ 1 ] ) + "; " + str ( tmp [ 2 ] ) + "; " + str ( tmp [ 3 ] ) + "\n" )
        
        #write out the Vertex Data (see VGF File Format Description for details)
        i = 0
        tmpFloat = [ 0 ] * 6
        #tmpFile.write ( "\nVertex Data\n" )
        while ( i < numVerts ) :
            #write out the vertex coordinates and normals (swap y and z because Blender swaps those axes)
            tmpFloat [ 0 ] = currentMesh.verts [ i ].co.x
            tmpFloat [ 1 ] = currentMesh.verts [ i ].co.z
            tmpFloat [ 2 ] = currentMesh.verts [ i ].co.y
            data = struct.pack ( "3f", tmpFloat [ 0 ], tmpFloat [ 1 ], tmpFloat [ 2 ] )
            outputFile.write ( data )
            #tmpFile.write ( str ( tmpFloat [ 0 ] ) + " " + str ( tmpFloat [ 1 ] ) + " " + str ( tmpFloat [ 2 ] ) + "; " )
            tmpFloat [ 0 ] = currentMesh.verts [ i ].no.x
            tmpFloat [ 1 ] = currentMesh.verts [ i ].no.z
            tmpFloat [ 2 ] = currentMesh.verts [ i ].no.y
            data = struct.pack ( "3f", tmpFloat [ 0 ], tmpFloat [ 1 ], tmpFloat [ 2 ] )
            outputFile.write ( data )
            #tmpFile.write ( str ( tmpFloat [ 0 ] ) + " " + str ( tmpFloat [ 1 ] ) + " " + str ( tmpFloat [ 2 ] ) + "\n" )
            i += 1
        
        #write out the Faces Data (see VGF File Format Description for details)
        vertIndex = [ 0, 0, 0 ]
        i = 0
        #tmpFile.write ( "\nFaces Data\n" )
        while ( i < numFaces ) :
            uvCoords = meshFaces [ i ].uv
            tmpIdx = 0
            
            #get the UV image index
            j = 0
            imageIndex = 0
            while ( j < numImages ) :
                if meshFaces [ i ].image != None:
                    if  meshFaces [ i ].image.getName () == images [ j ].getName () :
                        imageIndex = j
                j += 1
            #write out the number of vertices in the face
            #and the UV image index
            numFaceVerts = len ( meshFaces [ i ].v )
            data = struct.pack ( "2I", numFaceVerts, imageIndex )
            outputFile.write ( data )
            #tmpFile.write ( str ( numFaceVerts ) + " " + str ( imageIndex ) + "\n" )
            
            j = 0
            #go through the face's vertices
            while ( j < numFaceVerts ) :
                k = 0
                vertIndex = 0
                #go through the faces and determine when the vertices are equal
                #find this vertex's index in the mesh
                while ( k < len ( currentMesh.verts ) ) :
                    if meshFaces [ i ].v [ j ] == currentMesh.verts [ k ] :
                        vertIndex = k
                    k += 1
                #write out the vertex's index
                outputFile.write ( struct.pack ( "I", vertIndex ) )
                #tmpFile.write ( str ( vertIndex ) + "\n" )
                #write out the UV coordinates (if the face has UV coordinates)
                if ( currentMesh.hasFaceUV () ) :
                    data = struct.pack ( "2f", uvCoords [ j ] [ 0 ], uvCoords [ j ] [ 1 ] )
                    outputFile.write ( data )
                    #tmpFile.write ( str ( uvCoords [ j ] [ 0 ] ) + " " + str ( uvCoords [ j ] [ 1 ] ) + "\n" )
                #write out the number of bones that influences this vertex
                vertexInfluences = currentMesh.getVertexInfluences ( vertIndex )
                numVertexInfluences = len ( vertexInfluences )
                outputFile.write ( struct.pack ( "I", numVertexInfluences ) ) 
                #tmpFile.write ( str ( numVertexInfluences ) + "\n" )
                #write out the name and weight of all bones that influences the vertex
                boneIndex = 0
                while ( boneIndex < numVertexInfluences ) :
                    boneName = vertexInfluences [ boneIndex ] [ 0 ]
                    lenBoneName = len ( boneName )
                    fmtBoneName = "%ds" % lenBoneName
                    outputFile.write ( struct.pack ( "I", lenBoneName ) )
                    outputFile.write ( struct.pack ( fmtBoneName, boneName ) )
                    outputFile.write ( struct.pack ( "f", vertexInfluences [ boneIndex ] [ 1 ] ) )
                    #tmpFile.write ( str ( lenBoneName ) + " " + str ( boneName ) + " " + str ( vertexInfluences [ boneIndex ] [ 1 ] ) + "\n" )
                    boneIndex += 1
                j += 1    
            i += 1
        #End Faces Data
        
        #re-initialize tmpFloat
        tmpFloat = [ 0 ] * 16
        
        #write out the Armature Data (see VGF File Format Description for details)
        Blender.Set ( 'curframe', 1 )
        
        #tmpFile.write ( "\nArmature Data:\n" )
        #go through each armature and write out the proper values
        for armature in armatures:
            arm = armature.getData ()        
            
            #link current armature to its proper Blender object
            #objects = Blender.Object.Get ()
            #for obj in objects:
            #    if obj.getData ( 1 ) == arm.name:
            #        tmpArmature = obj
            #        tmpArmature.link ( arm )
            #        break
            
            #get the action strips for the object
            actionStrips = currentObj.actionStrips
            
            #tmpFile.write ( "Number of bones: " + str ( len ( arm.bones.values () ) ) + "\n" )
            #tmpFile.write ( "Number of actions: " + str ( len ( actionStrips ) ) + "\n" )
            
            #write out the number of bones and the number of action strips
            outputFile.write ( struct.pack ( "2I", len ( arm.bones.values() ), len ( actionStrips ) ) )
            
            #write out the Action Strip Data (see VGF File Format Description for details)
            for actionStrip in actionStrips:
                keyframes = actionStrip.action.getFrameNumbers ()
                numKeyframes = len ( keyframes )
                data = struct.pack ( "3I", actionStrip.actionStart, actionStrip.actionEnd, numKeyframes )
                outputFile.write ( data )
                #tmpFile.write ( "Start: " + str ( actionStrip.actionStart ) +
                                "; End: " + str ( actionStrip.actionEnd ) +
                                "; # of Keyframes: " + str ( numKeyframes ) + "\n" )
                
                #write out the keyframes (frame numbers)
                keyframeIndex = 0
                while ( keyframeIndex < numKeyframes ):
                    data = struct.pack ( "I", keyframes [ keyframeIndex ] )
                    outputFile.write ( data )
                    keyframeIndex += 1
                #tmpFile.write ( str ( keyframes ) + "\n" )
                
                #write out the bone data for each keyframe
                for bone in arm.bones.values ():
                    #write out the length of the bone's name and the bone's name
                    lengthBoneName = len ( bone.name )
                    formatBoneName = "%ds" % lengthBoneName
                    outputFile.write ( struct.pack ( "I", lengthBoneName ) )
                    outputFile.write ( struct.pack ( formatBoneName, bone.name ) )
                    #tmpFile.write ( str ( lengthBoneName ) + " " )
                    #tmpFile.write ( str ( bone.name ) + "\n" )
                    
                    for keyframe in keyframes:
                        Blender.Set ( 'curframe', keyframe )
                        
                        #swap Y and Z
                        tmpBoneMatrix = bone.matrix['ARMATURESPACE']
                        boneMatrix = Blender.Mathutils.CopyMat ( tmpBoneMatrix )
                        boneMatrix = boneMatrix.resize4x4 ()
                        tmpFloat [ 0 ] = boneMatrix [ 0 ][ 0 ]
                        tmpFloat [ 1 ] = boneMatrix [ 0 ][ 2 ]
                        tmpFloat [ 2 ] = boneMatrix [ 0 ][ 1 ]
                        tmpFloat [ 3 ] = boneMatrix [ 0 ][ 3 ]
                        
                        tmpFloat [ 4 ] = boneMatrix [ 1 ][ 0 ]
                        tmpFloat [ 5 ] = boneMatrix [ 1 ][ 2 ]
                        tmpFloat [ 6 ] = boneMatrix [ 1 ][ 1 ]
                        tmpFloat [ 7 ] = boneMatrix [ 1 ][ 3 ]
                        
                        tmpFloat [ 8 ] = boneMatrix [ 2 ][ 0 ]
                        tmpFloat [ 9 ] = boneMatrix [ 2 ][ 2 ]
                        tmpFloat [ 10 ] = boneMatrix [ 2 ][ 1 ]
                        tmpFloat [ 11 ] = boneMatrix [ 2 ][ 3 ]
                        
                        tmpFloat [ 12 ] = boneMatrix [ 3 ][ 0 ]
                        tmpFloat [ 13 ] = boneMatrix [ 3 ][ 2 ]
                        tmpFloat [ 14 ] = boneMatrix [ 3 ][ 1 ]
                        tmpFloat [ 15 ] = boneMatrix [ 3 ][ 3 ]
                        data = struct.pack ( "16f", tmpFloat [ 0 ], tmpFloat [ 1 ], tmpFloat [ 2 ], tmpFloat [ 3 ],
                                                tmpFloat [ 4 ], tmpFloat [ 5 ], tmpFloat [ 6 ], tmpFloat [ 7 ],
                                                tmpFloat [ 8 ], tmpFloat [ 9 ], tmpFloat [ 10 ], tmpFloat [ 11 ],
                                                tmpFloat [ 12 ], tmpFloat [ 13 ], tmpFloat [ 14 ], tmpFloat [ 15 ] )
                        outputFile.write ( data )
                        #tmpFile.write ( str ( tmpFloat [ 0 ] ) + "  " + str ( tmpFloat [ 1 ] ) + "  " + str ( tmpFloat [ 2 ] ) + "  " + str ( tmpFloat [ 3 ] ) + "  " +
                        #                str ( tmpFloat [ 4 ] ) + "  " + str ( tmpFloat [ 5 ] ) + "  " + str ( tmpFloat [ 6 ] ) + "  " + str ( tmpFloat [ 7 ] ) + "  " +
                        #                str ( tmpFloat [ 8 ] ) + "  " + str ( tmpFloat [ 9 ] ) + "  " + str ( tmpFloat [ 10 ] ) + "  " + str ( tmpFloat [ 11 ] ) + "  " +
                        #                str ( tmpFloat [ 12 ] ) + "  " + str ( tmpFloat [ 13 ] ) + "  " + str ( tmpFloat [ 14 ] ) + "  " + str ( tmpFloat [ 15 ] ) + "\n" )
                    Blender.Set ( 'curframe', 1 )
            #End Action Strip Data
        #End Armature Data
        x += 1    #next object
    #End Mesh Data
    #write out the file (for sure)
    outputFile.flush ()
    #tmpFile.flush ()
#End "write ( filename )" function

#Graphical User Interface Code --- START

from Blender import Draw, BGL

def event ( event, value ) :
    Draw.Redraw ( 1 )

def buttonEvent ( event ) :
    global globalEndFrame, reasonableNumberOfFrames
    if event == 1 :
        i = 0
        Blender.Window.FileSelector ( write, "Export" )
    elif event == 6 :
        Draw.Exit ()
    else :
        Draw.Redraw ( 1 )

def gui () :
    export = Draw.PushButton ( "Export", 1, 250, 10, 70, 20, "Exports the model to a .vgf file." )
    exit = Draw.PushButton ( "Exit", 6, 330, 10, 50, 20, "Exit the script." )

#register callback functions for the gui
Blender.Draw.Register ( gui, event, buttonEvent )

#Graphical User Interface Code --- END