/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrenderwindow.cpp
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

#include "vrenderwindow.h"

namespace Vibrant
{
    
    RenderWindow::RenderWindow ( int x, int y, int width, int height, DisplayStyle* style, GUI* gui )
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->style = style;
        this->scene = new Scene ( new Camera (), new Culler () );
        this->gui = gui;
    }
    
    RenderWindow::~RenderWindow ()
    {
        /*stub function*/
    }
    
    void RenderWindow::Update ()
    {
        /*stub function*/
    }
    
    void RenderWindow::Resize ( int width, int height )
    {
        /* stub function */
    }
    
    void RenderWindow::Move ( int x, int y )
    {
        /* stub function */
    }
    
    int RenderWindow::GetX () const
    {
        return x;
    }
    
    int RenderWindow::GetY () const
    {
        return y;
    }
    
    int RenderWindow::GetWidth () const
    {
        return width;
    }
    
    int RenderWindow::GetHeight () const
    {
        return height;
    }
    
    DisplayStyle* RenderWindow::GetDisplayStyle () const
    {
        return style;
    }
    
    Scene* RenderWindow::GetVisibleScene () const
    {
        return scene;
    }
    
    Scene* RenderWindow::GetScene () const
    {
        return scene;
    }
    
    GUI* RenderWindow::GetGUI () const
    {
        return gui;
    }
    
    void RenderWindow::SetX ( int x )
    {
        this->x = x;
    }
    
    void RenderWindow::SetY ( int y )
    {
        this->y = y;
    }
    
    void RenderWindow::SetWidth ( int width )
    {
        this->width = width;
    }
    
    void RenderWindow::SetHeight ( int height )
    {
        this->height = height;
    }

}
