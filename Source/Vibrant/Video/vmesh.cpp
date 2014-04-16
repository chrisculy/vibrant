/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmesh.cpp
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

#include "vmesh.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Mesh::Mesh ()
    {
        this->type = Mesh::TRIANGLE;
        this->vertices = null;
        this->indices = null;
    }
    
    Mesh::Mesh ( VertexBufferPtr vertices, IndexBufferPtr indices )
    {
        this->type = Mesh::TRIANGLE;
        this->vertices = vertices;
        this->indices = indices;
    }
    
    Mesh::~Mesh ()
    {
        /* stub function */
    }
    
    VertexBufferPtr Mesh::GetVertices () const
    {
        return this->vertices;
    }
    
    IndexBufferPtr Mesh::GetIndices () const
    {
        return this->indices;
    }
    
    const Mesh::MeshType& Mesh::GetMeshType () const
    {
        return this->type;
    }
    
    void Mesh::SetVertices ( VertexBufferPtr vertices )
    {
        this->vertices = vertices;
    }
    
    void Mesh::SetIndices ( IndexBufferPtr indices )
    {
        this->indices = indices;
    }
    
    void Mesh::SetMeshType ( Mesh::MeshType type )
    {
        this->type = type;
    }
    
    const RTTI* Mesh::GetType () const
    {
        return Mesh::GetRTTI ();
    }
    
    RTTI* Mesh::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            baseTypes.Push ( Node::GetRTTI () );
            baseTypes.Push ( SceneNode::GetRTTI () );
            type = new RTTI ( "Mesh", baseTypes );
        }
        return type;
    }
    
    const int Mesh::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Mesh::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        
        // Write out the basic mesh info.
        writer->WriteProperty ( "type", this->type );
        
        // Write out the SceneNode part of this object.
        writer->BeginBase ();
        SceneNode::Write ( writer );
        writer->EndBase ();
        
        // Write out the vertices and indices.
        writer->WriteChild(vertices);
        writer->WriteChild(indices);
        
        writer->EndObject ();
    }
    
    void Mesh::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        
        // Read in the basic mesh info.
        unsigned short meshType = 0;
        reader->ReadProperty ( "type", &meshType );
        this->type = (MeshType) meshType;
        
        // Read in the SceneNode part of this object.
        reader->BeginBase ();
        SceneNode::Read ( reader );
        reader->EndBase ();
        
        // Read in the vertices and indices.
        reader->ReadChild ( vertices);
        reader->ReadChild ( indices );
        
        reader->EndObject ();
    }
    
    void Mesh::UpdateDown ( long time )
    {
        SceneNode::UpdateDown ( time );
    }
    
    void Mesh::UpdateUp ()
    {
        SceneNode::UpdateUp ();
    }
    
    void Mesh::UpdateNormals ()
    {
        /* stub function */
    }

}
