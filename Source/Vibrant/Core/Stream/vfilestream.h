/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vfilestream.h
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

#ifndef VIBRANT_FILESTREAM_H
#define VIBRANT_FILESTREAM_H

#include <fstream>
#include <sstream>

#include "vfile.h"
#include "vstream.h"

namespace Vibrant
{
    
    /**
     * @brief Implements streaming for files.
     * 
     * @see Stream
     * @author Chris Culy
     */
    class VAPI FileStream : public Stream
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructs a file stream from a filename(path).
             * 
             * @param filename The filename of the file for the stream.
             * @param mode The mode to use when opening the file.
             */
            FileStream ( const String& filename, const File::FileMode mode = File::FILE_READ_WRITE_TEXT );

            /**
             * @brief Constructs a file stream from a file object.
             * 
             * @param file The file to use.
             */
            FileStream ( File* file );

            /**
             * @brief Destructor.
             */
            ~FileStream ();

            /**
             * @see Stream#Read(byte*, int, int)
             */
            bool Read ( byte* buffer, const int& offset, const int& count );

            /**
             * @see Stream#Read(byte)
             */
            bool Read ( byte& data );

            /**
             * @see Stream#Write(byte*, int, int)
             */
            bool Write ( const byte* buffer, const int& offset, const int& count );

            /**
             * @see Stream#Write(byte)
             */
            bool Write ( const byte& data );

            /**
             * @see Stream#Flush()
             */
            void Flush ();

            /**
             * @see Stream#Close()
             */
            void Close ();

            /**
             * @see Stream#Seek(unsigned long, unsigned long)
             */
            unsigned long Seek ( const unsigned long& offset, const long& position = -1 );

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
            void SetLength ( unsigned long length );

            /**
             * * @see Stream#GetLength()
             */
            unsigned long GetLength ();

            /**
             * @see Stream#CanSeek()
             */
            bool CanSeek ();

            /**
             * @see Stream#CanRead()
             */
            bool CanRead ();

            /**
             * @see Stream#CanWrite()
             */
            bool CanWrite ();

            /**
             * @see Stream#CanTimeout()
             */
            bool CanTimeout ();

            /**
             * @see Stream#SetReadTimeout(long)
             */
            void SetReadTimeout ( long timeout );

            /**
             * @see Stream#SetWriteTimeout(long)
             */
            void SetWriteTimeout ( long timeout );

            /**
             * @see Stream#GetReadTimeout()
             */
            long GetReadTimeout ();

            /**
             * @see Stream#GetWriteTimeout()
             */
            long GetWriteTimeout ();

            //************************ General Interface ***********************//
            

            //*********************** Buffer I/O Operators **********************//

            /**
             * @see Stream#operator<< (unsigned short)
             */
            Stream& operator<< ( const unsigned short val );

            /**
             * @see Stream#operator<< (short)
             */
            Stream& operator<< ( const short val );

            /**
             * @see Stream#operator<< (unsigned int)
             */
            Stream& operator<< ( const unsigned int val );

            /**
             * @see Stream#operator<< (int)
             */
            Stream& operator<< ( const int val );

            /**
             * @see Stream#operator<< (unsigned long)
             */
            Stream& operator<< ( const unsigned long val );

            /**
             * @see Stream#operator<< (long)
             */
            Stream& operator<< ( const long val );

            /**
             * @see Stream#operator<< (float)
             */
            Stream& operator<< ( const float val );

            /**
             * @see Stream#operator<< (double)
             */
            Stream& operator<< ( const double val );

            /**
             * @see Stream#operator<< (bool)
             */
            Stream& operator<< ( const bool val );

            /**
             * @see Stream#operator<< (char)
             */
            Stream& operator<< ( const char val );

            /**
             * @see Stream#operator<< (String)
             */
            Stream& operator<< ( const String val );

            /**
             * @see Stream#operator>> (unsigned short)
             */
            Stream& operator>> ( unsigned short& val );

            /**
             * @see Stream#operator>> (short)
             */
            Stream& operator>> ( short& val );

            /**
             * @see Stream#operator>> (unsigned int)
             */
            Stream& operator>> ( unsigned int& val );

            /**
             * @see Stream#operator>> (int)
             */
            Stream& operator>> ( int& val );

            /**
             * @see Stream#operator>> (unsigned long)
             */
            Stream& operator>> ( unsigned long& val );

            /**
             * @see Stream#operator>> (long)
             */
            Stream& operator>> ( long& val );

            /**
             * @see Stream#operator>> (float)
             */
            Stream& operator>> ( float& val );

            /**
             * @see Stream#operator>> (double)
             */
            Stream& operator>> ( double& val );

            /**
             * @see Stream#operator>> (bool)
             */
            Stream& operator>> ( bool& val );

            /**
             * @see Stream#operator>> (char)
             */
            Stream& operator>> ( char& val );

            /**
             * @see Stream#operator>> (String)
             */
            Stream& operator>> ( String& val );

            //*********************** Buffer I/O Operators **********************//

        private:
            
            /** @brief Holds the underlying file. */
            File* file;

            /** @brief Holds the file stream's length. */
            unsigned long length;

            /** @brief Whether the stream owns the file or not. */
            bool ownsFile;
    };

}

#endif
