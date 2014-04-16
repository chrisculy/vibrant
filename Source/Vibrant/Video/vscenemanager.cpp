/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscenemanager.cpp
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
#include "vscene.h"
#include "vscenemanager.h"
#include "vsystemmanager.h"
#include "vtime.h"

namespace Vibrant
{
    
    SceneManager::SceneManager ( RenderWindow* renderWindow )
    {
        this->scene.Push ( renderWindow->GetScene () );
    }
    
    SceneManager::~SceneManager ()
    {
        /*stub function*/
    }
    
    void SceneManager::Update ()
    {
        Time* time = SystemManager::GetTimeSystem ();
        for ( int i = 0; i < this->scene.Size (); i++ )
        {
            this->scene[ i ]->Update ( time->GetTime () );
        }
    }
    
    Scene* SceneManager::CreateScene ( double x, double y )
    {
        /*stub function*/
        return null;
    }
    
    Scene* SceneManager::GetMainScene ()
    {
        if ( this->scene.IsEmpty () )
        {
            throw EmptyContainerException ( "SceneManager::GetMainScene - Scene is empty." );
        }
        
        return this->scene[ 0 ];
    }

}
