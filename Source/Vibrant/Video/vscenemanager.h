/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscenemanager.h
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

#ifndef VIBRANT_SCENEMANAGER_H
#define VIBRANT_SCENEMANAGER_H

#include "varray.h"
#include "vrenderwindow.h"
#include "vscene.h"

namespace Vibrant
{
    
    /**
     * @brief Manages all the currently used scenes for the engine.
     * 
     * <p>
     * This class allows the creation of new scenes from a position within
     * the world, as well as keeping track of all the scenes (and the main
     * scene in particular) and updating them each frame.
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI SceneManager
    {
        public:
            
            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             * 
             * <p>
             * If <code>renderWindow</code> is not <code>null</code>, then
             * the constructor will walk through the GUI and add all auxiliary
             * scenes (from GUIRenderWindow objects) to the
             * SceneManager::scene member.
             * </p>
             */
            SceneManager ( RenderWindow* renderWindow = null );

            /**
             * @brief Destructor.
             */
            virtual ~SceneManager ();

            /**
             * @brief Updates all the scenes (the parts of
             * the world that are visible to the user.)
             */
            virtual void Update ();

            /**
             * @brief Creates a scene from the region of the world
             * surrounding the given coordinates and also adds
             * the newly created scene to the list of active scenes.
             * 
             * @param x the x coordinate in the world map of the specified location
             * @param y the y coordinate in the world map of the specified location
             * @return A scene generated from the specified location in the world.
             */
            virtual Scene* CreateScene ( double x, double y );

            /**
             * @brief Returns the main scene.
             * 
             * @return The main scene (the scene that is displayed in the main render window).
             * @throws EmptyContainerException If the scene is empty (i.e. there is no main scene).
             */
            virtual Scene* GetMainScene ();

            //************************ General Interface ************************//

        private:
            
            /** @brief Holds all the scenes. */
            Array< Scene* > scene;
    };

}

#endif
