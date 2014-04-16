/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vpointable.h
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

#ifndef VIBRANT_POINTABLE_H
#define VIBRANT_POINTABLE_H

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief This is an interface for objects that allow smart pointers to themselves.
     * 
     * @author Chris Culy
     * @see Pointer
     */
    class VAPI Pointable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Destructor.
             */
            virtual ~Pointable ();

            /**
             * @brief Increments the reference count on this object.
             */
            virtual void AddReference ();

            /**
             * @brief Decrements the reference count on this object.
             * 
             * <p>
             * When the reference count reaches zero, the object
             * is deleted.
             * </p>
             */
            virtual void RemoveReference ();

            /**
             * @brief Retrieves the number of active references to this
             * object that currently exist.
             *
             * @return The number of active references.
             */
            virtual int ReferenceCount () const;

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * <p>
             * Made protected to disallow instantiation of this class since this
             * class is meant to be used only as an interface.
             * </p>
             */
            Pointable ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the number of references to this object. */
            int referenceCount;
    };

}

#endif
