/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationdemo.cpp
 * 
 * 
 * --  Copyright (c) 2007-2009 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#include "vanimation.h"
#include "vanimationdemo.h"
#include "vanimationmodes.h"
#include "vanimationsession.h"
#include "vanimationtrack.h"
#include "vaudio.h"
#include "vclient.h"
#include "vindexbuffer.h"
#include "vinput.h"
#include "vkeyframeanimationdata.h"
#include "vlog.h"
#include "vmath.h"
#include "vsimpleanimationdata.h"
#include "vsystem.h"
#include "vsystemmanager.h"
#include "vtime.h"
#include "vvertexbuffer.h"
#include "vvideo.h"

#ifdef SYSTEM_WINDOWS

#include "vwindowsclient.h"

AnimationWindowsApplication::AnimationWindowsApplication ( Config* config, HINSTANCE hInstance ) :
    WindowsApplication ( config, hInstance )
{
    this->a1 = new Animation ();
}

AnimationWindowsApplication::~AnimationWindowsApplication ()
{
    if ( a1 != null )
    {
        delete this->a1;
        this->a1 = null;
    }
}

bool AnimationWindowsApplication::OnKeyDown ( Input* input, KeyEventParam param )
{
    switch ( param.key )
    {
        case KEY_SPACE:
        {
            if ( this->a1->IsActive () )
            {
                this->a1->Pause ();
            }
            else
            {
                this->a1->Play ();
            }
            return true;
        }
        case KEY_LEFT:
        {
            this->a1->Stop ();
            return true;
        }
        case KEY_F:
        {
            Application* app = Application::GetInstance ();
            Client* client = app->GetClient ();
            this->logger << INF << "Client frame rate: " << client->GetFrameRate () << " fps.\n";
            
            Audio* audio = SystemManager::GetAudioSystem ();
            this->logger << INF << "Audio frame rate: " << audio->GetFrameRate () << " fps.\n";
            
            Video* video = SystemManager::GetVideoSystem ();
            this->logger << INF << "Video frame rate: " << video->GetFrameRate () << " fps.\n";
            return true;
        }
        case KEY_T:
        {
            Time* time = SystemManager::GetTimeSystem ();
            this->logger << INF << "Current time: " << time->GetTime () << " ms.\n";
            return true;
        }
        default:
            return false;
    }
}

