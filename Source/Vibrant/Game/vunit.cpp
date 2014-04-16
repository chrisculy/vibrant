/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunit.cpp
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

#include "vlog.h"
#include "vstring.h"
#include "vunit.h"
#include "vunitability.h"
#include "vunitstat.h"

namespace Vibrant
{
    
    Unit::Unit ( String name )
    {
        this->name = name;
    }
    
    Unit::~Unit ()
    {
        stat.Clear ();
        ability.Clear ();
    }
    
    void Unit::Update ()
    {
        /* stub function */
    }
    
    int Unit::SearchStat ( String name )
    {
        /* stub function */
        return -1;
    }
    
    int Unit::SearchAbility ( String name )
    {
        /* stub function */
        return -1;
    }
    
    void Unit::SetName ( String name )
    {
        /* stub function */
    }
    
    bool Unit::AddStat ( String name, double total, double value )
    {
        /* stub function */
        if ( SearchStat ( name ) > -1 )
        {
            //            if ( --stat variable is full-- )
            //            {
            //                //extend the variable
            //            }
            //            stat[whichever element] = UnitStat ( name, total, value );
            return true;
        }
        
        return false;
    }
    
    bool Unit::AddAbility ( String name, UnitAbilityLimit limit )
    {
        /* stub function */
        if ( SearchAbility ( name ) > -1 )
        {
            //            if ( --ability variable is full-- ) 
            //            {
            //                //extend the variable
            //            }
            //            ability[whichever element] = UnitAbility ( name, limit );
            return true;
        }
        
        return false;
    }
    
    String Unit::GetName ()
    {
        return name;
    }
    
    UnitStat* Unit::GetStat ( String name )
    {
        if ( int index = SearchStat ( name ) > -1 ) 
        {
            return stat[ index ];
        }
        
        //vlog << ERR << "Unit::GetStat()-could not find requested statistic.\n";
        return null;
    }
    
    UnitAbility* Unit::GetAbility ( String name )
    {
        int index = SearchAbility ( name );
        if ( index > -1 )
        {
            return ability[ index ];
        }
        
        //vlog << ERR  << "Unit::getAbility()-could not find requested ability.\n";
        return null;
    }

}
