#ifndef VIBRANT_SAMPLE_SAMPLESENDER_H
#define VIBRANT_SAMPLE_SAMPLESENDER_H

#include "vevent.h"

using namespace Vibrant;

/**
 * @brief Sample event sending class.
 * 
 * @author Chris Culy
 */
class SampleSender
{
    public:
        
        /**
         * @brief Constructor.
         */
        SampleSender ();

        /**
         * @brief Destructor.
         */
        ~SampleSender ();

        /** @brief The sample event. */
        Event< SampleSender, int > senderEvent;
};

#endif
