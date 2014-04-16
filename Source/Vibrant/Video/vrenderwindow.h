/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrenderwindow.h
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

#ifndef VIBRANT_RENDERWINDOW_H
#define VIBRANT_RENDERWINDOW_H

#include "vdisplaystyle.h"
#include "vgui.h"
#include "vobject.h"
#include "vpointer.h"
#include "vscene.h"

namespace Vibrant
{
    
    /**
     * @brief Represents the concept of an area of the screen to be rendered to.
     * 
     * <p>
     * This could be the entire screen or just a portion of it. This is used
     * in particular for multiple viewports.
     * </p>
     * 
     * @see GUIRenderWindow
     * @see Object
     * @see Pointer
     * @author Chris Culy
     */
    class VAPI RenderWindow : public Object
    {
        public:
            
            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             */
            RenderWindow ( int x = 0, int y = 0, int width = 0, int height = 0, DisplayStyle* style = new DisplayStyle (), GUI* = null );

            /**
             * @brief Destructor.
             */
            ~RenderWindow ();

            /**
             * @brief Updates the render window.
             */
            virtual void Update ();

            /**
             * @brief Resizes the render window.
             * 
             * @param width The window's new width.
             * @param height The window's new height.
             */
            virtual void Resize ( int width, int height );

            /**
             * @brief Moves the render window.
             * 
             * @param x The new x coordinate of the top left corner of the window.
             * @param y The new y coordinate of the top left corner of the window.
             */
            virtual void Move ( int x, int y );

            /**
             * @brief Retreives the x coordinate of the window's
             * top left corner (in screen coordinates, in pixels.)
             * 
             * @return The window's top left corner x coordinate.
             */
            int GetX () const;

            /**
             * @brief Retreives the y coordinate of the window's
             * top left corner (in screen coordinates, in pixels.)
             * 
             * @return The window's top left corner y coordinate.
             */
            int GetY () const;

            /**
             * @brief Retrieves the window's width.
             * 
             * @return The window's width.
             */
            int GetWidth () const;

            /**
             * @brief Retrieves the window's height.
             * 
             * @return The window's height.
             */
            int GetHeight () const;

            /**
             * @brief Retrieves the window's display style.
             * 
             * @return The window's display style.
             */
            DisplayStyle* GetDisplayStyle () const;

            /**
             * @brief Retrieves the window's visible scene.
             * 
             * @return The window's visible scene.
             */
            Scene* GetVisibleScene () const;

            /**
             * @brief Retrieves the window's full scene.
             * 
             * @return The window's scene.
             */
            Scene* GetScene () const;

            /**
             * @brief Retrieves the window's GUI.
             * 
             * @return The window's GUI.
             */
            GUI* GetGUI () const;

            /**
             * @brief Sets the x coordinate of the window's
             * top left corner (in screen coordinates, in pixels.)
             * 
             * @param x The window's new top left corner x coordinate.
             */
            void SetX ( int x );

            /**
             * @brief Sets the y coordinate of the window's
             * top left corner (in screen coordinates, in pixels.)
             * 
             * @param y The window's new top left corner y coordinate.
             */
            void SetY ( int y );

            /**
             * @brief Sets the window's width.
             * 
             * @param width The window's new width.
             */
            void SetWidth ( int width );

            /**
             * @brief Sets the window's height.
             * 
             * @param height The window's new height.
             */
            void SetHeight ( int height );

            //************************ General Interface ************************//

        private:
            
            /** @brief The x coordinate of the top left corner of the window (in screen coordinates, in pixels). */
            int x;

            /** @brief The y coordinate of the top left corner of the window (in screen coordinates, in pixels). */
            int y;

            /** @brief The width of the window (in pixels). */
            int width;

            /** @brief The height of the window (in pixels). */
            int height;

            /** @brief The display style for the window (i.e. normal, wireframe, IR vision, etc.). */
            DisplayStyle* style;

            /** @brief Holds the scene visible through the render window. */
            Scene* scene;

            /** @brief Holds the render window's GUI (if it has one). */
            GUI* gui;
    };
    
    typedef Pointer< RenderWindow > RenderWindowPtr;

}

#endif
