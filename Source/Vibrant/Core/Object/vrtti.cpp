/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vrtti.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "varray.h"
#include "vexception.h"
#include "vrtti.h"
#include "vstring.h"

namespace Vibrant
{
    
    // Initialize static members.
    Array< String > RTTI::rttiNames;
    
    RTTI::RTTI ( String name, Array< RTTI* > baseTypes )
    {
        // If the name is not empty, validate its uniqueness
        // and add it to the unique names list.
        if ( name != "" )
        {
            // Make sure the name is unique.
            int nameCount = RTTI::rttiNames.Size ();
            for ( int i = 0; i < nameCount; i++ )
            {
                if ( name == RTTI::rttiNames[ i ] )
                {
                    throw IllegalArgumentException ( "RTTI::RTTI - RTTI name was not unique." );
                }
            }
            
            // Add the name to the list of unique names.
            RTTI::rttiNames.Push ( name );
        }

        this->name = name;
        this->baseTypes = baseTypes;
    }
    
    RTTI::~RTTI ()
    {
        /* stub function */
    }
    
    const String& RTTI::GetName () const
    {
        return this->name;
    }
    
    const Array< RTTI* >& RTTI::GetBaseTypes () const
    {
        return this->baseTypes;
    }
    
    bool RTTI::operator== ( const RTTI rtti ) const
    {
        // Check if the names are equal.
        if ( this->name == rtti.GetName () )
        {
            // Check if all the base types are equal.
            // Technically, this need not be done since
            // all names are unique, but we do it to make sure.
            if ( this->baseTypes.Size () != 0 && rtti.GetBaseTypes ().Size () != 0 )
            {
                Array< RTTI* > rttiBaseTypes = rtti.GetBaseTypes ();
                int baseTypeCount = this->baseTypes.Size ();
                bool equal = true;
                for ( int i = 0; i < baseTypeCount; i++ )
                {
                    if ( !( ( *this->baseTypes[ i ] ) == ( *rttiBaseTypes[ i ] ) ) )
                    {
                        equal = false;
                    }
                }
                return equal;
            }
            else
            {
                return this->baseTypes.Size () == rtti.GetBaseTypes ().Size ();
            }
        }
        else
        {
            return false;
        }
    }
    
    bool RTTI::operator!= ( const RTTI rtti ) const
    {
        return !( *this == rtti );
    }
    
    bool RTTI::IsExactly ( const RTTI* type ) const
    {
        return *this == *type;
    }
    
    bool RTTI::IsDerived ( const RTTI* type ) const
    {
        // If this type is equal to the given type, return true.
        if ( *this == *type )
        {
            return true;
        }
        
        // Test if any of this type's base types are
        // equal to the given type.
        else
        {
            bool isDerivedType = false;
            int baseTypeCount = this->baseTypes.Size ();
            for ( int i = 0; i < baseTypeCount; i++ )
            {
                if ( ( *this->baseTypes[ i ] ) == ( *type ) )
                {
                    isDerivedType = true;
                }
            }
            return isDerivedType;
        }
    }
    
    int RTTI::GetBytesUsed ()
    {
        /* stub function */
        return 0;
    }

}
