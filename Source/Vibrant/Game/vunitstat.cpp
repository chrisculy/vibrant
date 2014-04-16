/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunitstat.cpp
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

#include "vstring.h"
#include "vunitstat.h"

namespace Vibrant
{
    
    UnitStat::UnitStat ( String statName, double total, double value )
    {
        this->statName = statName;
        this->total = total;
        this->value = value;
    }
    
    UnitStat::~UnitStat ()
    {
        /* stub function */
    }
    
    void UnitStat::SetStatName ( String statName )
    {
        this->statName = statName;
    }
    
    void UnitStat::SetTotal ( double total )
    {
        this->total = total;
    }
    
    void UnitStat::SetValue ( double value )
    {
        this->value = value;
    }
    
    String UnitStat::GetStatName ()
    {
        return statName;
    }
    
    double UnitStat::GetTotal ()
    {
        return total;
    }
    
    double UnitStat::GetValue ()
    {
        return value;
    }

}
