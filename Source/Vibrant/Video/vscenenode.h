/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vscenenode.h
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

#ifndef VIBRANT_SCENENODE_H
#define VIBRANT_SCENENODE_H

#include "varray.h"
#include "vboundingvolume.h"
#include "veffect.h"
#include "vlight.h"
#include "vnode.h"
#include "vpointer.h"
#include "vreader.h"
#include "vrtti.h"
#include "vtransform.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the hierarchical behavior of objects with
     * 3D properties (local/world transformations, bounding volumes,
     * lights and lighting states, and effects) within a scene graph.
     * 
     * @see Node
     * @see Transform
     * @see BoundingVolume
     * @see Light
     * @see Effect
     * @author Chris Culy
     */
    class VAPI SceneNode : public Node
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            SceneNode ();

            /**
             * @brief Destructor.
             */
            ~SceneNode ();

            //************************ General Interface ***********************//
            

            //************************ Update Interface ************************//

            /**
             * @brief Updates the scene node and all its children.
             * 
             * <p>
             * Updates controllers and transformations as it moves down
             * the hierarchy and updates bounding volumes as it moves back
             * up the hierarchy.
             * </p>
             * 
             * @param time The current system time in milliseconds.
             */
            virtual void Update ( long time );

            /**
             * @brief The scene node's local transformation.
             */
            Transform local;

            /**
             * @brief The scene node's world transformation matrix.
             */
            Matrix world;

            /**
             * @brief The scene node's bounding volume.
             * 
             * <p>
             * (Consider making this private.)
             * </p>
             */
            BoundingVolume boundingVolume;

            /** @brief Holds whether the world's bounding volume is current. */
            bool worldBoundingVolumeIsCurrent;

            /** @brief Holds whether the world's transformation is current. */
            bool worldTransformIsCurrent;

            //************************ Update Interface ************************//
            

            //**************** Lights (Lighting State) Interface ***************//

            /**
             * @brief Retrieves the number of lights
             * associated with the scene node.
             * 
             * @return The number of lights.
             */
            const int LightCount () const;

            /**
             * @brief Adds a light to the scene node.
             * 
             * @param light The light to add.
             * @throws NullPointerException If light is null.
             * @see #RemoveLight
             * @see #RemoveAllLights
             */
            void AddLight ( Light* light );

            /**
             * @brief Removes a light from the scene node.
             * 
             * @param light The light to remove.
             * @throws NullPointerException If light is null.
             * @see #AddLight
             * @see #RemoveAllLights
             */
            void RemoveLight ( Light* light );

            /**
             * @brief Removes all lights from the scene node.
             * 
             * @see #AddLight
             * @see #RemoveLight
             */
            void RemoveAllLights ();

            /**
             * @brief Retrieves the light at the specified index.
             * 
             * @param index The index of the desired light.
             * @throws IndexOutOfBoundsException If index &lt; 0 or
             *      index > LightCount ().
             * @return The specified light.
             */
            Light* GetLight ( int index ) const;

            //**************** Lights (Lighting State) Interface ***************//
            

            //************************ Effects Interface ***********************//

            /**
             * @brief Retrieves the number of effects
             * associated with the scene node.
             * 
             * @return The number of effects.
             */
            const int EffectCount () const;

            /**
             * @brief Adds an effect to the scene node.
             * 
             * @param effect The effect to add.
             * @throws NullPointerException If effect is null.
             * @see #RemoveEffect
             * @see #RemoveAllEffects
             */
            void AddEffect ( Effect* effect );

            /**
             * @brief Removes an effect from the scene node.
             * 
             * @param effect The effect to remove.
             * @throws NullPointerException If effect is null.
             * @see #AddEffect
             * @see #RemoveAllEffects
             */
            void RemoveEffect ( Effect* effect );

            /**
             * @brief Removes all effects from the scene node.
             * 
             * @see #AddEffect
             * @see #RemoveEffect
             */
            void RemoveAllEffects ();

            /**
             * @brief Retrieves the effect at the specified index.
             * 
             * @param index The index of the desired effect.
             * @throws IndexOutOfBoundsException If index &lt; 0 or
             *      index > EffectCount ().
             * @return The specified effect.
             */
            Effect* GetEffect ( int index ) const;

            /**
             * @brief Sets the first effect to execute.
             * 
             * <p>
             * This allows for use of only certain effects.
             * (i.e. add an effect, set the first effect to its index,
             * thus enabling it to be the only effect executed if no
             * further effects are added after it.)
             * </p>
             * 
             * @param index The index of the desired first effect.
             * @throws IndexOutOfBoundsException If index &lt; 0 or
             *      index > EffectCount ().
             */
            void SetFirstEffect ( int index );

            /**
             * @brief Gets the index of the first effect to execute.
             * 
             * @return The index of the first effect.
             */
            const int GetFirstEffect ();

            //************************ Effects Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            virtual const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            virtual void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            virtual void Read ( Reader* reader );

            //************************ Streaming system ************************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all scene nodes.
             * 
             * @return The SceneNode RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//

        protected:
            
            //************************ Update Interface ************************//

            /**
             * @brief Updates down the hierarchy.
             * 
             * <p>
             * Updates controllers, global and lighting states,
             * and world transformation, and all children.
             * </p>
             * 
             * @param time The current system time in milliseconds.
             */
            virtual void UpdateDown ( long time );
            /**
             * @brief Updates up the hierarchy.
             * 
             * <p>
             * Updates bounding volumes based upon the node
             * and its children (and their bounding volumes).
             * </p>
             */
            virtual void UpdateUp ();

            //************************ Update Interface ************************//

        private:
            
            /** @brief Holds all the lighting for this node. */
            Array< Light* > lights;

            /** @brief Holds all the effects for this node. */
            Array< Effect* > effects;

            /** @brief Holds the index of the first effect. */
            int firstEffectIndex;
    };
    
    typedef Pointer< SceneNode > SceneNodePtr;

}

#endif
