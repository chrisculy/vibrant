/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscene.cpp
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

#include "vscene.h"

namespace Vibrant
{
    
    Scene::Scene ( Camera* camera, Culler* culler )
    {
        this->camera = camera;
        this->culler = culler;
    }
    
    Scene::~Scene ()
    {
        /* stub function */
    }
    
    void Scene::Update ( long time )
    {
        SceneNode* root = this->GetRoot ();
        if ( root != null )
        {
            root->Update ( time );
        }
    }
    
    Camera* Scene::GetCamera ()
    {
        return this->camera;
    }
    
    Culler* Scene::GetCuller ()
    {
        return this->culler;
    }
    
    SceneNode* Scene::GetRoot ()
    {
        if ( this->ChildCount () > 0 )
        {
            for ( int i = 0; i < this->ChildCount (); i++ )
            {
                if ( this->GetChild ( i )->IsDerived ( SceneNode::GetRTTI () ) )
                {
                    return (SceneNode*) this->GetChild ( i );
                }
            }
        }
        
        return null;
    }

}
