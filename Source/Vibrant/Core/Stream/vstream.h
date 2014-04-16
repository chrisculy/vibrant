/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vstream.h
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

#ifndef VIBRANT_STREAM_H
#define VIBRANT_STREAM_H

#include "vexception.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Defines the streaming system.
     * 
     * @see Object
     * @author Chris Culy
     */
    class VAPI Stream
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Stream ();

            /**
             * @brief Destructor.
             */
            virtual ~Stream ();

            /**
             * @brief Reads the data from the stream.
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to read into the buffer.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise.
             * @throws NotSupportedOperationException If the stream cannot read.
             */
            virtual bool Read ( byte* buffer, const int& offset, const int& count ) = 0;

            /**
             * @brief Reads a byte of data from the stream.
             * 
             * @param data A reference to where the read byte will be stored.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise.
             * @throws NotSupportedOperationException If the stream cannot read.
             */
            virtual bool Read ( byte& data ) = 0;

            /**
             * @brief Writes the data to the stream.
             * 
             * @param buffer The buffer to write data from.
             * @param offset The offset into the buffer.
             * @param count The number of bytes to write from the buffer.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             * @throws NotSupportedOperationException If the stream cannot write.
             */
            virtual bool Write ( const byte* buffer, const int& offset, const int& count ) = 0;

            /**
             * @brief Writes a byte of data to the stream.
             * 
             * @param data A reference to the byte to be written out.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             * @throws NotSupportedOperationException If the stream cannot write.
             */
            virtual bool Write ( const byte& data ) = 0;

            /**
             * @brief Flushes the stream.
             */
            virtual void Flush () = 0;

            /**
             * @brief Closes the stream.
             */
            virtual void Close () = 0;

            /**
             * @brief Seeks to the given position within the stream.
             * 
             * @param offset The offset from the starting position.
             * @param position The starting position to seek from 
             *      (-1 indicates the current position).
             * @throws NotSupportedOperationException If the stream cannot seek.
             */
            virtual unsigned long Seek ( const unsigned long& offset, const long& position = -1 ) = 0;

            /**
             * @brief Sets the current position within the stream.
             * 
             * <p>
             * Note: this will clamp the position to valid values.
             * </p>
             * 
             * @param position The desired position.
             * @throws NotSupportedOperationException If the stream cannot seek.
             */
            virtual void SetPosition ( const unsigned long& position ) = 0;

            /**
             * @brief Retrieves the current position within the stream.
             * 
             * @return The current stream position.
             * @throws NotSupportedOperationException If the stream cannot seek.
             */
            virtual unsigned long GetPosition () = 0;

            /**
             * @brief Sets the length of the stream.
             * 
             * <p>
             * Note: This may be an expensive operation.
             * </p>
             * 
             * @param length The length of the stream in bytes.
             * @throws NotSupportedOperationException If the stream cannot seek.
             */
            virtual void SetLength ( unsigned long length ) = 0;

            /**
             * @brief Gets the length of the stream.
             * 
             * @return The length of the stream in bytes.
             * @throws NotSupportedOperationException If the stream cannot seek.
             */
            virtual unsigned long GetLength () = 0;

            /**
             * @brief Retrieves whether the stream supports seeking.
             * 
             * @return <code>true</code> if the stream supports
             *      seeking;<code>false</code> otherwise.
             */
            virtual bool CanSeek () = 0;

            /**
             * @brief Retrieves whether the stream supports reading.
             * 
             * @return <code>true</code> if the stream supports
             *      reading;<code>false</code> otherwise.
             */
            virtual bool CanRead () = 0;

            /**
             * @brief Retrieves whether the stream supports writing.
             * 
             * @return <code>true</code> if the stream supports
             *      writing;<code>false</code> otherwise.
             */
            virtual bool CanWrite () = 0;

            /**
             * @brief Retrieves whether the stream can timeout.
             * 
             * @return <code>true</code> if the stream can
             *      timeout;<code>false</code> otherwise.
             */
            virtual bool CanTimeout () = 0;

            /**
             * @brief Sets the timeout for reading.
             * 
             * @param timeout The timeout for reading (in milliseconds).
             * @throws NotSupportedOperationException If the stream cannot timeout.
             */
            virtual void SetReadTimeout ( long timeout ) = 0;

            /**
             * @brief Sets the timeout for writing.
             * 
             * @param timeout The timeout for writing (in milliseconds).
             * @throws NotSupportedOperationException If the stream cannot timeout.
             */
            virtual void SetWriteTimeout ( long timeout ) = 0;

            /**
             * @brief Gets the timeout for reading.
             * 
             * @return The timeout for reading (in milliseconds).
             * @throws NotSupportedOperationException If the stream cannot timeout.
             */
            virtual long GetReadTimeout () = 0;

            /**
             * @brief Gets the timeout for writing.
             * 
             * @return The timeout for writing (in milliseconds).
             * @throws NotSupportedOperationException If the stream cannot timeout.
             */
            virtual long GetWriteTimeout () = 0;

            //************************ General Interface ***********************//
            

            //*********************** Buffer I/O Operators **********************//

            /**
             * @brief Write an unsigned short to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const unsigned short val ) = 0;

            /**
             * @brief Write a short to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const short val ) = 0;

            /**
             * @brief Write an unsigned int to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const unsigned int val ) = 0;

            /**
             * @brief Write an int to the string buffer.
             * 
             * @param val Tthe value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const int val ) = 0;

            /**
             * @brief Write an unsigned long to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const unsigned long val ) = 0;

            /**
             * @brief Write a long to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const long val ) = 0;

            /**
             * @brief Write a float to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const float val ) = 0;

            /**
             * @brief Write a double to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const double val ) = 0;

            /**
             * @brief Write a bool to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const bool val ) = 0;

            /**
             * @brief Write a character to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const char val ) = 0;

            /**
             * @brief Write a string to the string buffer.
             * 
             * @param val The value to write to the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator<< ( const String val ) = 0;

            /**
             * @brief Read an unsigned short from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( unsigned short& val ) = 0;

            /**
             * @brief Read a short from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( short& val ) = 0;

            /**
             * @brief Read an unsigned int from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( unsigned int& val ) = 0;

            /**
             * @brief Read an int from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( int& val ) = 0;

            /**
             * @brief Read an unsigned long from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( unsigned long& val ) = 0;

            /**
             * @brief Read a long from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( long& val ) = 0;

            /**
             * @brief Read a float from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( float& val ) = 0;

            /**
             * @brief Read a double from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( double& val ) = 0;

            /**
             * @brief Read a bool from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( bool& val ) = 0;

            /**
             * @brief Read a character from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( char& val ) = 0;

            /**
             * @brief Read a string from the string buffer.
             * 
             * @param val The value to read into from the buffer.
             * @return A reference to this stream.
             */
            virtual Stream& operator>> ( String& val ) = 0;
            
            //*********************** Buffer I/O Operators **********************//
    };

}

#endif
