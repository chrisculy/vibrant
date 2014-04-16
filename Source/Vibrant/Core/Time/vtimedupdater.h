/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtimedupdater.h
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

#ifndef VIBRANT_TIMEDUPDATER_H
#define VIBRANT_TIMEDUPDATER_H

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates objects that update at a certain
     * frequency (allows subsystems to run at a set frame rate).
     * 
     * @author Chris Culy
     */
    class VAPI TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param frequency The desired frequency (i.e. 60 for 60 Hz/fps).
             */
            TimedUpdater ( int frequency = -1 );

            /**
             * @brief Destructor.
             */
            virtual ~TimedUpdater ();

            /**
             * @brief Sets the desired frequency of the object.
             * 
             * @param frequency The desired frequency (i.e. 60 for 60 Hz/fps).
             */
            void SetFrequency ( int frequency );

            /**
             * @brief Retrieves the desired frequency of the object.
             * 
             * @return The desired frequency (i.e. 60 for 60 Hz/fps).
             */
            int GetFrequency ();

            /**
             * @brief Calculates the current frame rate for this object.
             * 
             * @return The current frame rate.
             */
            double GetFrameRate ();

            /**
             * @brief Calculates if the object should be updated.
             * 
             * <p>
             * This allows the object to be updated at the desired frequency.
             * Note: Derived classes <b>must</b> call this function
             * when they update to determine whether they should
             * update or not. If this is not used properly,
             * the frequency will not be met.
             * </p>
             * 
             * <p>
             * <b>Example:</b>
             * <pre>
             * void DerivedFromTimedUpdater :: update ()
             * {
             *      if ( this->DoUpdate () )
             *      {
             *          // .. update the object here .. 
             *      }
             * }
             * </pre>
             * </p>
             * 
             * @return <code>true</code> if the object should be
             *      updated;<code>false</code> otherwise.
             */
            virtual bool DoUpdate ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the desired frequency. */
            int frequency;

            /** @brief Holds the number of updates. */
            long updateCount;

            /** @brief Holds the number of milliseconds passed. */
            double millisecondsPassed;

            /** @brief Holds the time interval between updates (in milliseconds). */
            int updateTimeInterval;

            /** @brief Holds the last time that an update occurred. */
            long previousTime;

            /** @brief Holds the last time (in increments of the update
             * time interval) that an update occurred. */
            long previousUpdateTime;

            /** @brief Holds the current time. */
            long currentTime;
    };

}

#endif
