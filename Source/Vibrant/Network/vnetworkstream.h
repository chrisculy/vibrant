/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworkstream.h
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

#ifndef VIBRANT_NETWORKSTREAM_H
#define VIBRANT_NETWORKSTREAM_H

#include "vstream.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Provides data streaming functionality over a network connection.
     * 
     * @author Chris Culy
     */
    class VAPI NetworkStream : public Stream
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            NetworkStream ();

            /**
             * @brief Destructor.
             */
            virtual ~NetworkStream ();

            /**
             * @see Stream#Read(byte*, int, int)
             */
            bool Read ( byte* buffer, const int& offset, const int& count );

            /**
             * @see Stream#Read(byte)
             */
            virtual bool Read ( byte& data );

            /**
             * @see Stream#Write(byte*, int, int)
             */
            virtual bool Write ( const byte* buffer, const int& offset, const int& count );

            /**
             * @see Stream#Write(byte)
             */
            virtual bool Write ( const byte& data );

            /**
             * @see Stream#Flush()
             */
            virtual void Flush ();

            /**
             * @see Stream#Close()
             */
            virtual void Close ();

            /**
             * @see Stream#Seek(long, long)
             */
            virtual unsigned long Seek ( const unsigned long& offset, const long& position = 0 );

            /**
             * @see Stream#SetPosition(unsigned long)
             */
            void SetPosition ( const unsigned long& position );

            /**
             * @see Stream#GetPosition()
             */
            unsigned long GetPosition ();

            /**
             * @see Stream#SetLength(unsigned long)
             */
            virtual void SetLength ( unsigned long length );

            /**
             * * @see Stream#GetLength()
             */
            virtual unsigned long GetLength ();

            /**
             * @see Stream#CanSeek()
             */
            virtual bool CanSeek ();

            /**
             * @see Stream#CanRead()
             */
            virtual bool CanRead ();

            /**
             * @see Stream#CanWrite()
             */
            virtual bool CanWrite ();

            /**
             * @see Stream#CanTimeout()
             */
            virtual bool CanTimeout ();

            /**
             * @see Stream#SetReadTimeout(long)
             */
            virtual void SetReadTimeout ( long timeout );

            /**
             * @see Stream#SetWriteTimeout(long)
             */
            virtual void SetWriteTimeout ( long timeout );

            /**
             * @see Stream#GetReadTimeout()
             */
            virtual long GetReadTimeout ();

            /**
             * @see Stream#GetWriteTimeout()
             */
            virtual long GetWriteTimeout ();

            //************************ General Interface ***********************//
            

            //*********************** Buffer I/O Operators **********************//

            /**
             * @see Stream#operator<< (unsigned short)
             */
            virtual Stream& operator<< ( const unsigned short val );

            /**
             * @see Stream#operator<< (short)
             */
            virtual Stream& operator<< ( const short val );

            /**
             * @see Stream#operator<< (unsigned int)
             */
            virtual Stream& operator<< ( const unsigned int val );

            /**
             * @see Stream#operator<< (int)
             */
            virtual Stream& operator<< ( const int val );

            /**
             * @see Stream#operator<< (unsigned long)
             */
            virtual Stream& operator<< ( const unsigned long val );

            /**
             * @see Stream#operator<< (long)
             */
            virtual Stream& operator<< ( const long val );

            /**
             * @see Stream#operator<< (float)
             */
            virtual Stream& operator<< ( const float val );

            /**
             * @see Stream#operator<< (double)
             */
            virtual Stream& operator<< ( const double val );

            /**
             * @see Stream#operator<< (bool)
             */
            virtual Stream& operator<< ( const bool val );

            /**
             * @see Stream#operator<< (char)
             */
            virtual Stream& operator<< ( const char val );

            /**
             * @see Stream#operator<< (String)
             */
            virtual Stream& operator<< ( const String val );

            /**
             * @see Stream#operator>> (unsigned short)
             */
            virtual Stream& operator>> ( unsigned short& val );
            /**
             * @see Stream#operator>> (short)
             */
            virtual Stream& operator>> ( short& val );

            /**
             * @see Stream#operator>> (unsigned int)
             */
            virtual Stream& operator>> ( unsigned int& val );

            /**
             * @see Stream#operator>> (int)
             */
            virtual Stream& operator>> ( int& val );

            /**
             * @see Stream#operator>> (unsigned long)
             */
            virtual Stream& operator>> ( unsigned long& val );

            /**
             * @see Stream#operator>> (long)
             */
            virtual Stream& operator>> ( long& val );

            /**
             * @see Stream#operator>> (float)
             */
            virtual Stream& operator>> ( float& val );

            /**
             * @see Stream#operator>> (double)
             */
            virtual Stream& operator>> ( double& val );

            /**
             * @see Stream#operator>> (bool)
             */
            virtual Stream& operator>> ( bool& val );

            /**
             * @see Stream#operator>> (char)
             */
            virtual Stream& operator>> ( char& val );

            /**
             * @see Stream#operator>> (String)
             */
            virtual Stream& operator>> ( String& val );

            //*********************** Buffer I/O Operators **********************//

        protected:
            
            /** @brief Holds the read timeout. */
            long readTimeout;

            /** @brief Holds the write timeout. */
            long writeTimeout;
    };

}

#endif
