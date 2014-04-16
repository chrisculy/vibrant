/*
 * =======================================
 * ================ Osprey ===============
 * =======================================
 *
 * 
 * File: testapplication.cpp
 * 
 * 
 * --  Copyright (c) 2009-2010 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#include "testapplication.h"
#include "vclient.h"
#include "vconfig.h"
#include "veventsystem.h"
#include "vindexbuffer.h"
#include "vinput.h"
#include "vinputsystem.h"
#include "vlog.h"
#include "vmesh.h"
#include "vsystem.h"
#include "vsystemmanager.h"
#include "vtexture.h"
#include "vtextureeffect.h"
#include "vvertexbuffer.h"
#include "vvideo.h"

#ifdef SYSTEM_WINDOWS

#include "vwindowsclient.h"

using namespace Vibrant;

namespace Osprey
{
    TestApplication::TestApplication ( Config* config, HINSTANCE hInstance ) :
        WindowsApplication ( config, hInstance )
    {
        
    }
    
    TestApplication::~TestApplication ()
    {
        
    }
    
    bool TestApplication::OnKeyDown ( Input* input, KeyEventParam param )
    {
        switch ( param.key )
        {
            case KEY_SPACE:
            {
                return false;
            }
            default:
                return false;
        }
    }
    
    void TestApplication::Run ()
    {
        try
        {
            // Set up key bindings.
            Input* input = SystemManager::GetInputSystem ();
            input->keyDown.Subscribe ( EventSystem::MakeListener ( this, &TestApplication::OnKeyDown ) );
            
            // Create a scene node as a container for all meshes.
            Video* video = SystemManager::GetVideoSystem ();
            Scene* scene = video->GetMainRenderWindow ()->GetScene ();
            SceneNodePtr root = new SceneNode ();
            scene->AddChild ( root );
            
            // Create a quad.
            Vector pos0 ( 0.0, 0.0, 0.0 );
            Vector pos1 ( 320.0, 0.0, 0.0 );
            Vector pos2 ( 320.0, 120.0, 0.0 );
            Vector pos3 ( 0.0, 120.0, 0.0 );
            Color white ( 1.0, 1.0, 1.0 );
            
            // Create the texture and the texture coordinates.
            Texture texture ( "D:/Programming/alterr/osprey/osprey.png" );
            TextureCoord tc0 ( 0, texture.GetHeight () );
            TextureCoord tc1 ( texture.GetWidth (), texture.GetHeight () );
            TextureCoord tc2 ( texture.GetWidth (), 0 );
            TextureCoord tc3 ( 0, 0 );
            
            Vertex vertices[ 4 ];
            vertices[ 0 ].SetPosition ( pos0 );
            vertices[ 0 ].SetColor ( white );
            vertices[ 0 ].SetTextureCoord ( tc0 );
            vertices[ 1 ].SetPosition ( pos1 );
            vertices[ 1 ].SetColor ( white );
            vertices[ 1 ].SetTextureCoord ( tc1 );
            vertices[ 2 ].SetPosition ( pos2 );
            vertices[ 2 ].SetColor ( white );
            vertices[ 2 ].SetTextureCoord ( tc2 );
            vertices[ 3 ].SetPosition ( pos3 );
            vertices[ 3 ].SetColor ( white );
            vertices[ 3 ].SetTextureCoord ( tc3 );
            
            VertexBufferPtr vertexBuffer = new VertexBuffer ( vertices, 4 );
            unsigned short indices[ 4 ] = { 0, 1, 2, 3 };
            IndexBufferPtr indexBuffer = new IndexBuffer ( indices, 4 );
            MeshPtr mesh = new Mesh ( vertexBuffer, indexBuffer );
            mesh->SetMeshType ( Mesh::QUAD );
            
            TextureEffect textureEffect ( &texture );
            mesh->AddEffect ( &textureEffect );
            
            // Add the mesh to the scene.
            root->AddChild ( mesh );
            
            // Set the client to not run in high performance mode (don't hog the CPU).
            WindowsClient* windowsClient = (WindowsClient*) client;
            windowsClient->SetInHighPerformanceMode ( false );
            
            // Start the client.
            client->Start ();
            
            // Set the main render window's display style to 2D.
            DisplayStyle* displayStyle = video->GetMainRenderWindow ()->GetDisplayStyle ();
            displayStyle->SetIs2D ( true );
            
            // Enter main program loop (update everything until the client is done).
            while ( !client->IsDone () )
            {
                client->Update ();
            }
            
            // We are done, so stop the client.
            client->Stop ();
        }
        catch ( Exception e )
        {
            this->logger << ERR << e.GetMessage ();
        }
    }

}

#endif
