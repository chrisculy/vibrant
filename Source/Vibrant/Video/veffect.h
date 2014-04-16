/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: veffect.h
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

#ifndef VIBRANT_EFFECT_H
#define VIBRANT_EFFECT_H

#include "vobject.h"
#include "vpointer.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a 3D effect (such as texturing,
     * reflection, parallax occlusion mapping).
     * 
     * <p>
     * Note: Effect derived class need to implement
     * the streaming operators.
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI Effect : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Effect ();

            /**
             * @brief Destructor.
             */
            ~Effect ();

            //************************ General Interface ***********************//
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all effects.
             * 
             * @return The Effect RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//
            

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
    };
    
    typedef Pointer< Effect > EffectPtr;

}

#endif
