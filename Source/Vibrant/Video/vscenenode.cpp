/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscenenode.cpp
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

#include "vscenenode.h"
#include "varray.h"
#include "vcontroller.h"
#include "vreader.h"
#include "vsystem.h"
#include "vwriter.h"

namespace Vibrant
{
    
    SceneNode::SceneNode ()
    {
        this->local = Transform ();
        this->world = Matrix::GetIdentityMatrix ();
        this->boundingVolume = BoundingVolume ();
        this->effects = Array< Effect* > ();
        this->lights = Array< Light* > ();
    }
    
    SceneNode::~SceneNode ()
    {
        /* stub function */
    }
    
    void SceneNode::Update ( long time )
    {
        // Update downwards.
        UpdateDown ( time );
        
        // Update upwards.
        UpdateUp ();
    }
    
    const int SceneNode::LightCount () const
    {
        return this->lights.Size ();
    }
    
    void SceneNode::AddLight ( Light* light )
    {
        if ( light == null )
        {
            throw NullPointerException ( "SceneNode::AddLight - The light to add must be non-null." );
        }
        
        this->lights.Push ( light );
    }
    
    void SceneNode::RemoveLight ( Light* light )
    {
        if ( light == null )
        {
            throw NullPointerException ( "SceneNode::RemoveLight - The light to remove must be non-null." );
        }
        
        for ( int i = 0; i < this->lights.Size (); i++ )
        {
            if ( this->lights[ i ] == light )
            {
                this->lights.Remove ( i );
            }
        }
    }
    
    void SceneNode::RemoveAllLights ()
    {
        this->lights.Clear ();
    }
    
    Light* SceneNode::GetLight ( int index ) const
    {
        if ( index < 0 || index > this->lights.Size () - 1 )
        {
            throw IndexOutOfBoundsException ( "SceneNode::GetLight - The light index is out of bounds." );
        }
        
        return this->lights[ index ];
    }
    
    const int SceneNode::EffectCount () const
    {
        return this->effects.Size ();
    }
    
    void SceneNode::AddEffect ( Effect* effect )
    {
        if ( effect == null )
        {
            throw NullPointerException ( "SceneNode::AddEffect - The effect to add must be non-null." );
        }
        
        this->effects.Push ( effect );
    }
    
    void SceneNode::RemoveEffect ( Effect* effect )
    {
        if ( effect == null )
        {
            throw NullPointerException ( "SceneNode::RemoveEffect - The effect to remove must be non-null." );
        }
        
        for ( int i = 0; i < this->effects.Size (); i++ )
        {
            if ( this->effects[ i ] == effect )
            {
                this->effects.Remove ( i );
            }
        }
    }
    
    void SceneNode::RemoveAllEffects ()
    {
        this->effects.Clear ();
    }
    
    Effect* SceneNode::GetEffect ( int index ) const
    {
        if ( index < 0 || index > this->effects.Size () - 1 )
        {
            throw IndexOutOfBoundsException ( "SceneNode::GetEffect - The effect index is out of bounds." );
        }
        
        return this->effects[ index ];
    }
    
    void SceneNode::SetFirstEffect ( int index )
    {
        if ( index < 0 || index > this->effects.Size () - 1 )
        {
            throw IndexOutOfBoundsException ( "SceneNode::SetFirstEffect - The effect index is out of bounds." );
        }
        
        this->firstEffectIndex = index;
    }
    
    const int SceneNode::GetFirstEffect ()
    {
        return this->firstEffectIndex;
    }
    
    const int SceneNode::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void SceneNode::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        writer->WriteProperty ( "effects", this->EffectCount () );
        writer->WriteProperty ( "lights", this->LightCount () );
        
        // Write out the Node part of this object.
        writer->BeginBase ();
        Node::Write ( writer );
        writer->EndBase ();
        
        // TODO: Write out the lights.

        // Write out the effects.
        for ( int effectIndex = 0; effectIndex < this->EffectCount (); effectIndex++ )
        {
            writer->WriteChild ( this->GetEffect ( effectIndex ) );
        }
        writer->EndObject ();
    }
    
    void SceneNode::Read ( Reader* reader )
    {
        int effectCount = 0;
        int lightCount = 0;
        
        reader->BeginObject ( this->GetType ()->GetName () );
        reader->ReadProperty ( "effects", &effectCount );
        reader->ReadProperty ( "lights", &lightCount );
        
        // Read in the Node part of this object.
        reader->BeginBase ();
        Node::Read ( reader );
        reader->EndBase ();
        
        // TODO: Read in the lights.

        // Read in the effects.
        Effect* effect = null;
        for ( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
        {
            reader->ReadChild ( effect );
            this->AddEffect ( effect );
        }
        reader->EndObject ();
    }
    
    const RTTI* SceneNode::GetType () const
    {
        return SceneNode::GetRTTI ();
    }
    
    RTTI* SceneNode::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            baseTypes.Push ( Node::GetRTTI () );
            type = new RTTI ( "SceneNode", baseTypes );
        }
        return type;
    }
    
    void SceneNode::UpdateDown ( long time )
    {
        // Update all of the node's controllers.
        for ( int i = 0; i < ControllerCount (); i++ )
        {
            GetController ( i )->Update ( time );
        }

        // Update the lights.
        for ( int i = 0; i < LightCount (); i++ )
        {
            GetLight ( i )->Update ();
        }

        // Update the node's world transformation.
        if ( !worldTransformIsCurrent )
        {
            // If the node has a parent, find the product
            // of the parent's world transformation and the
            // node's local transformation to get the node's
            // new world tranformation.
            if ( this->GetParent () != null && this->GetParent ()->IsDerived ( SceneNode::GetRTTI () ) )
            {
                SceneNode* parentNode = (SceneNode*) this->GetParent ();
                world = parentNode->world * local.GetMatrix ();
            }
            // The node does not have a SceneNode derived parent, so its
            // world transformation is the same as its local transformation.
            else
            {
                world = local.GetMatrix ();
            }
            
            // We have update the world transform so it is current now.
            worldTransformIsCurrent = true;
        }
        
        // Update all children.
        for ( int i = 0; i < ChildCount (); i++ )
        {
            GetChild ( i )->Update ( time );
        }
    }
    
    void SceneNode::UpdateUp ()
    {
        // Update the node's bounding volume.
        if ( !worldBoundingVolumeIsCurrent )
        {
            // If the node has children, use the children's
            // bounding volumes to recalculate the parent
            // node's bounding volume.
            if ( HasChildren () )
            {
                // Set the node's bounding volume to nothing,
                // then grow to contain all other children.
                boundingVolume.Clear ();
                SceneNode* childNode = null;
                for ( int i = 0; i < ChildCount (); i++ )
                {
                    // If the node's current child is a SceneNode,
                    // then calculate bounding volume stuff.
                    if ( GetChild ( i )->IsDerived ( SceneNode::GetRTTI () ) )
                    {
                        childNode = (SceneNode*) GetChild ( i );
                        boundingVolume.GrowToContain ( childNode->boundingVolume );
                    }
                }
            }
        }
    }

}
