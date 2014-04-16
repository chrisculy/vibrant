/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunitstatcontrol.h
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

#ifndef VIBRANT_UNITSTATCONTROL_H
#define VIBRANT_UNITSTATCONTROL_H

#include "vunitstat.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the different ways to modify a unit's stat.
     */
    enum UnitStatModType
    {
        ADDITION = 0,
        SUBTRACTION = 1,
        MULTIPLICATION = 2,
        DIVISION = 3
    };
    
    /**
     * @brief Encapsulates the ability to control
     * and modify a unit's stat.
     * 
     * @author Chris Culy
     */
    struct UnitStatControl
    {
            /** @brief The statistic that will be modified. */
            UnitStat* stat;

            /** @brief The type of modification being done on
             * the stat (addition, subtraction, etc.). */
            UnitStatModType mod;

            /** @brief The value to modify with. */
            int modVal;
    };

}

#endif