void AnimationWindowsApplication::Run ()
{
    try
    {
        // Set up key bindings.
        Input* input = SystemManager::GetInputSystem ();
        input->keyDown.Subscribe ( EventSystem::MakeListener ( this, &AnimationWindowsApplication::OnKeyDown ) );
        
        // Create a scene node as a container for all animatable boxes.
        Video* video = SystemManager::GetVideoSystem ();
        Scene* scene = video->GetMainRenderWindow ()->GetScene ();
        SceneNode* root = new SceneNode ();
        scene->AddChild ( root );
        root->local.SetTranslation ( 0.0f, 0.0f, -10.0f );
        root->worldTransformIsCurrent = false;
        
        // Create the boxes and add them to the main scene.
        AnimatableBox* boxOne = new AnimatableBox ();
        AnimatableBox* boxTwo = new AnimatableBox ();
        AnimatableBox* boxThree = new AnimatableBox ();
        AnimatableBox* boxFour = new AnimatableBox ();
        root->AddChild ( boxOne );
        root->AddChild ( boxTwo );
        root->AddChild ( boxThree );
        root->AddChild ( boxFour );
        
        // Move the boxes into their beginning positions and dirty their world transforms.
        boxOne->local.SetTranslation ( 3.0f, 1.75f, 0.0f );
        boxTwo->local.SetTranslation ( 3.0f, -1.75f, 0.0f );
        boxThree->local.SetTranslation ( -3.0f, -1.75f, 0.0f );
        boxFour->local.SetTranslation ( -3.0f, 1.75f, 0.0f );
        
        boxOne->worldTransformIsCurrent = false;
        boxTwo->worldTransformIsCurrent = false;
        boxThree->worldTransformIsCurrent = false;
        boxFour->worldTransformIsCurrent = false;
        
        // ------------- Construct animation data. -------------- //

        // Key points (first and second control tangents) used for spline interpolation.
        Array< float > keyPoints ( 2 );
        keyPoints[ 0 ] = 1.2f;
        keyPoints[ 1 ] = 3.6f;
        
        // -- Key Values and Key Times -- //
        Quaternion qA0 = Quaternion::CreateFromAxisAngle ( 1.0f, 1.0f, 0.0f, 0.0f );
        Quaternion qA1 = Quaternion::CreateFromAxisAngle ( 1.0f, 2.0f, 0.0f, 30.0f );
        Quaternion qA2 = Quaternion::CreateFromAxisAngle ( 1.0f, 3.0f, 0.0f, 320.0f );
        Quaternion qA3 = Quaternion::CreateFromAxisAngle ( 1.0f, 2.0f, 0.0f, 180.0f );
        Quaternion qA4 = Quaternion::CreateFromAxisAngle ( 1.0f, 1.0f, 0.0f, 0.0f );
        
        Array< float* > keyValues ( 5 );
        Array< float > keyTimes ( 5 );
        
        keyValues[ 0 ] = new float[ 4 ];
        keyValues[ 0 ][ 0 ] = qA0.GetX ();
        keyValues[ 0 ][ 1 ] = qA0.GetY ();
        keyValues[ 0 ][ 2 ] = qA0.GetZ ();
        keyValues[ 0 ][ 3 ] = qA0.GetW ();
        
        keyValues[ 1 ] = new float[ 4 ];
        keyValues[ 1 ][ 0 ] = qA1.GetX ();
        keyValues[ 1 ][ 1 ] = qA1.GetY ();
        keyValues[ 1 ][ 2 ] = qA1.GetZ ();
        keyValues[ 1 ][ 3 ] = qA1.GetW ();
        
        keyValues[ 2 ] = new float[ 4 ];
        keyValues[ 2 ][ 0 ] = qA2.GetX ();
        keyValues[ 2 ][ 1 ] = qA2.GetY ();
        keyValues[ 2 ][ 2 ] = qA2.GetZ ();
        keyValues[ 2 ][ 3 ] = qA2.GetW ();
        
        keyValues[ 3 ] = new float[ 4 ];
        keyValues[ 3 ][ 0 ] = qA3.GetX ();
        keyValues[ 3 ][ 1 ] = qA3.GetY ();
        keyValues[ 3 ][ 2 ] = qA3.GetZ ();
        keyValues[ 3 ][ 3 ] = qA3.GetW ();
        
        keyValues[ 4 ] = new float[ 4 ];
        keyValues[ 4 ][ 0 ] = qA4.GetX ();
        keyValues[ 4 ][ 1 ] = qA4.GetY ();
        keyValues[ 4 ][ 2 ] = qA4.GetZ ();
        keyValues[ 4 ][ 3 ] = qA4.GetW ();
        
        keyTimes[ 0 ] = 0.0f;
        keyTimes[ 1 ] = 0.1f;
        keyTimes[ 2 ] = 0.3f;
        keyTimes[ 3 ] = 0.6f;
        keyTimes[ 4 ] = 1.0f;
        // -- Key Values and Key Times -- //

        // -- Animation Data Objects -- //
        KeyframeAnimationData* a1AData = new KeyframeAnimationData ( boxOne, "rotation", &keyValues, &keyTimes, 5 );
        a1AData->SetInterpolationMode ( SPLINE );
        a1AData->SetKeyPoints ( keyPoints[ 0 ], keyPoints[ 1 ] );
        
        KeyframeAnimationData* a1BData = new KeyframeAnimationData ( boxTwo, "rotation", &keyValues, &keyTimes, 5 );
        a1BData->SetInterpolationMode ( DISCRETE );
        
        KeyframeAnimationData* a1CData = new KeyframeAnimationData ( boxThree, "rotation", &keyValues, &keyTimes, 5 );
        a1CData->SetInterpolationMode ( PACED );
        
        KeyframeAnimationData* a1DData = new KeyframeAnimationData ( boxFour, "rotation", &keyValues, &keyTimes, 5 );
        a1DData->SetInterpolationMode ( LINEAR );
        // -- Animation Data Objects -- //

        // ------------- Construct animation data. -------------- //
        

        // ------------ Create and setup animations. ------------ //

        this->a1ATrack = new AnimationTrack ( a1AData, 5.0f );
        this->a1ATrack->SetAdditive ( true );
        this->a1ATrack->SetRepeatCount ( ANIMATION_INDEFINITE );
        this->a1->AddTrack ( this->a1ATrack );
        
        this->a1BTrack = new AnimationTrack ( a1BData, 5.0f );
        this->a1BTrack->SetAdditive ( true );
        this->a1BTrack->SetRepeatCount ( ANIMATION_INDEFINITE );
        this->a1->AddTrack ( this->a1BTrack );
        
        this->a1CTrack = new AnimationTrack ( a1CData, 5.0f );
        this->a1CTrack->SetAdditive ( true );
        this->a1CTrack->SetRepeatCount ( ANIMATION_INDEFINITE );
        this->a1->AddTrack ( this->a1CTrack );
        
        this->a1DTrack = new AnimationTrack ( a1DData, 5.0f );
        this->a1DTrack->SetAdditive ( true );
        this->a1DTrack->SetRepeatCount ( ANIMATION_INDEFINITE );
        this->a1->AddTrack ( this->a1DTrack );
        
        // ------------ Create and setup animations. ------------ //
        

        // Set the client to not run in high performance mode (don't hog the CPU).
        WindowsClient* windowsClient = (WindowsClient*) client;
        windowsClient->SetInHighPerformanceMode ( false );
        
        // Start the client.
        client->Start ();
        
        // Play the animation.
        this->a1->Play ();
        
        // Enter main program loop (update everything until the client is done).
        while ( !client->IsDone () )
        {
            a1->Update ( SystemManager::GetTimeSystem ()->GetTime () );
            client->Update ();
        }

        // Stop the animation.
        this->a1->Stop ();
        
        // We are done, so stop the client.
        client->Stop ();
        
        // Clean up allocated memory.
        delete keyValues[ 0 ];
        delete keyValues[ 1 ];
        delete keyValues[ 2 ];
        delete keyValues[ 3 ];
        delete keyValues[ 4 ];
        
        delete a1AData;
        delete a1BData;
        delete a1CData;
        delete a1DData;
        
        delete this->a1ATrack;
        delete this->a1BTrack;
        delete this->a1CTrack;
        delete this->a1DTrack;
        
        delete boxOne;
        delete boxTwo;
        delete boxThree;
        delete boxFour;
    }
    catch ( Exception e )
    {
        this->logger << ERR << e.GetMessage ();
    }
}

