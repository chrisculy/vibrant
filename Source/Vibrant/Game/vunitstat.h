/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vunitstat.h
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

#ifndef VIBRANT_UNITSTAT_H
#define VIBRANT_UNITSTAT_H

#include "vobject.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a unit or character's stat or attribute.
     * 
     * @author Chris Culy
     */
    class UnitStat : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param statName The name of the stat.
             * @param total The total value of the stat.
             * @param value The actual (current) value of the stat
             *      (this would just specify the initial value).
             */
            UnitStat ( String statName, double total = 100.0, double value = 100.0 );

            /**
             * @brief Destructor.
             */
            ~UnitStat ();

            /**
             * @brief Sets the stat's name.
             * 
             * @param statName The stat's new name.
             */
            void SetStatName ( String statName );

            /**
             * @brief Sets the stat's total value.
             * 
             * @param total The stat's new total value.
             */
            void SetTotal ( double total );

            /**
             * @brief Sets the stat's actual (current) value.
             * 
             * @param value The stat's new actual (current) value.
             */
            void SetValue ( double value );

            /**
             * @brief Retrieves the stat's name.
             * 
             * @return The stat's name.
             */
            String GetStatName ();

            /**
             * @brief Retrieves the stat's total value.
             * 
             * @returns The stat's total value.
             */
            double GetTotal ();

            /**
             * @brief Retrieves the stat's actual (current) value.
             * 
             * @return The stat's actual (current) value.
             */
            double GetValue ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the name of the stat. */
            String statName;

            /** @brief Holds the total value of stat. */
            double total;

            /** @brief Holds the actual (current) value of the stat. */
            double value;
    };

}

#endif
