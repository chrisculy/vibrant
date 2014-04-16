/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrtti.h
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

#ifndef VIBRANT_RTTI_H
#define VIBRANT_RTTI_H

#include "varray.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Provides a run time type information/identification system.
     * 
     * <p>
     * Classes that use this system must have a
     * <code>virtual const RTTI* GetType()</code> function and a
     * <code>static RTTI* GetRTTI()</code> function.
     * </p>
     * 
     * @see Object
     * @author Chris Culy
     */
    class VAPI RTTI
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs an RTTI object with the specified name
             * and list of base class types.
             *
             * @param name The name for the new type.
             * @param baseTypes The base classes for the new type.
             * @throws IllegalArgumentException If name is not unique.
             */
            RTTI ( String name = "", Array< RTTI* > baseTypes = *( new Array< RTTI* > () ) );

            /**
             * @brief Destructor.
             */
            ~RTTI ();

            /**
             * @brief Returns this type's name.
             * 
             * @return The type's name.
             */
            const String& GetName () const;

            /**
             * @brief Returns this type's base types.
             * 
             * @return The type's base types.
             */
            const Array< RTTI* >& GetBaseTypes () const;

            /**
             * @brief Tests the two RTTI objects for equality.
             * 
             * @param rtti The RTTI object to test for equality.
             * @return <code>true</code> if the two objects are
             *      equal;<code>false</code> otherwise.
             */
            bool operator== ( const RTTI rtti ) const;

            /**
             * @brief Tests the two RTTI objects for inequality.
             * 
             * @param rtti The RTTI object to test for inequality.
             * @return <code>true</code> if the two objects are
             *      not equal;<code>false</code> otherwise.
             */
            bool operator!= ( const RTTI rtti ) const;

            /**
             * @brief Returns whether this type is exactly equal
             * to the specified type or not.
             * 
             * @param type The type to compare to.
             * @return <code>true</code> if <code>this</code> is exactly equal to
             *        <code>type</code>; <code>false</code> otherwise.
             */
            bool IsExactly ( const RTTI* type ) const;

            /**
             * @brief Returns whether this type is derived
             * from the specified type or not, or if it is equal.
             * 
             * @param type The type to compare to.
             * @return <code>true</code> if <code>this</code> is derived from
             *        <code>type</code>; <code>false</code> otherwise.
             */
            bool IsDerived ( const RTTI* type ) const;

            //************************ General Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @brief Retrieves the number of bytes used to stream this object.
             * This allows for streaming of run time type information
             * along with the object that is streamed.
             *
             * @return The number of bytes used to stream this object.
             */
            int GetBytesUsed ();

            //************************ Streaming system ************************//

        private:
            
            /** @brief Holds all the RTTI unique names. */
            static Array< String > rttiNames;

            /** @brief The unique name for this RTTI object. */
            String name;

            /** @brief All the base (or parent) RTTI types. */
            Array< RTTI* > baseTypes;
    };

}

#endif
