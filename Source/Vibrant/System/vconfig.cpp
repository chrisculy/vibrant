/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vconfig.cpp
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

#include "vconfig.h"
#include "vhashtable.h"
#include "vlog.h"
#include "vstring.h"

namespace Vibrant
{
    
    Config::Config ( String filename )
    {
        this->filename = filename;
    }
    
    Config::~Config ()
    {
        /* stub function */
    }
    
    void Config::Load ()
    {
        std::ifstream inConfig;
        String tmp1, tmp2;
        
        if ( filename.Length () > 0 )
        {
            // Open the configuration file.
            inConfig.open ( filename.CString () );
            
            // Clear the current configuration.
            config.Clear ();
            
            // Load the configuration.
            while ( !inConfig.eof () )
            {
                inConfig >> tmp1 >> tmp2;
                config.Put ( tmp1, tmp2 );
            }
            
            // Close the configuration file.
            inConfig.close ();
        }
        else
        {
            //vlog << ERR << "Invalid file name.\n";
        }
        
        //vlog << INF << "Configuration file loaded.\n";
    }
    
    void Config::Save ()
    {
        std::ofstream outConfig;
        
        if ( filename.Length () > 0 )
        {
            // Open the configuration file.
            outConfig.open ( filename.CString () );
            
            // Save the configuration.
            for ( Hashtable< String, String >::Iterator< > iter = config.StartIterator (); iter != config.EndIterator (); iter.Next () )
            {
                outConfig << iter.GetKey ().CString () << " " << iter.GetValue ().CString () << "\n";
            }
            
            // Close the configuration file
            outConfig.close ();
        }
        else
        {
            //vlog << ERR << "Invalid file name.\n";
        }
        
        //vlog << INF << "Configuration file saved.\n";
    }
    
    void Config::SetProperty ( String name, String value )
    {
        // Find out if the property already exists.
        if ( config.Contains ( name ) )
        {
            // Overwrite the old value with the new value.
            config.Get ( name ) = value;
        }
        else
        {
            // Create the property and set its value.
            config.Put ( name, value );
        }
    }
    
    String Config::GetProperty ( String name )
    {
        // Make sure the property exists.
        if ( !config.Contains ( name ) )
        {
            //vlog << ERR << "Property (\"" << name << "\") does not exist!\n";
            
            // Return empty string and don't create
            // the property in the configuration.
            return "";
        }
        
        return config.Get ( name );
    }

}
