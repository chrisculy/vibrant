/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: varmaturecontroller.h
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

#ifndef VIBRANT_ARMATURECONTROLLER_H
#define VIBRANT_ARMATURECONTROLLER_H

#include "varray.h"
#include "vcontroller.h"
#include "vmatrix.h"
#include "vmesh.h"
#include "vreader.h"
#include "vserializable.h"
#include "vstring.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates bones (used for skeletal animation).
     * 
     * @author Chris Culy
     */
    struct VAPI Bone : public Serializable
    {
            /**
             * @brief Destructor.
             */
            virtual ~Bone ();

            /** @brief Holds the name of the bone. */
            String name;

            /** @brief Holds the number of keyframes. */
            int keyframeCount;

            /** @brief Holds the matrix for each keyframe. */
            Matrix* matrix;

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );
    };
    
    /**
     * @brief Encapsulates the concept of an action
     * for a 3D object (i.e. run, walk, attack, etc.).
     * 
     * @author Chris Culy
     */
    struct VAPI Action : public Serializable
    {
        public:
            
            /** @brief Holds the start frame of the action. */
            int startFrame;

            /** @brief Holds the end frame of the action. */
            int endFrame;

            /** @brief Holds the number of keyframes for the action. */
            int keyframeCount;

            /** @brief Holds the keyframes for the action. */
            int* keyframes;

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );
    };
    
    /**
     * @brief Encapsulates armature (bones) animation.
     * 
     * @author Chris Culy
     */
    class VAPI ArmatureController : public Controller
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param mesh The mesh that this controller controls.
             * @param bones The armature's bones.
             * @param actions The armature's actions.
             */
            ArmatureController ( Mesh* mesh, Array< Bone >* bones, Array< Action >* actions );

            /**
             * @brief Destructor.
             */
            ~ArmatureController ();

            /**
             * @brief Retrieves the bones of the armature.
             */
            const Array< Bone >* GetBones () const;

            /**
             * @brief Retrieves the actions of the armature.
             */
            const Array< Action >* GetActions () const;

            //************************ General Interface ***********************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all armature controllers.
             * 
             * @return The ArmatureController RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );

            //************************ Streaming system ************************//

        private:
            
            /** @brief Holds the bones of the armature. */
            Array< Bone >* bones;

            /** @brief Holds the actions of the armature. */
            Array< Action >* actions;
    };

}

#endif
