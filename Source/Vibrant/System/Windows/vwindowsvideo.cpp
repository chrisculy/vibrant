/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsvideo.cpp
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vconvert.h"
#include "vlog.h"
#include "vmutex.h"
#include "vmutexlock.h"
#include "vrenderwindow.h"
#include "vscenemanager.h"
#include "vstring.h"
#include "vsystemmanager.h"
#include "vvideo.h"
#include "vwindowsapplication.h"
#include "vwindowsinput.h"
#include "vwindowsexception.h"
#include "vwindowsvideo.h"

namespace Vibrant
{
    
    WindowsVideo::WindowsVideo ( Config* config, RenderWindow* renderWindow ) :
        Video ( config, renderWindow )
    {
        // Store whether the video system is running in a separate thread from the input system.
        this->inSeparateThread = ( config->GetProperty ( "video_thread" ) != "1" );
        
        // Set members to default values.
        this->deviceContext = 0;
        this->renderContext = 0;
        this->windowHandle = 0;
        this->waitMutex = Mutex::GetNewMutex ();
        
        // Store video settings.
        this->width = 0;
        this->height = 0;
        this->bpp = 0;
        StringToVal ( config->GetProperty ( "video_width" ), &this->width );
        StringToVal ( config->GetProperty ( "video_height" ), &this->height );
        StringToVal ( config->GetProperty ( "video_bits_per_pixel" ), &this->bpp );
        
        // Store if the video system is going to be fullscreen.
        bool fullscreen = false;
        StringToVal ( config->GetProperty ( "video_is_fullscreen" ), &fullscreen );
        this->SetIsFullscreen ( fullscreen );
        
        // Set window styles.
        this->windowStyle = WS_OVERLAPPEDWINDOW;
        this->windowExtendedStyle = WS_EX_APPWINDOW;
        
        // Support drawing to a window, and double buffering.
        int supportFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        
        // If we are using DirectX, add
        // the appropriate stuff to the descriptor.
        if ( config->GetProperty ( "video_renderer_type" ) == "DirectX" )
        {
            // Support DirectDraw (DirectX graphics).
            //supportFlags |= PFD_SUPPORT_DIRECTDRAW;
        }
        // Otherwise, use OpenGL.
        else
        {
            supportFlags |= PFD_SUPPORT_OPENGL;
        }

        // Set the pixel format descriptor.
        PIXELFORMATDESCRIPTOR tmpPixelFormatDescriptor = { sizeof(PIXELFORMATDESCRIPTOR), 1, supportFlags, PFD_TYPE_RGBA, (BYTE) bpp, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
        this->pixelFormatDescriptor = tmpPixelFormatDescriptor;
        
        // User selected fullscreen mode.
        if ( this->IsFullscreen () )
        {
            // If we fail to enter fullscreen mode,
            // run in windowed mode instead.
            if ( !this->GoFullscreen ( width, height, bpp ) )
            {
                MessageBox ( HWND_DESKTOP, "Failed to enter full screen mode.\nRunning in windowed mode.", "Error", MB_OK
                    | MB_ICONEXCLAMATION );
                this->SetIsFullscreen ( false );
            }
            // If we enter fullscreen mode successfully.
            else
            {
                ShowCursor ( false );
                this->windowStyle = WS_POPUP;
                this->windowExtendedStyle |= WS_EX_TOPMOST;
            }
        }
        // User selected windowed mode.
        else
        {
            RECT windowRect = { 0, 0, width, height };
            AdjustWindowRectEx ( &windowRect, windowStyle, 0, windowExtendedStyle );
        }

        // Create the application window.
        WindowsApplication* app = (WindowsApplication*) Application::GetInstance ();
        this->windowHandle = CreateWindowEx ( this->windowExtendedStyle, app->GetClassName ().CString (), app->GetTitle ().CString (),
            this->windowStyle, 50, 50, width, height, HWND_DESKTOP, 0, app->GetHInstance (), this );
        
        // Make sure the window was created successfully.
        if ( this->windowHandle == 0 )
        {
            throw WindowsException ( "Could not create window.\n" );
        }

        // Get the device context and make sure we are successful.
        this->deviceContext = GetDC ( this->windowHandle );
        if ( this->deviceContext == 0 )
        {
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
            throw WindowsException ( "Could not get a device context.\n" );
        }

        // Get the pixel format and make sure we are successful.
        int pixelFormat = ChoosePixelFormat ( this->deviceContext, &this->pixelFormatDescriptor );
        if ( pixelFormat == 0 )
        {
            ReleaseDC ( this->windowHandle, this->deviceContext );
            this->deviceContext = 0;
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
            throw WindowsException ( "Could not get the pixel format.\n" );
        }

        // Attempt to set the pixel format.
        if ( !SetPixelFormat ( this->deviceContext, pixelFormat, &this->pixelFormatDescriptor ) )
        {
            ReleaseDC ( this->windowHandle, this->deviceContext );
            this->deviceContext = 0;
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
            throw WindowsException ( "Could not set the pixel format.\n" );
        }
        
        // If the video system runs in a separate thread, then
        // there is some initialization that must take place later,
        // so we just leave that initialization for later.
    }
    
    WindowsVideo::~WindowsVideo ()
    {
        // Destroy everything that still exists in the application
        // if the app has a window handle.
        if ( this->windowHandle != 0 )
        {
            // If the app has a device context.
            if ( this->deviceContext != 0 )
            {
                // Release the device context and set it to 0.
                ReleaseDC ( this->windowHandle, this->deviceContext );
                this->deviceContext = 0;
            }

            // Destroy the window and set the window handle to 0.
            DestroyWindow ( this->windowHandle );
            this->windowHandle = 0;
        }

        // If the window is full screen
        // switch back to the desktop resolution
        // and show the cursor.
        if ( this->IsFullscreen () )
        {
            ChangeDisplaySettings ( null, 0 );
            ShowCursor ( true );
        }
        
        // Clean up wait mutex.
        if ( this->waitMutex != null )
        {
            delete this->waitMutex;
            this->waitMutex = null;
        }
    }
    
    void WindowsVideo::Start ()
    {
        // If we are running in a separate thread
        // synchronize window creation and video
        // initialization with the input system.
        if ( this->inSeparateThread )
        {
            // Lock the video system and perform initialization.
            {
                LockMutex ( this->waitMutex );
                StartVideo ();
                
                // Notify the input system to show the window.
                // The input system *should* be waiting by now;
                // if not, the whole program will probably hang.
                // (The input system is notified when the mutex
                // is released automatically at the end of the code block.)
            }

            // Wait until the window has been shown
            // and before updating the video system.
            WindowsInput* input = (WindowsInput*) SystemManager::GetInputSystem ();
            input->GetWaitMutex ()->Wait ();
        }
        else
        {
            StartVideo ();
        }
    }
    
    void WindowsVideo::Update ()
    {
        if ( this->DoUpdate () )
        {
            this->sceneManager->Update ();
            this->renderer->Draw ( renderWindow );
            
            // Swap the buffers.
            SwapBuffers ( this->deviceContext );
        }
    }
    
    bool WindowsVideo::GoFullscreen ( int width, int height, int bpp )
    {
        DEVMODE deviceModeScreenSettings;
        ZeroMemory ( &deviceModeScreenSettings, sizeof ( DEVMODE ) );
        
        // Set the video mode settings.
        deviceModeScreenSettings.dmSize = sizeof(DEVMODE);
        deviceModeScreenSettings.dmPelsWidth = width;
        deviceModeScreenSettings.dmPelsHeight = height;
        deviceModeScreenSettings.dmBitsPerPel = bpp;
        deviceModeScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        
        // Attempt to go fullscreen.
        if ( ChangeDisplaySettings ( &deviceModeScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
        {
            return false;
        }
        return true;
    }
    
    bool WindowsVideo::IsInSeparateThread ()
    {
        return this->inSeparateThread;
    }
    
    HWND WindowsVideo::GetWindowHandle ()
    {
        return this->windowHandle;
    }
    
    Mutex* WindowsVideo::GetWaitMutex ()
    {
        return this->waitMutex;
    }

}

#endif
