#ifndef VIBRANT_SAMPLE_SAMPLELISTENER_H
#define VIBRANT_SAMPLE_SAMPLELISTENER_H

#include "sample_mysender.h"

/**
 * @brief Sample event listener class.
 * 
 * @author Chris Culy
 */
class SampleListener
{
    public:
        
        /**
         * @brief Constructor.
         */
        SampleListener ();

        /**
         * @brief Destructor.
         */
        ~SampleListener ();

        /**
         * @brief Handles the sample event.
         * 
         * @param sender The sender of the event.
         * @param arg The argument of the event.
         * @return <code>true</code> if the event was handled;
         *      <code>false</code> otherwise.
         */
        bool OnSenderEvent ( SampleSender* sender, int arg )
        {
            std::cout << "Handled SampleSender event with arg = " << arg << ".\n";
            return true;
        }
};

#endif
