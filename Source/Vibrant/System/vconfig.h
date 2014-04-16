/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vconfig.h
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

#ifndef VIBRANT_CONFIG_H
#define VIBRANT_CONFIG_H

#include "vhashtable.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Allows for reading and writing a configuration file for the engine.
     * 
     * @author Chris Culy
     */
    class VAPI Config
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Config ( String filename = "vengine.cfg" );

            /**
             * @brief Destructor.
             */
            ~Config ();

            /**
             * @brief Loads the configuration file into the member variables.
             */
            void Load ();

            /**
             * @brief Saves the member variables to the file.
             */
            void Save ();

            /**
             * @brief Sets the property to the specified value.
             * 
             * <p>
             * If the property is not in the configuration, it is
             * added. If it already exists in the configuration,
             * the value is changed.
             * </p>
             * 
             * @param name The property's name.
             * @param value The property's value.
             */
            void SetProperty ( String name, String value );

            /**
             * @brief Retrieves the property with the given name.
             * 
             * @param name The name of the desired property.
             * @return The property's value.
             */
            String GetProperty ( String name );

            //************************ General Interface ***********************//

        private:
            
            /** @brief The filename of the configuration file. */
            String filename;

            /** @brief The configuration stored as a hash table. */
            Hashtable< String, String > config;
    };

}

#endif
