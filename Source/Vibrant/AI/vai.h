/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vai.h
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

#ifndef VIBRANT_AI_H
#define VIBRANT_AI_H

#include "vconfig.h"
#include "venginesystem.h"
#include "vpointer.h"
#include "vtimedupdater.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the artificial intelligence system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see TimedUpdater
     */
    class VAPI AI : public EngineSystem, public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration that the AI
             *      system uses to construct itself.
             */
            AI ( Config* config );

            /**
             * @brief Destructor.
             */
            ~AI ();

            /**
             * @brief Updates the AI system.
             * 
             * <p>
             * Note: must update only if DoUpdate () is true.
             * </p>
             * 
             * @see TimedUpdater#DoUpdate()
             * @see Updatable#Update()
             */
            virtual void Update ();
            
            //************************ General Interface ***********************//
    };
    
    typedef Pointer< AI > AIPtr;

}

#endif
