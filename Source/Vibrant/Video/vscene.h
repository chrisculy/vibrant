/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscene.h
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

#ifndef VIBRANT_SCENE_H
#define VIBRANT_SCENE_H

#include "vcamera.h"
#include "vculler.h"
#include "vmesh.h"
#include "vnode.h"
#include "vpointer.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a single "scene" or area within the game world.
     * 
     * @see Node
     * @author Chris Culy
     */
    class VAPI Scene : public Node
    {
        public:
            
            //************************ General Interface ************************//

            /**
             * @brief Constructor.
             */
            Scene ( Camera* camera, Culler* culler );

            /**
             * @brief Destructor.
             */
            ~Scene ();

            /**
             * @brief Updates the scene.
             * 
             * <p>
             * <br><b>Note:</b> this will eventually include
             * functionality to automatically stream the approaching terrain
             * for the scene over the network/from the DVD/from the HDD.
             * </p>
             * 
             * <p>
             * Note: It is within this function that the system time
             * is retrieved and passed down the chain of update () calls.
             * </p>
             * 
             * @param time The current system time in milliseconds.
             */
            virtual void Update ( long time );

            /**
             * @brief Retrieves the scene's camera.
             * 
             * @return The scene's camera.
             */
            Camera* GetCamera ();

            /**
             * @brief Retrieves the scene's culler.
             * 
             * @return The scene's culler.
             */
            Culler* GetCuller ();

            /**
             * @brief Returns the root object of the scene (this is what is actually rendered).
             * 
             * @return The root scene object.
             */
            SceneNode* GetRoot ();

            //************************ General Interface ************************//

        private:
            
            /** @brief Holds the scene's camera. */
            Camera* camera;

            /** @brief Holds the scene's culler (performs CPU culling before handing off everything else to the GPU). */
            Culler* culler;
    };
    
    typedef Pointer< Scene > ScenePtr;

}

#endif
