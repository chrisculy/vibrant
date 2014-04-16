/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vlog.h
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

#ifndef VIBRANT_LOG_H
#define VIBRANT_LOG_H

#include <fstream>

#include "vstring.h"

// ------------------------------------------------------------------------- //
// -- Disable warning about std::ofstream not being exported to the DLL. --- //

#if defined (_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

// --------------------------------- Begin --------------------------------- //
// ------------------------------------------------------------------------- //

namespace Vibrant
{
    
    /**
     * @brief Used by Log to format messages.
     * 
     * <p>
     * Format modes (message types):
     * <code>INF</code> - Information,
     * <code>WARN</code> - Warning,
     * <code>ERR</code> - Error.
     * </p>
     */
    enum LogMessageType
    {
        INF,
        WARN,
        ERR
    };
    
    /**
     * @brief Encapsulates logging capabilities for program
     * information, warnings, and errors.
     *
     * @author Chris Culy
     */
    class VAPI Log
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Log ( String filename = "output.log" );

            /**
             * @brief Destructor.
             */
            virtual ~Log ();

            /**
             * @brief Sets the filename to vlog messages to.
             * 
             * @param filename The specified filename.
             */
            void SetFilename ( const String filename );

            //************************ General Interface ***********************//
            

            //************************ Output Operators ************************//

            /**
             * @brief Sets the message type and does some minimal formatting.
             * 
             * @param type The desired message type.
             */
            Log& operator<< ( const LogMessageType type );

            /**
             * @brief Writes a string to the vlog file.
             * 
             * @param val The string to write to the vlog file.
             * @return A reference to the logger.
             */
            Log& operator<< ( const String val );

            /**
             * @brief Writes an integer to the vlog file.
             * 
             * @param val The value to write to the vlog file.
             * @return A reference to the logger.
             */
            Log& operator<< ( const int val );

            /**
             * @brief Writes a long integer to the vlog file.
             * 
             * @param val The value to write to the vlog file.
             * @return A reference to the logger.
             */
            Log& operator<< ( const long val );

            /**
             * @brief Writes a normal floating point number to the vlog file.
             * 
             * @param val The value to write to the vlog file.
             * @return A reference to the logger.
             */
            Log& operator<< ( const float val );

            /**
             * @brief Writes a double precision floating point number to the vlog file.
             * 
             * @param val The value to write to the vlog file.
             * @return A reference to the logger.
             */
            Log& operator<< ( const double val );

            //************************ Output Operators ************************//

        private:
            
            /** @brief The file stream to vlog messages to. */
            std::ofstream logFile;

            /** @brief The file name (may or may not be a resolved file path). */
            String filename;
    };

}

// ------------------------------------------------------------------------- //
// -- Disable warning about std::ofstream not being exported to the DLL. --- //

#if defined (_MSC_VER)
#pragma warning(pop)
#endif

// ---------------------------------- End ---------------------------------- //
// ------------------------------------------------------------------------- //

#endif
