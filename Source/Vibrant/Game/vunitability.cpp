/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunitability.cpp
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

#include "vexception.h"
#include "vstring.h"
#include "vunitability.h"
#include "vunitstat.h"

namespace Vibrant
{
    
    UnitAbility::UnitAbility ( String abilityName, UnitAbilityLimit limit )
    {
        // Make sure that the limit is a reasonable value.
        if ( limit < 0 || limit > 5 )
        {
            this->limit = STAT_GREATER_THAN_EQUAL;
        }
        else
        {
            this->limit = limit;
        }
        this->abilityName = abilityName;
    }
    
    UnitAbility::~UnitAbility ()
    {
        if ( stat.stat )
        {
            stat.stat = null;
        }
        if ( tarGetStat.stat )
        {
            tarGetStat.stat = null;
        }
    }
    
    void UnitAbility::SetAbilityName ( String abilityName )
    {
        this->abilityName = abilityName;
    }
    
    void UnitAbility::SetLimit ( UnitAbilityLimit limit )
    {
        this->limit = limit;
    }
    
    void UnitAbility::SetTimeLimit ( long timeLimit )
    {
        this->timeLimit = timeLimit;
    }
    
    void UnitAbility::SetStat ( UnitStat* stat )
    {
        if ( stat == null )
        {
            throw NullPointerException ( "UnitAbility::SetStat - Stat pointer was null." );
        }
        this->stat.stat = stat;
    }
    
    void UnitAbility::SetTargetStat ( UnitStat* stat )
    {
        if ( stat == null )
        {
            throw NullPointerException ( "UnitAbility::SetTarGetStat - Target stat pointer was null." );
        }
        this->tarGetStat.stat = stat;
    }
    
    String UnitAbility::GetAbilityName ()
    {
        return abilityName;
    }
    
    UnitAbilityLimit UnitAbility::GetLimit ()
    {
        return limit;
    }
    
    long UnitAbility::GetTimeLimit ()
    {
        return timeLimit;
    }
    
    UnitStat* UnitAbility::GetStat ()
    {
        return this->stat.stat;
    }
    
    UnitStat* UnitAbility::GetTargetStat ()
    {
        return this->tarGetStat.stat;
    }

}
