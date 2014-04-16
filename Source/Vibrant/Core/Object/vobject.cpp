/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vobject.cpp
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
#include "vhashtable.h"
#include "vlog.h"
#include "vobject.h"
#include "vreader.h"
#include "vstring.h"
#include "vsystem.h"
#include "vwriter.h"

namespace Vibrant
{
    
    // Initialize static members.
    Hashtable< unsigned int, Object* >* Object::liveObjects = null;
    unsigned int Object::nextID = 0;
    
    Object::~Object ()
    {
        // Remove the object from the liveObjects map.
        liveObjects->Remove ( id );
    }
    
    void Object::SetName ( const String name )
    {
        /* stub function */
    }
    
    String Object::GetName () const
    {
        return name;
    }
    
    unsigned int Object::GetID () const
    {
        return id;
    }
    
    unsigned int Object::GetNextID ()
    {
        return Object::nextID++;
    }
    
    Pointer< Object > Object::GetObject ( String name ) const
    {
        /* stub function */
        return null;
    }
    
    Pointer< Object > Object::GetObject ( unsigned int id ) const
    {
        /* stub function */
        return null;
    }
    
    Pointer< Object >* Object::GetAllObjects ( String name ) const
    {
        /* stub function */
        return null;
    }
    
    const RTTI* Object::GetType () const
    {
        return Object::GetRTTI ();
    }
    
    RTTI* Object::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Clear ();
            type = new RTTI ( "Object", baseTypes );
        }
        return type;
    }
    
    bool Object::IsExactly ( const RTTI* type ) const
    {
        return this->GetType ()->IsExactly ( type );
    }
    
    bool Object::IsDerived ( const RTTI* type ) const
    {
        return this->GetType ()->IsDerived ( type );
    }
    
    bool Object::IsExactlyTypeOf ( const Object* obj ) const
    {
        return this->GetType ()->IsExactly ( obj->GetType () );
    }
    
    bool Object::IsDerivedTypeOf ( const Object* obj ) const
    {
        /* stub function */
        return this->GetType ()->IsDerived ( obj->GetType () );
    }
    
    void Object::AddController ( Controller* controller )
    {
        this->controllers.Push ( controller );
    }
    
    void Object::RemoveController ( Controller* controller )
    {
        for ( int i = 0; i < this->controllers.Size (); i++ )
        {
            if ( this->controllers[ i ] == controller )
            {
                this->controllers.Remove ( i );
                return;
            }
        }
    }
    
    void Object::RemoveAllControllers ()
    {
        this->controllers.Clear ();
    }
    
    Pointer< Controller > Object::GetController ( int index ) const
    {
        return this->controllers.At ( index );
    }
    
    int Object::ControllerCount () const
    {
        return this->controllers.Size ();
    }
    
    bool Object::UpdateControllers ( long time )
    {
        for ( int i = 0; i < this->controllers.Size (); i++ )
        {
            this->controllers[ i ]->Update ( time );
        }
        return false;
    }
    
    const int Object::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Object::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        writer->WriteProperty ( "name", this->name );
        writer->WriteProperty ( "id", this->id );
        writer->WriteProperty ( "references", this->ReferenceCount () );
        writer->WriteProperty ( "controllers", this->ControllerCount () );
        
        // Write out the controllers.
        for ( int controllerIndex = 0; controllerIndex < this->ControllerCount (); controllerIndex++ )
        {
            writer->WriteChild ( this->GetController ( controllerIndex ) );
        }
        writer->EndObject ();
    }
    
    void Object::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        reader->ReadProperty ( "name", &this->name );
        reader->ReadProperty ( "id", &this->id );
        int referenceCount = 0;
        reader->ReadProperty ( "references", &referenceCount );
        // Set the number of references.
        if ( this->ReferenceCount () < referenceCount )
        {
            while ( this->ReferenceCount () < referenceCount )
            {
                this->AddReference ();
            }
        }
        else if ( this->ReferenceCount () > referenceCount )
        {
            while ( this->ReferenceCount () > referenceCount )
            {
                this->RemoveReference ();
            }
        }

        // Read in the controllers.
        int ControllerCount = 0;
        reader->ReadProperty ( "controllers", &ControllerCount );
        Controller* controller = null;
        for ( int controllerIndex = 0; controllerIndex < this->ControllerCount (); controllerIndex++ )
        {
            reader->ReadChild ( controller );
            this->AddController ( controller );
        }
        reader->EndObject ();
    }
    
    Pointer< Object > Object::Copy ( bool createNewName ) const
    {
        /* stub function */
        return null;
    }
    
    Object::Object ()
    {
        // Make sure the liveObjects table exists.
        if ( Object::liveObjects == null )
        {
            Object::liveObjects = new Hashtable< unsigned int, Object* > ();
        }
        // Find an unused ID and then put the object in the table.
        id = Object::GetNextID ();
        while ( liveObjects->Contains ( id ) )
        {
            id = Object::GetNextID ();
        }
        
        Object::liveObjects->Put ( this->id, this );
    }

}
