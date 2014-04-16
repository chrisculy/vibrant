/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcontroller.h
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

#ifndef VIBRANT_CONTROLLER_H
#define VIBRANT_CONTROLLER_H

#include "vobject.h"
#include "vpointer.h"
#include "vreader.h"
#include "vrtti.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Provides time-based control of an object.
     * 
     * <p>
     * This is an interface for changing any attribute of an
     * object over time (i.e. animation).
     * </p>
     * 
     * @see Object
     * @see RTTI
     * @see Stream
     * @author Chris Culy
     */
    class VAPI Controller : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Destructor.
             */
            virtual ~Controller ();

            /**
             * @brief Gets the controlled object.
             * 
             * @returns The controlled object.
             */
            Pointer< Object > GetObject ();

            /**
             * @brief Updates the controller.
             * 
             * @param time The current time (in milliseconds).
             * @return <code>true</code> if the controller was successfully
             *      updated; <code>false</code> otherwise.
             */
            virtual bool Update ( long time );

            /**
             * @brief Holds the various repeat types for time-based controllers.
             * 
             * <p>
             * The repeat types:
             * <ul>
             *  <li>CLAMP - causes the "animation" to be clamped to the
             *      minimum and maximum times. If the time goes below minTime,
             *      it is set to minTime; if the time goes above maxTime, it
             *      is set to maxTime.</li>
             *  <li>WRAP - causes the "animation" to start from minTime
             *      when it reaches maxTime.</li>
             *  <li>CYCLE - causes the "animation" to bounce back and forth
             *      between minTime and maxTime. When the time reaches
             *      maxTime, it decreases towards minTime, etc.</li>
             * </ul>
             * </p>
             */
            enum RepeatType
            {
                CLAMP,
                WRAP,
                CYCLE,
                REPEAT_QUANTITY
            };

            /**
             * @brief The repeat type for this controller.
             */
            RepeatType repeatType;

            /**
             * @brief The minimum time for this controller.
             */
            double minTime;

            /**
             * @brief The maximum time for this controller.
             */
            double maxTime;

            /**
             * @brief The frequency used to convert to this controller's
             * time units, where:
             * <code>controllerTime = frequency * applicationTime + phase</code>.
             */
            double phase;

            /**
             * @brief Holds the controller's frequency.
             * 
             * <p>
             * The frequency used to convert to this controller's time units, where:
             * <code>controllerTime = frequency * applicationTime + phase</code>.
             * </p>
             */
            double frequency;

            /**
             * @brief Specifies whether this controller is active or not
             * (if this controller is not active, it is not updated).
             * </p>
             */
            bool active;

            //************************ General Interface ***********************//
            

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
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all controllers.
             * 
             * @return The Controller RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Default constructor.
             * 
             * <p>
             * Declared protected to make this an abstract class.
             * </p>
             */
            Controller ();

            /**
             * @brief Sets the controlled object.
             * 
             * @param obj The object to control.
             */
            virtual void SetObject ( Object* obj );

            /**
             * @brief Converts application time to controller time units.
             * 
             * @param applicationTime The current time of the application.
             * @throws NullPointerException If applicationTime is null.
             * @return The current time of the application in controller units.
             */
            double GetControllerTime ( double applicationTime ) const;

            //************************ General Interface ***********************//

        private:
            
            /** @brief Application time when this object was updated last(in ms). */
            double lastApplicationTime;

            /** @brief Controlled object (we use a normal pointer to not create
             * a circular loop since every Object holds smart pointers to
             * its controllers). */
            Object* obj;
    };
    
    typedef Pointer< Controller > ControllerPtr;

}

#endif
