/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvertex.cpp
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

#include "varray.h"
#include "vcolor.h"
#include "vhashtable.h"
#include "vexception.h"
#include "vreader.h"
#include "vsystem.h"
#include "vtexturecoord.h"
#include "vvector.h"
#include "vvertex.h"
#include "vwriter.h"

namespace Vibrant
{
    
    VertexInfluence::~VertexInfluence ()
    {
        /* stub function */
    }
    
    const int VertexInfluence::GetDiskSize () const
    {
        static int staticSize = sizeof(float);
        return staticSize + sizeof( boneName.CString () );
    }
    
    void VertexInfluence::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "VertexInfluence" );
        writer->WriteProperty ( "bone-name", this->boneName );
        writer->WriteProperty ( "bone-weight", this->boneWeight );
        writer->EndObject ();
    }
    
    void VertexInfluence::Read ( Reader* reader )
    {
        reader->BeginObject ( "VertexInfluence" );
        reader->ReadProperty ( "bone-name", &this->boneName );
        reader->ReadProperty ( "bone-weight", &this->boneWeight );
        reader->EndObject ();
    }
    
    Vertex::Vertex ( Vector position, Vector normal, TextureCoord textureCoord, Color color )
    {
        this->position = position;
        this->normal = normal;
        this->SetTextureCoord ( textureCoord );
        this->color = color;
        this->vertexInfluences = new Array< VertexInfluence > ();
    }
    
    Vertex::Vertex ( Vector position, Vector normal, Hashtable< int, TextureCoord > textureCoords, Color color )
    {
        this->position = position;
        this->normal = normal;
        this->SetTextureCoords ( textureCoords );
        this->color = color;
        this->vertexInfluences = new Array< VertexInfluence > ();
    }
    
    Vertex::Vertex ( const Vertex& vertex )
    {
        this->position = vertex.GetPosition ();
        this->normal = vertex.GetNormal ();
        this->SetTextureCoords ( vertex.GetTextureCoords () );
        this->color = vertex.GetColor ();
        *( this->vertexInfluences ) = *( vertex.GetVertexInfluences () );
    }
    
    Vertex::~Vertex ()
    {
        if ( this->vertexInfluences != null )
        {
            delete this->vertexInfluences;
            this->vertexInfluences = null;
        }
    }
    
    const Vector& Vertex::GetPosition () const
    {
        return this->position;
    }
    
    const Vector& Vertex::GetNormal () const
    {
        return this->normal;
    }
    
    const TextureCoord& Vertex::GetTextureCoord ( int uvImageID ) const
    {
        // Make sure there are texture coordinates.
        if ( this->textureCoords.IsEmpty () )
        {
            throw EmptyContainerException ( "TextureCoord::GetTextureCoord - No texture coordinates exist." );
        }
        
        // Get the texture coordinate and return
        // it, or return the default ones (the first ones).
        if ( this->textureCoords.Contains ( uvImageID ) )
        {
            return this->textureCoords.Get ( uvImageID );
        }
        else
        {
            int firstUVImageID = this->textureCoords.StartIterator ().GetKey ();
            return this->textureCoords.Get ( firstUVImageID );
        }
    }
    
    const Hashtable< int, TextureCoord >& Vertex::GetTextureCoords () const
    {
        return this->textureCoords;
    }
    
    const Color& Vertex::GetColor () const
    {
        return this->color;
    }
    
    void Vertex::SetPosition ( const Vector& position )
    {
        this->position = position;
    }
    
    void Vertex::SetNormal ( const Vector& normal )
    {
        this->normal = normal;
    }
    
    void Vertex::SetTextureCoord ( const TextureCoord& textureCoord )
    {
        if ( this->textureCoords.Contains ( textureCoord.GetUVImageID () ) )
        {
            this->textureCoords.Get ( textureCoord.GetUVImageID () ) = textureCoord;
        }
        else
        {
            this->textureCoords.Put ( textureCoord.GetUVImageID (), textureCoord );
        }
    }
    
    void Vertex::SetTextureCoords ( const Hashtable< int, TextureCoord >& textureCoords )
    {
        this->textureCoords = textureCoords;
    }
    
    void Vertex::SetColor ( const Color& color )
    {
        this->color = color;
    }
    
    Array< VertexInfluence >* Vertex::GetVertexInfluences () const
    {
        return this->vertexInfluences;
    }
    
    Vertex::VertexData Vertex::GetVertexData ()
    {
        VertexData data;
        memset ( &data, 0, sizeof(VertexData) );
        
        // Copy in the position, normal, and color.
        data.x = position.GetX ();
        data.y = position.GetY ();
        data.z = position.GetZ ();
        data.nx = normal.GetX ();
        data.ny = normal.GetY ();
        data.nz = normal.GetZ ();
        data.r = color.GetRed ();
        data.g = color.GetGreen ();
        data.b = color.GetBlue ();
        data.a = color.GetAlpha ();
        
        // Copy in the texture coordinates.
        if ( textureCoords.Size () > 0 )
        {
            Hashtable< int, TextureCoord >::Iterator< > iter = textureCoords.StartIterator ();
            data.s0 = iter.GetValue ().GetS ();
            data.t0 = iter.GetValue ().GetT ();
            iter.Next ();
            
            if ( iter != textureCoords.EndIterator () )
            {
                data.s1 = iter.GetValue ().GetS ();
                data.t1 = iter.GetValue ().GetT ();
                iter.Next ();
                
                if ( iter != textureCoords.EndIterator () )
                {
                    data.s2 = iter.GetValue ().GetS ();
                    data.t2 = iter.GetValue ().GetT ();
                }
            }
        }
        
        return data;
    }
    
    const int Vertex::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Vertex::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        writer->WriteProperty ( "texture-coordinates", this->TextureCoordCount () );
        writer->WriteProperty ( "vertex-influences", this->vertexInfluences->Size () );
        
        // Write out the Object part of this object.
        writer->BeginBase ();
        Object::Write ( writer );
        writer->EndBase ();
        
        // Write out vertex info.
        writer->WriteChild ( &this->position );
        writer->WriteChild ( &this->normal );
        writer->WriteChild ( &this->color );
        
        // Write out the vertex's texture coordinates.
        Hashtable< int, TextureCoord >::Iterator< > iter = this->GetTextureCoords ().StartIterator ();
        TextureCoord textureCoord;
        while ( iter != this->GetTextureCoords ().EndIterator () )
        {
            textureCoord = iter.GetValue ();
            writer->WriteChild ( &textureCoord );
            iter.Next ();
        }

        // Write out the vertex's bone influences
        Array< VertexInfluence >* influences = this->GetVertexInfluences ();
        for ( int i = 0; i < influences->Size (); i++ )
        {
            writer->WriteChild ( &( influences->At ( i ) ) );
        }
        writer->EndObject ();
    }
    
    void Vertex::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        int textureCoordCount = 0;
        int vertexInfluenceCount = 0;
        reader->ReadProperty ( "texture-coordinates", &textureCoordCount );
        reader->ReadProperty ( "vertex-influences", &vertexInfluenceCount );
        
        // Read in the Object part of this object.
        reader->BeginBase ();
        Object::Read ( reader );
        reader->EndBase ();
        
        // Read in vertex info.
        reader->ReadChild ( &this->position );
        reader->ReadChild ( &this->normal );
        reader->ReadChild ( &this->color );
        
        // Read in the vertex's texture coordinates.
        TextureCoord textureCoord;
        for ( int i = 0; i < textureCoordCount; i++ )
        {
            reader->ReadChild ( &textureCoord );
            this->SetTextureCoord ( textureCoord );
        }

        // Read in the vertex's bone influences
        Array< VertexInfluence > influences ( vertexInfluenceCount );
        for ( int i = 0; i < influences.Size (); i++ )
        {
            reader->ReadChild ( &( influences.At ( i ) ) );
        }
        *( this->vertexInfluences ) = influences;
        reader->EndObject ();
    }
    
    const RTTI* Vertex::GetType () const
    {
        return Vertex::GetRTTI ();
    }
    
    RTTI* Vertex::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            type = new RTTI ( "Vertex", baseTypes );
        }
        return type;
    }
    
    int Vertex::TextureCoordCount () const
    {
        return this->textureCoords.Size ();
    }
    
    Vertex::VertexDataSerializer* Vertex::VertexDataSerializer::MakeReadable ( VertexData* data )
    {
        static VertexDataSerializer readable;
        
        readable.readData = data;
        return &readable;
    }
    
    Vertex::VertexDataSerializer* Vertex::VertexDataSerializer::MakeWritable ( const VertexData* data )
    {
        static VertexDataSerializer writable;
        
        writable.writeData = data;
        return &writable;
    }
    
    const int Vertex::VertexDataSerializer::GetDiskSize () const
    {
        return DATA_SIZE;
    }
    
    void Vertex::VertexDataSerializer::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "vertexdata" );
        
        // Write out all the vertex data's members.
        writer->WriteProperty ( "x", writeData->x );
        writer->WriteProperty ( "y", writeData->y );
        writer->WriteProperty ( "z", writeData->z );
        writer->WriteProperty ( "nx", writeData->nx );
        writer->WriteProperty ( "ny", writeData->ny );
        writer->WriteProperty ( "nz", writeData->nz );
        writer->WriteProperty ( "r", writeData->r );
        writer->WriteProperty ( "g", writeData->g );
        writer->WriteProperty ( "b", writeData->b );
        writer->WriteProperty ( "a", writeData->a );
        writer->WriteProperty ( "s0", writeData->s0 );
        writer->WriteProperty ( "t0", writeData->t0 );
        writer->WriteProperty ( "s1", writeData->s1 );
        writer->WriteProperty ( "t1", writeData->t1 );
        writer->WriteProperty ( "s2", writeData->s2 );
        writer->WriteProperty ( "t2", writeData->t2 );
        
        writer->EndObject ();
    }
    
    void Vertex::VertexDataSerializer::Read ( Reader* reader )
    {
        reader->BeginObject ( "vertexdata" );
        
        // Read in all the vertex data's members.
        reader->ReadProperty ( "x", &readData->x );
        reader->ReadProperty ( "y", &readData->y );
        reader->ReadProperty ( "z", &readData->z );
        reader->ReadProperty ( "nx", &readData->nx );
        reader->ReadProperty ( "ny", &readData->ny );
        reader->ReadProperty ( "nz", &readData->nz );
        reader->ReadProperty ( "r", &readData->r );
        reader->ReadProperty ( "g", &readData->g );
        reader->ReadProperty ( "b", &readData->b );
        reader->ReadProperty ( "a", &readData->a );
        reader->ReadProperty ( "s0", &readData->s0 );
        reader->ReadProperty ( "t0", &readData->t0 );
        reader->ReadProperty ( "s1", &readData->s1 );
        reader->ReadProperty ( "t1", &readData->t1 );
        reader->ReadProperty ( "s2", &readData->s2 );
        reader->ReadProperty ( "t2", &readData->t2 );
        
        reader->EndObject ();
    }
    
    Vertex::VertexDataSerializer::VertexDataSerializer ()
    {
        /* stub function */
    }

}