// Initialize static members.
const String AnimatableBox::attributeTranslation = "translation";
const String AnimatableBox::attributeRotation = "rotation";
const String AnimatableBox::attributeTransform = "transform";

AnimatableBox::AnimatableBox ()
{
    // Set the mesh type.
    this->SetMeshType ( TRIANGLE );
    
    // Create the vertex buffer with vertex position, normal, and color.
    Array<Vertex> vertices ( 8 );
    
    vertices[ 0 ].SetPosition ( Vector ( 1.0, 1.0, -1.0 ) );
    vertices[ 1 ].SetPosition ( Vector ( 1.0, -1.0, -1.0 ) );
    vertices[ 2 ].SetPosition ( Vector ( -1.0, -1.0, -1.0 ) );
    vertices[ 3 ].SetPosition ( Vector ( -1.0, 1.0, -1.0 ) );
    vertices[ 4 ].SetPosition ( Vector ( 1.0, 1.0, 1.0 ) );
    vertices[ 5 ].SetPosition ( Vector ( 1.0, -1.0, 1.0 ) );
    vertices[ 6 ].SetPosition ( Vector ( -1.0, -1.0, 1.0 ) );
    vertices[ 7 ].SetPosition ( Vector ( -1.0, 1.0, 1.0 ) );
    
    vertices[ 0 ].SetNormal ( Vector ( 1.0, 1.0, -1.0 ) );
    vertices[ 1 ].SetNormal ( Vector ( 1.0, -1.0, -1.0 ) );
    vertices[ 2 ].SetNormal ( Vector ( -1.0, -1.0, -1.0 ) );
    vertices[ 3 ].SetNormal ( Vector ( -1.0, 1.0, -1.0 ) );
    vertices[ 4 ].SetNormal ( Vector ( 1.0, 1.0, 1.0 ) );
    vertices[ 5 ].SetNormal ( Vector ( 1.0, -1.0, 1.0 ) );
    vertices[ 6 ].SetNormal ( Vector ( -1.0, -1.0, 1.0 ) );
    vertices[ 7 ].SetNormal ( Vector ( -1.0, 1.0, 1.0 ) );
    
    vertices[ 0 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 1 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 2 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 3 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 4 ].SetColor ( Color ( 0.8f, 0.15f, 0.16f ) );
    vertices[ 5 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 6 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    vertices[ 7 ].SetColor ( Color ( 0.0f, 0.55f, 0.76f ) );
    
    this->vertices = new VertexBuffer(vertices, 8);
    
    // Create the index buffer.
    Array<unsigned short> indices ( 36 );
    
    // Front face.
    indices[ 0 ] = 4;
    indices[ 1 ] = 7;
    indices[ 2 ] = 6;
    indices[ 3 ] = 6;
    indices[ 4 ] = 5;
    indices[ 5 ] = 4;
    
    // Right face.
    indices[ 6 ] = 4;
    indices[ 7 ] = 5;
    indices[ 8 ] = 0;
    indices[ 9 ] = 0;
    indices[ 10 ] = 5;
    indices[ 11 ] = 1;
    
    // Top face.
    indices[ 12 ] = 4;
    indices[ 13 ] = 0;
    indices[ 14 ] = 7;
    indices[ 15 ] = 7;
    indices[ 16 ] = 3;
    indices[ 17 ] = 0;
    
    // Left face.
    indices[ 18 ] = 7;
    indices[ 19 ] = 3;
    indices[ 20 ] = 6;
    indices[ 21 ] = 6;
    indices[ 22 ] = 2;
    indices[ 23 ] = 3;
    
    // Bottom face.
    indices[ 24 ] = 2;
    indices[ 25 ] = 1;
    indices[ 26 ] = 6;
    indices[ 27 ] = 6;
    indices[ 28 ] = 1;
    indices[ 29 ] = 5;
    
    // Back face.
    indices[ 30 ] = 1;
    indices[ 31 ] = 2;
    indices[ 32 ] = 0;
    indices[ 33 ] = 0;
    indices[ 34 ] = 2;
    indices[ 35 ] = 3;
    
    this->indices = new IndexBuffer(indices, 36);
    
    // Initialize the animation session.
    this->transformAnimationSession = null;
}

AnimatableBox::~AnimatableBox ()
{
    // Clean up the vertices and indices.
    if ( this->vertices != null )
    {
        //delete this->vertices;
        this->vertices = null;
    }
    if ( this->indices != null )
    {
        //delete this->indices;
        this->indices = null;
    }
    
    // Clean up the animation session.
    if ( this->transformAnimationSession != null )
    {
        delete this->transformAnimationSession;
        this->transformAnimationSession = null;
    }
}

void AnimatableBox::ApplyAnimatedValue ( float* animatedValue, short animatedValueSize, int targetAttribute )
{
    if ( targetAttribute == ATTRIBUTE_TRANSLATION )
    {
        // If we receive a full column wise matrix, extract the translation values.
        if ( animatedValueSize == 16 )
        {
            this->local.SetTranslation ( animatedValue[ 12 ], animatedValue[ 13 ], animatedValue[ 14 ] );
        }
        // Check if it is a three tuple of the actual translation values.
        else if ( animatedValueSize == 3 )
        {
            this->local.SetTranslation ( animatedValue[ 0 ], animatedValue[ 1 ], animatedValue[ 2 ] );
        }
        
        // Set the world transformation as dirty.
        this->worldTransformIsCurrent = false;
    }
    else if ( targetAttribute == ATTRIBUTE_ROTATION )
    {
        // If we receive a full column wise matrix, extract the rotation values.
        if ( animatedValueSize == 16 )
        {
            Quaternion q = Quaternion::CreateFromMatrix ( Matrix ( animatedValue ) );
            this->local.SetRotation ( q );
        }
        // Check if it is a four tuple of the actual rotation values.
        else if ( animatedValueSize == 4 )
        {
            this->local.SetRotation ( animatedValue[ 0 ], animatedValue[ 1 ], animatedValue[ 2 ], animatedValue[ 3 ] );
        }
        
        // Set the world transformation as dirty.
        this->worldTransformIsCurrent = false;
    }
    else if ( targetAttribute == ATTRIBUTE_TRANSFORMATION )
    {
        Matrix matrix ( animatedValue );
        this->local.SetMatrix ( matrix );
        
        // Set the world transformation as dirty.
        this->worldTransformIsCurrent = false;
    }
}

AnimationSession* AnimatableBox::GetAnimationSession ( int targetAttribute )
{
    if ( targetAttribute == ATTRIBUTE_TRANSLATION || targetAttribute == ATTRIBUTE_ROTATION || targetAttribute == ATTRIBUTE_TRANSFORMATION )
    {
        if ( this->transformAnimationSession == null )
        {
            this->transformAnimationSession = new AnimationSession ();
            
            // Set the value size for the animation session.
            this->transformAnimationSession->valueSize = 16;
        }
        
        return this->transformAnimationSession;
    }
    
    return null;
}

int AnimatableBox::GetTargetAttribute ( String attributeName )
{
    if ( attributeName == AnimatableBox::attributeTranslation )
    {
        return ATTRIBUTE_TRANSLATION;
    }
    else if ( attributeName == AnimatableBox::attributeRotation )
    {
        return ATTRIBUTE_ROTATION;
    }
    else if ( attributeName == AnimatableBox::attributeTransform )
    {
        return ATTRIBUTE_TRANSFORMATION;
    }
    
    return -1;
}

int AnimatableBox::GetTargetAttributeSize ( int targetAttribute )
{
    if ( targetAttribute == ATTRIBUTE_TRANSLATION )
    {
        return 3;
    }
    else if ( targetAttribute == ATTRIBUTE_ROTATION )
    {
        return 4;
    }
    else if ( targetAttribute == ATTRIBUTE_TRANSFORMATION )
    {
        return 16;
    }
    
    return -1;
}

AnimatableAttributeType AnimatableBox::GetTargetAttributeType ( int targetAttribute )
{
    if ( targetAttribute == ATTRIBUTE_TRANSLATION )
    {
        return SCALAR;
    }
    else if ( targetAttribute == ATTRIBUTE_ROTATION )
    {
        return QUATERNION;
    }
    else if ( targetAttribute == ATTRIBUTE_TRANSFORMATION )
    {
        return MATRIX;
    }
    else
    {
        throw IllegalArgumentException ( "AnimatableBox::GetTargetAttributeType - Target attribute is not supported." );
    }
}

void AnimatableBox::GetTargetAttributeValue ( int targetAttribute, float* value, short valueSize )
{
    if ( targetAttribute == ATTRIBUTE_TRANSLATION )
    {
        // If we receive a full column wise matrix, copy out the entire local transform.
        if ( valueSize == 16 )
        {
#ifdef _MSC_VER
            memcpy_s ( value, 16 * sizeof ( float ), this->local.GetMatrix ().GetValues (), 16 * sizeof ( float ) );
#else
            memcpy ( value, this->local.GetMatrix ().GetValues (), 16 * sizeof(float) );
#endif
        }
        // Copy out a three tuple of the actual translation values.
        else if ( valueSize == 3 )
        {
            value[ 0 ] = this->local.GetMatrix ().GetValue ( 0, 3 );
            value[ 1 ] = this->local.GetMatrix ().GetValue ( 1, 3 );
            value[ 2 ] = this->local.GetMatrix ().GetValue ( 2, 3 );
        }
    }
    else if ( targetAttribute == ATTRIBUTE_ROTATION )
    {
        // If we receive a full column wise matrix, copy out the entire local transform.
        if ( valueSize == 16 )
        {
#ifdef _MSC_VER
            memcpy_s ( value, 16 * sizeof ( float ), this->local.GetMatrix ().GetValues (), 16 * sizeof ( float ) );
#else
            memcpy ( value, this->local.GetMatrix ().GetValues (), 16 * sizeof(float) );
#endif
        }
        // Copy out a four tuple of the actual rotation values.
        else if ( valueSize == 4 )
        {
            Quaternion q = Quaternion::CreateFromMatrix ( this->local.GetMatrix () );
            value[ 0 ] = q.GetX ();
            value[ 1 ] = q.GetY ();
            value[ 2 ] = q.GetZ ();
            value[ 3 ] = q.GetW ();
        }
    }
    else if ( targetAttribute == ATTRIBUTE_TRANSFORMATION )
    {
#ifdef _MSC_VER
        memcpy_s ( value, 16 * sizeof ( float ), this->local.GetMatrix ().GetValues (), 16 * sizeof ( float ) );
#else
        memcpy ( value, this->local.GetMatrix ().GetValues (), 16 * sizeof(float) );
#endif
    }
}

#endif
