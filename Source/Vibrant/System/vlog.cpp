/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vlog.cpp
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

namespace Vibrant
{
    VAPI Log vlog;
    
    Log::Log ( String filename )
    {
        // Set the log file's file name
        SetFilename ( filename );
        
        // Open log file and clear it
        logFile.open ( filename.CString (), std::ios::trunc );
        logFile.close ();
        logFile.open ( filename.CString (), std::ios::app );
    }
    
    Log::~Log ()
    {
        // Close the log file
        logFile.close ();
    }
    
    Log& Log::operator<< ( const LogMessageType type )
    {
        // Determine the message type
        switch ( type )
        {
            case INF: // Print an information message label
                logFile << "INFORMATION: ";
                break;
            case WARN: // Print a warning message label
                logFile << "WARNING: ";
                break;
            case ERR: // Print an error message label
                logFile << "ERROR: ";
                break;
            default:
                break;
        }

        // Make sure the log file is up to date
        logFile.flush ();
        return *this;
    }
    
    Log& Log::operator<< ( const String val )
    {
        logFile << val.CString ();
        logFile.flush ();
        return *this;
    }
    
    Log& Log::operator<< ( const int val )
    {
        logFile << val;
        logFile.flush ();
        return *this;
    }
    
    Log& Log::operator<< ( const long val )
    {
        logFile << val;
        logFile.flush ();
        return *this;
    }
    
    Log& Log::operator<< ( const float val )
    {
        logFile << val;
        logFile.flush ();
        return *this;
    }
    
    Log& Log::operator<< ( const double val )
    {
        logFile << val;
        logFile.flush ();
        return *this;
    }
    
    void Log::SetFilename ( String filename )
    {
        this->filename = filename;
    }

}
