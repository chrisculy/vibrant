/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnode.cpp
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
#include "vexception.h"
#include "vnode.h"
#include "vreader.h"
#include "vsystem.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Node::Node ()
    {
        parent = null;
        children.Clear ();
    }
    
    Node::Node ( Node *parent )
    {
        parent = null;
        children.Clear ();
        parent->AddChild ( this );
    }
    
    Node::~Node ()
    {
        children.Clear ();
    }
    
    bool Node::HasParent () const
    {
        return ( parent != null );
    }
    
    bool Node::HasChildren () const
    {
        return ( children.Size () > 0 );
    }
    
    int Node::ChildCount () const
    {
        return children.Size ();
    }
    
    void Node::AddChild ( Node* newChild )
    {
        // Make sure newChild is not null
        if ( newChild == null )
        {
            throw new NullPointerException ( "Node::AddChild - The child to be added was null." );
        }

        // If the new child already has a parent, then
        // remove it from its parent's children
        if ( newChild->HasParent () )
        {
            Node* oldParent = newChild->parent;
            oldParent->RemoveChild ( newChild );
        }

        newChild->parent = this;
        
        // Note that if this child was already added to
        // this object's children, it would have been removed
        // in the above code; thus, there are never duplicates
        // within an object's list of children
        children.Push ( newChild );
    }
    
    bool Node::RemoveChild ( Node* child )
    {
        // Make sure child is not null
        if ( child == null )
        {
            throw new NullPointerException ( "Node::RemoveChild - The child to be removed was null." );
        }

        for ( int i = 0; i < this->children.Size (); i++ )
        {
            if ( this->children[ i ] == child )
            {
                children.Remove ( i );
                return true;
            }
        }
        
        // Child was not found
        return false;
    }
    
    void Node::RemoveChildAt ( int index )
    {
        // Check bounds.
        if ( index < 0 || index > ( ChildCount () - 1 ) )
        {
            throw new IndexOutOfBoundsException ( "Node::RemoveChildAt - Child index out of bounds." );
        }
        
        // Remove child.
        children.Remove ( index );
    }
    
    Node* Node::GetChild ( int index ) const
    {
        // Check bounds.
        if ( index < 0 || index > ( ChildCount () - 1 ) )
        {
            throw new IndexOutOfBoundsException ( "Node::GetChild - Child index out of bounds." );
        }
        
        return children[ index ];
    }
    
    Node* Node::GetParent () const
    {
        return this->parent;
    }
    
    const int Node::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Node::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        writer->WriteProperty ( "children", this->ChildCount () );
        
        // Write out the Object part of this object.
        writer->BeginBase ();
        Object::Write ( writer );
        writer->EndBase ();
        
        if ( this->HasChildren () )
        {
            // Write out all children.
            for ( int i = 0; i < this->ChildCount (); i++ )
            {
                writer->WriteChild ( this->GetChild ( i ) );
            }
        }
        writer->EndObject ();
    }
    
    void Node::Read ( Reader* reader )
    {
        int childCount = 0;
        reader->BeginObject ( this->GetType ()->GetName () );
        reader->ReadProperty ( "children", &childCount );
        
        // Read in the Object part of this object.
        reader->BeginBase ();
        Object::Read ( reader );
        reader->EndBase ();
        
        if ( this->HasChildren () )
        {
            // Read in all the children.
            Node* child = null;
            for ( int i = 0; i < this->ChildCount (); i++ )
            {
                reader->ReadChild ( child );
                this->AddChild ( child );
            }
        }
        reader->EndObject ();
    }
    
    const RTTI* Node::GetType () const
    {
        return Node::GetRTTI ();
    }
    
    RTTI* Node::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            type = new RTTI ( "Node", baseTypes );
        }
        return type;
    }

}
