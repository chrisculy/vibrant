/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationdemo.h
 * 
 * 
 * --  Copyright (c) 2007-2009 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#ifndef VIBRANT_ANIMATIONDEMO_H
#define VIBRANT_ANIMATIONDEMO_H

#include "vanimatable.h"
#include "vanimation.h"
#include "vanimationsession.h"
#include "vconfig.h"
#include "vinput.h"
#include "vinputsystem.h"
#include "vlog.h"
#include "vmesh.h"
#include "vstring.h"
#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vwindowsapplication.h"

using namespace Vibrant;

/**
 * @brief A demo application that demonstrates the animation system.
 * 
 * @author Chris Culy
 */
class AnimationWindowsApplication : public WindowsApplication
{
    public:
        
        /**
         * @see WindowsApplication#WindowsApplication(Config, HINSTANCE)
         */
        AnimationWindowsApplication ( Config* config, HINSTANCE hInstance );

        /**
         * @brief Destructor.
         */
        ~AnimationWindowsApplication ();

        /**
         * @see Input#keyDown
         */
        bool OnKeyDown ( Input* input, KeyEventParam param );

        /**
         * @see Application#run()
         */
        void Run ();

    private:
        
        /** @brief Holds the main animation. */
        Animation* a1;

        /** @brief Holds the first animation track of the main animation. */
        AnimationTrack* a1ATrack;

        /** @brief Holds the second animation track of the main animation. */
        AnimationTrack* a1BTrack;

        /** @brief Holds the third animation track of the main animation. */
        AnimationTrack* a1CTrack;

        /** @brief Holds the fourth animation track of the main animation. */
        AnimationTrack* a1DTrack;

        /** @brief Holds the logger. */
        Log logger;
};

/**
 * @brief The box that is animated in the animation demo.
 * 
 * @author Chris Culy
 */
class AnimatableBox : public Mesh, public Animatable
{
    public:
        
        //************************ General Interface ***********************//

        /**
         * @brief Constructor.
         */
        AnimatableBox ();

        /**
         * @brief Destructor.
         */
        ~AnimatableBox ();

        /**
         * @see Animatable#ApplyAnimatedValue(float*, short, int, float)
         */
        void ApplyAnimatedValue ( float* animatedValue, short animatedValueSize, int targetAttribute );

        /**
         * @see Animatable#GetAnimationSession(int)
         */
        AnimationSession* GetAnimationSession ( int targetAttribute );

        /**
         * @see Animatable#GetTargetAttribute(String)
         */
        int GetTargetAttribute ( String attributeName );

        /**
         * @see Animatable#GetTargetAttributeSize(int)
         */
        int GetTargetAttributeSize ( int targetAttribute );

        /**
         * @see Animatable#GetTargetAttributeType(int)
         */
        AnimatableAttributeType GetTargetAttributeType ( int targetAttribute );

        /**
         * @see Animatable#GetTargetAttributeValue(int, float*, short)
         */
        void GetTargetAttributeValue ( int targetAttribute, float* value, short valueSize );

        //************************ General Interface ***********************//

    private:
        
        /** @brief Holds the animation session for translation and transformation. */
        AnimationSession* transformAnimationSession;

        /**
         * @brief Represents the animatable attributes of the animatable box.
         */
        enum AnimatableAttribute
        {
            ATTRIBUTE_TRANSLATION = 0,
            ATTRIBUTE_ROTATION,
            ATTRIBUTE_TRANSFORMATION
        };

        /** @brief Holds the string name for animating translation. */
        static const String attributeTranslation;

        /** @brief Holds the string name for animating rotation. */
        static const String attributeRotation;

        /** @brief Holds the string name for animating transformation. */
        static const String attributeTransform;
};

#endif

#endif
