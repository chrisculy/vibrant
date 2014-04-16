/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vexception.h
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

#ifndef VIBRANT_EXCEPTION_H
#define VIBRANT_EXCEPTION_H

#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Provides a base class for all exceptions.
     * 
     * <p>
     * The convention for throwing Exception derived
     * exceptions is as follows:
     * <pre>
     * throw XXXException ( "SomeClass::SomeFunction - Here lies a problem." );
     * </pre>
     * </p>
     * 
     * @author Chris Culy
     */
    class VAPI Exception
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param message The exception's message.
             */
            Exception ( String message = null );

            /**
             * @brief Retrieves the exception's message.
             */
            String GetMessage ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the exception's message. */
            String message;
    };

    /**
     * @brief Exception that is thrown when
     * something is null that shouldn't be.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class NullPointerException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            NullPointerException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when
     * a function argument is invalid or illegal.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class IllegalArgumentException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            IllegalArgumentException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when an
     * illegal operation is attempted.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class IllegalOperationException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            IllegalOperationException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when
     * an index is out of an array's bounds.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class IndexOutOfBoundsException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            IndexOutOfBoundsException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when
     * trying to access (i.e. pop an
     * element from) an empty container structure.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class EmptyContainerException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            EmptyContainerException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when
     * an operation is attempted that is not supported.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class NotSupportedOperationException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            NotSupportedOperationException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when
     * a file I/O operation fails.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class FileIOException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            FileIOException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };
    
    /**
     * @brief Exception that is thrown when an error or
     * incorrect behavior occurs in the networking system.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class NetworkException : public Exception
    {
        public:

            /**
             * @see Exception#Exception(String)
             */
            NetworkException ( String message = null ) :
                Exception ( message )
            {
                /* stub function */
            }
    };

}

#endif
