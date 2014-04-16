/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunitability.h
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

#ifndef VIBRANT_UNITABILITY_H
#define VIBRANT_UNITABILITY_H

#include "vobject.h"
#include "vstring.h"
#include "vunitstat.h"
#include "vunitstatcontrol.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the type of 
     * limit of a unit's ability.
     */
    enum UnitAbilityLimit
    {
        /** @brief Statistic: less than x. */
        STAT_LESS_THAN = 0,
        
        /** @brief Statistic: less than or equal to x. */
        STAT_LESS_THAN_EQUAL = 1,
        
        /** @brief Statistic: equal to x. */
        STAT_EQUAL = 2,
        
        /** @brief Statistic: greater than or equal to x. */
        STAT_GREATER_THAN_EQUAL = 3,
        
        /** @brief Statistic: greater than x. */
        STAT_GREATER_THAN = 4,
        
        /** @brief Time: has a time limit. */
        TIME = 5
    };
    
    /**
     * @brief Encapsulates the type of action a
     * unit's ability represents.
     */
    enum UnitAbilityAction
    {
        MODIFY_OBJECT = 0,
        HARVEST_OBJECT = 1,
        CREATE_OBJECT = 2,
        MOVE_OBJECT = 3
    };
    
    /**
     * @brief Represents a unit or character's ability.
     * 
     * @author Chris Culy
     */
    class UnitAbility : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param abilityName The name of the ability.
             * @param limit The limit type of the ability (time, stat, etc.).
             */
            UnitAbility ( String abilityName, UnitAbilityLimit limit = STAT_GREATER_THAN_EQUAL );

            /**
             * @brief Destructor.
             */
            ~UnitAbility ();

            /**
             * @brief Sets the ability's name.
             * 
             * @param abilityName The ability's new name.
             */
            void SetAbilityName ( String abilityName );

            /**
             * @brief Sets the ability's limit.
             * 
             * @param limit The ability's new limit.
             */
            void SetLimit ( UnitAbilityLimit limit );

            /**
             * @brief Sets the ability's time limit.
             * 
             * @param timeLimit The ability's new time limit.
             */
            void SetTimeLimit ( long timeLimit );

            /**
             * @brief Sets the unit's stat that the ability modifies.
             * 
             * @param stat The unit's stat that the ability will modify;
             *      must not be null.
             * @throws NullPointerException If stat is null.
             */
            void SetStat ( UnitStat* stat );

            /**
             * @brief Sets the target's stat that the ability modifies.
             * 
             * @param stat The target's stat that ability will modify;
             *      must not be null.
             * @throws NullPointerException If stat is null.
             */
            void SetTargetStat ( UnitStat* stat );

            /**
             * @brief Retrieves the ability's name.
             * 
             * @return The ability's name.
             */
            String GetAbilityName ();

            /**
             * @brief Retrieves the ability's limit type
             * (time limit, stat limit, etc.).
             *
             * @return The ability's limit.
             */
            UnitAbilityLimit GetLimit ();

            /**
             * @brief Retrieves the time limit of the ability
             * if it exists.
             * 
             * @returns The time limit of the ability.
             */
            long GetTimeLimit ();

            /**
             * @brief Retrieves the unit's stat that the
             * ability modifies.
             * 
             * @return The unit's stat that the ability modifies.
             */
            UnitStat* GetStat ();

            /**
             * @brief Retrieves the target's stat that the
             * ability modifies.
             * 
             * @return The target's stat that the ability modifies.
             */
            UnitStat* GetTargetStat ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the name of the ability. */
            String abilityName;

            /** @brief Holds the limit on the ability (time, statistic, etc.). */
            UnitAbilityLimit limit;

            /** @brief Holds the action performed when the ability is used. */
            UnitAbilityAction action;

            /** @brief Holds the unit stat that is modified or required
             * by the ability and how it is modified. */
            UnitStatControl stat;

            /** @brief Holds the target's statistic that is modified
             * and how it is modified. */
            UnitStatControl tarGetStat;

            /** @brief Holds the number of the animation to use during this
             * ability (-1 if there is no specific animation). */
            int animID;

            /** @brief Holds the time limit of the ability 
             * (if it has one) in milliseconds. */
            long timeLimit;
    };

}

#endif
