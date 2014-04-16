/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunit.h
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

#ifndef VIBRANT_UNIT_H
#define VIBRANT_UNIT_H

#include "varray.h"
#include "vstring.h"
#include "vunitability.h"
#include "vunitstat.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a unit or character in a game.
     * 
     * @author Chris Culy
     */
    class Unit
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Contructor.
             */
            Unit ( String name );

            /**
             * @brief Destructor.
             */
            virtual ~Unit ();

            /**
             * @brief Updates the stats, abilities, and graphics for the unit.
             */
            virtual void Update ();

            /**
             * @brief Searches for the specified stat.
             * 
             * @param name The name of the wanted stat.
             * @return The index of the stat, or -1 if not found.
             */
            int SearchStat ( String name );

            /**
             * @brief Searches for the specified ability.
             * 
             * @param name The name of the wanted ability.
             * @return The index of the ability, or -1 if not found.
             */
            int SearchAbility ( String name );

            /**
             * @brief Sets the unit's name.
             * 
             * @param name The unit's new name.
             */
            void SetName ( String name );

            /**
             * @brief Adds the stat with the specified parameters.
             * 
             * @param name The name of the stat.
             * @param total The total value for the stat.
             * @param value The actual value for the stat.
             * @return <code>true</code> if the stat was successfully
             *      added; <code>false</code> otherwise.
             */
            bool AddStat ( String name, double total, double value );

            /**
             * @brief Adds the ability with the specified parameters.
             * 
             * @param name The name of the ability.
             * @param limit The limit type for the ability.
             * @return <code>true</code> if the ability was successfully
             *      added; <code>false</code> otherwise.
             */
            bool AddAbility ( String name, UnitAbilityLimit limit );

            /**
             * @brief Retrieves the unit's name.
             * 
             * @return The unit's name.
             */
            String GetName ();

            /**
             * @brief Retrieves the specified stat (if it exists).
             * 
             * @param name The name of the wanted stat.
             * @return The specified stat or <code>null</code>.
             */
            UnitStat* GetStat ( String name );

            /**
             * @brief Retrieves the specified ability (if it exists).
             * 
             * @param name The name of the wanted ability.
             * @return The specified ability or <code>null</code>.
             */
            UnitAbility* GetAbility ( String name );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the name of the unit. */
            String name;

            /** @brief Holds the stats of the unit. */
            Array< UnitStat* > stat;

            /** @brief Holds the abilities of the unit. */
            Array< UnitAbility* > ability;
    };

}

#endif
