/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: varmaturecontroller.cpp
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
#include "vmesh.h"
#include "vobject.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Bone::~Bone ()
    {
        /*stub function */
    }
    
    const int Bone::GetDiskSize () const
    {
        static int staticSize = sizeof(int) + sizeof(Matrix*);
        return staticSize + sizeof( name.CString () );
    }
    
    void Bone::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "Bone" );
        writer->WriteProperty ( "name", this->name );
        writer->WriteProperty ( "keyframes", this->keyframeCount );
        for ( int matrixIndex = 0; matrixIndex < this->keyframeCount; matrixIndex++ )
        {
            writer->WriteChild ( &( this->matrix[ matrixIndex ] ) );
        }
        writer->EndObject ();
    }
    
    void Bone::Read ( Reader* reader )
    {
        reader->BeginObject ( "Bone" );
        reader->ReadProperty ( "name", &this->name );
        reader->ReadProperty ( "keyframes", &this->keyframeCount );
        
        // TODO: Manage memory.
        this->matrix = new Matrix[ this->keyframeCount ];
        for ( int matrixIndex = 0; matrixIndex < this->keyframeCount; matrixIndex++ )
        {
            reader->ReadChild ( &( this->matrix[ matrixIndex ] ) );
        }
        reader->EndObject ();
    }
    
    const int Action::GetDiskSize () const
    {
        static int staticSize = ( sizeof(int) * 3 ) + sizeof(int*);
        return staticSize;
    }
    
    void Action::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "Action" );
        writer->WriteProperty ( "start", this->startFrame );
        writer->WriteProperty ( "end", this->endFrame );
        writer->WriteProperty ( "keyframe-count", this->keyframeCount );
        
        // Write out the keyframe values.
        writer->WriteProperty ( "keyframes", this->keyframes, this->keyframeCount );
        writer->EndObject ();
    }
    
    void Action::Read ( Reader* reader )
    {
        reader->BeginObject ( "Action" );
        reader->ReadProperty ( "start", &this->startFrame );
        reader->ReadProperty ( "end", &this->endFrame );
        reader->ReadProperty ( "keyframe-count", &this->keyframeCount );
        
        // TODO: Manage memory.
        this->keyframes = new int[ this->keyframeCount ];
        
        // Read in the keyframe values.
        reader->ReadProperty ( "keyframes", this->keyframes, this->keyframeCount );
        reader->EndObject ();
    }
    
    ArmatureController::ArmatureController ( Mesh* mesh, Array< Bone >* bones, Array< Action >* actions )
    {
        /* stub function */
        this->SetObject ( (Object*) mesh );
        this->bones = bones;
        this->actions = actions;
    }
    
    ArmatureController::~ArmatureController ()
    {
        /* stub function */
    }
    
    const Array< Bone >* ArmatureController::GetBones () const
    {
        return this->bones;
    }
    
    const Array< Action >* ArmatureController::GetActions () const
    {
        return this->actions;
    }
    
    const RTTI* ArmatureController::GetType () const
    {
        return ArmatureController::GetRTTI ();
    }
    
    RTTI* ArmatureController::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            baseTypes.Push ( Controller::GetRTTI () );
            type = new RTTI ( "ArmatureController", baseTypes );
        }
        return type;
    }
    
    const int ArmatureController::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void ArmatureController::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        writer->WriteProperty ( "name", this->GetName () );
        
        const Array< Bone >* bones = this->GetBones ();
        int boneCount = bones->Size ();
        writer->WriteProperty ( "bones", boneCount );
        
        const Array< Action >* actions = this->GetActions ();
        int actionCount = actions->Size ();
        writer->WriteProperty ( "actions", actionCount );
        
        // Write out the Controller part of this object.
        writer->BeginBase ();
        Controller::Write ( writer );
        writer->EndBase ();
        
        // Write out all the bones.
        for ( int boneIndex = 0; boneIndex < boneCount; boneIndex++ )
        {
            writer->WriteChild ( &( this->bones->At ( boneIndex ) ) );
        }

        // Write out all the actions.
        for ( int actionIndex = 0; actionIndex < actionCount; actionIndex++ )
        {
            writer->WriteChild ( &( this->actions->At ( actionIndex ) ) );
        }
        writer->EndObject ();
    }
    
    void ArmatureController::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        String name;
        reader->ReadProperty ( "name", &name );
        this->SetName ( name );
        
        int boneCount = 0;
        reader->ReadProperty ( "bones", &boneCount );
        
        // TODO: Manage memory.
        this->bones = new Array< Bone > ( boneCount );
        
        int actionCount = 0;
        reader->ReadProperty ( "actions", &actionCount );
        
        // TODO: Manage memory.
        this->actions = new Array< Action > ( actionCount );
        
        // Read in the Controller part of this object.
        reader->BeginBase ();
        Controller::Read ( reader );
        reader->EndBase ();
        
        // Read in all the bones.
        for ( int boneIndex = 0; boneIndex < boneCount; boneIndex++ )
        {
            reader->ReadChild ( &( this->bones->At ( boneIndex ) ) );
        }

        // Read in all the actions.
        for ( int actionIndex = 0; actionIndex < actionCount; actionIndex++ )
        {
            reader->ReadChild ( &( this->actions->At ( actionIndex ) ) );
        }
        reader->EndObject ();
    }

}
