/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vfile.h
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

#ifndef VIBRANT_FILE_H
#define VIBRANT_FILE_H

#include <stdio.h>

#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Represents a file on disk.
     * 
     * @author Chris Culy
     */
    class VAPI File
    {
        public:
            
            //**************************** File Modes **************************//

            /**
             * @brief Specifies the different file modes:
             * 
             * <p>
             * The file modes:
             * <ul>
             *  <li>FILE_READ_TEXT</li>
             *  <li>FILE_READ_BINARY</li>
             *  <li>FILE_WRITE_OVERWRITE_TEXT</li>
             *  <li>FILE_WRITE_OVERWRITE_BINARY</li>
             *  <li>FILE_READ_WRITE_TEXT</li>
             *  <li>FILE_READ_WRITE_BINARY</li>
             *  <li>FILE_READ_WRITE_OVERWRITE_TEXT</li>
             *  <li>FILE_READ_WRITE_OVERWRITE_BINARY</li>
             *  <li>FILE_APPEND_TEXT</li>
             *  <li>FILE_APPEND_BINARY</li>
             *  <li>FILE_APPEND_READ_TEXT</li>
             *  <li>FILE_APPEND_READ_BINARY</li>
             * </ul>
             * </p>
             */
            enum FileMode
            {
                FILE_READ_TEXT,
                FILE_READ_BINARY,
                FILE_WRITE_OVERWRITE_TEXT,
                FILE_WRITE_OVERWRITE_BINARY,
                FILE_READ_WRITE_TEXT,
                FILE_READ_WRITE_BINARY,
                FILE_READ_WRITE_OVERWRITE_TEXT,
                FILE_READ_WRITE_OVERWRITE_BINARY,
                FILE_APPEND_TEXT,
                FILE_APPEND_BINARY,
                FILE_APPEND_READ_TEXT,
                FILE_APPEND_READ_BINARY
            };

            /**
             * @brief Retrieves whether the mode is a text mode or not.
             * 
             * @return <code>true</code> if the mode is a text mode;
             *      <code>false</code> otherwise.
             */
            static bool IsTextMode ( FileMode mode );

            /**
             * @brief Retrieves whether the mode is a binary mode or not.
             * 
             * @return <code>true</code> if the mode is a binary mode;
             *      <code>false</code> otherwise.
             */
            static bool IsBinaryMode ( FileMode mode );

            //**************************** File Modes **************************//
            

            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param filename The filename (path) of the file.
             * @param mode The file mode to use when opening the file.
             */
            File ( const String& filename = "", FileMode mode = FILE_READ_WRITE_TEXT );

            /**
             * @brief Destructor.
             */
            ~File ();

            /**
             * @brief Opens the file with the given filename and file mode.
             * 
             * @param filename The filename (path) of the file to open.
             * @param mode The file mode.
             * @throws IllegalArgumentException If the file mode is not supported.
             */
            void Open ( const String& filename, FileMode mode );

            /**
             * @brief Closes the file.
             */
            void Close ();

            /**
             * @brief Reads data into the given buffer (using the file's
             * mode-either text or binary).
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer (where data
             *      should start being read into).
             * @param count The number of bytes to read in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise.
             */
            bool Read ( byte* buffer, const unsigned long offset, const unsigned long count );

            /**
             * @brief Writes data from the given buffer (using the file's
             * mode-either text or binary).
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer (where data
             *      should start being written from).
             * @param count The number of bytes to write out.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool Write ( const byte* buffer, const unsigned long offset, const unsigned long count );

            /**
             * @brief Flushes data to the file.
             */
            void Flush ();

            /**
             * @brief Seeks to the given position in the file.
             * 
             * @param offset The offset to seek to.
             * @param position The position to start seeking from
             *      (-1 indicates seeking from the current position).
             * @return The current file position after seeking.
             */
            unsigned long Seek ( const unsigned long& offset, const long& position = -1 );

            /**
             * @brief Sets the current file position.
             * 
             * @param position The position to seek to.
             */
            void SetPosition ( const unsigned long& position );

            /**
             * @brief Retrieves the current file position.
             * 
             * @return The position.
             */
            unsigned long GetPosition ();

            /**
             * @brief Retrieves whether the file is closed.
             * 
             * @return <code>true</code> if the file is closed;
             *      <code>false</code> otherwise.
             */
            bool IsClosed ();

            /**
             * @brief Retrieves whether the file is open.
             * 
             * @return <code>true</code> if the file is open;
             *      <code>false</code> otherwise.
             */
            bool IsOpen ();

            /**
             * @brief Retrieves whether the file can read.
             * 
             * @return <code>true</code> if the file supports reading;
             *      <code>false</code> otherwise.
             */
            bool CanRead ();

            /**
             * @brief Retrieves whether the file can write.
             * 
             * @return <code>true</code> if the file supports writing;
             *      <code>false</code> otherwise.
             */
            bool CanWrite ();

            /**
             * @brief Retrieves the filename (path) of the file.
             * 
             * @return The file's filename.
             */
            String GetFilename ();

            /**
             * @brief Retrieves the file mode of the file.
             * 
             * @return The file's file mode.
             */
            FileMode GetMode ();

            /**
             * @brief Retrieves the file's size (in bytes).
             * 
             * @return The size of the file in bytes.
             */
            unsigned long GetSize ();

            /**
             * @brief Retrieves whether the file with the given
             * filename (path) exists or not.
             * 
             * @return <code>true</code> if the file exists;
             *      <code>false</code> otherwise.
             */
            static bool Exists ( const String& filename );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadUnsignedShort ( unsigned short* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadShort ( short* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadUnsignedInt ( unsigned int* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadInt ( int* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadUnsignedLong ( unsigned long* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadLong ( long* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadFloat ( float* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadDouble ( double* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadBool ( bool* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadCharacter ( vchar* val );

            /**
             * @brief Reads the given value.
             * 
             * @param val The value to store the read value in.
             * @return <code>true</code> if the read was successful;
             *      <code>false</code> otherwise (in this case,
             *      <code>val</code>'s value may be incorrect or corrupted).
             */
            bool ReadString ( String* val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteUnsignedShort ( const unsigned short& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteShort ( const short& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteUnsignedInt ( const unsigned int& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteInt ( const int& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteUnsignedLong ( const unsigned long& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteLong ( const long& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteFloat ( const float& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteDouble ( const double& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteBool ( const bool& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteCharacter ( const vchar& val );

            /**
             * @brief Writes the given value.
             * 
             * @param val The value to write to the file.
             * @return <code>true</code> if the write was successful;
             *      <code>false</code> otherwise.
             */
            bool WriteString ( const String& val );

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Reads a single value from the file.
             * 
             * @param type The type to read in (use a value from {@link File::FileIOConstants}).
             * @param val The value to read into.
             * @return <code>true</code> if the value was read in successfully;
             *      <code>false</code> otherwise.
             * @see File::FileIOConstants
             */
            template< typename T > bool Read ( const char* type, T* val );

            /**
             * @brief Writes a single value to a file.
             * 
             * @param type The type to write out (use a value from {@link File::FileIOConstants}).
             * @param val The value to write out.
             * @return <code>true</code> if the value was written out successfully;
             *      <code>false</code> otherwise.
             * @see File::FileIOConstants
             */
            template< typename T > bool Write ( const char* type, const T& val );

            /**
             * @brief Reads text from a file.
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @return <code>true</code> if the text was read successfully;
             *      <code>false</code> otherwise.
             */
            bool ReadText ( byte* buffer, const unsigned long offset, const unsigned long count );

            /**
             * @brief Reads bytes from a file.
             * 
             * @param buffer The buffer to read into.
             * @param offset The offset into the buffer.
             * @param count The number of elements to read (<code>byte</code>s).
             * @return <code>true</code> if the bytes were read successfully;
             *      <code>false</code> otherwise.
             */
            bool ReadBytes ( byte* buffer, const unsigned long offset, const unsigned long count );

            /**
             * @brief Writes text to a file.
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to write (<code>byte</code>s).
             * @return <code>true</code> if the text was written successfully;
             *      <code>false</code> otherwise.
             */
            bool WriteText ( const byte* buffer, const unsigned long offset, const unsigned long count );

            /**
             * @brief Writes bytes to a file.
             * 
             * @param buffer The buffer to write from.
             * @param offset The offset into the buffer.
             * @param count The number of elements to write (<code>byte</code>s).
             * @return <code>true</code> if the bytes were written successfully;
             *      <code>false</code> otherwise.
             */
            bool WriteBytes ( const byte* buffer, const unsigned long offset, const unsigned long count );

            //************************ General Interface ***********************//
            

            //**************************** File Modes **************************//

            /** 
             * @brief Defines the file mode constants used
             * by the C file I/O functions.
             */
            struct FileModeConstants
            {
                    /** 
                     * @brief Opens the file for reading text-the file must exist.
                     */
                    static const char* FILE_READ_TEXT;

                    /**
                     * @brief Opens the file for reading binary-the file must exist.
                     */
                    static const char* FILE_READ_BINARY;

                    /**
                     * @brief Opens the file for writing text-the file need not exist;
                     * if the file already existed, it is overwritten.
                     */
                    static const char* FILE_WRITE_OVERWRITE_TEXT;

                    /**
                     * @brief Opens the file for writing binary-the file need not exist;
                     * if the file already existed, it is overwritten.
                     */
                    static const char* FILE_WRITE_OVERWRITE_BINARY;

                    /**
                     * @brief Opens the file for reading and writing text-the file must exist.
                     */
                    static const char* FILE_READ_WRITE_TEXT;

                    /**
                     * @brief Opens the file for reading and writing binary-the file must exist.
                     */
                    static const char* FILE_READ_WRITE_BINARY;

                    /**
                     * @brief Opens the file for reading and writing text-the file need not exist;
                     * if the file already existed, it is overwritten.
                     */
                    static const char* FILE_READ_WRITE_OVERWRITE_TEXT;

                    /**
                     * @brief Opens the file for reading and writing binary-the file need not exist;
                     * if the file already existed, it is overwritten.
                     */
                    static const char* FILE_READ_WRITE_OVERWRITE_BINARY;

                    /**
                     * @brief Opens the file for appending text-the file is created if it does not exist.
                     */
                    static const char* FILE_APPEND_TEXT;

                    /**
                     * @brief Opens the file for appending binary-the file is created if it does not exist.
                     */
                    static const char* FILE_APPEND_BINARY;

                    /**
                     * @brief Opens the file for reading (throughout the file) and appending
                     * text (only at the end)-the file is created if it does not exist.
                     */
                    static const char* FILE_APPEND_READ_TEXT;

                    /**
                     * @brief Opens the file for reading (throughout the file) and appending
                     * binary (only at the end)-the file is created if it does not exist.
                     */
                    static const char* FILE_APPEND_READ_BINARY;
            };

            /**
             * @brief Gets the file mode constant used by the C I/O library
             * functions that corresponds to the given FileMode.
             * 
             * @param mode The file mode.
             * @return The corresponding C file I/O mode.
             * @throws IllegalArgumentException If the file mode is not supported.
             */
            const char* GetFileModeConstant ( FileMode mode );

            //**************************** File Modes **************************//
            

            //************************ File I/O Constants **********************//

            /** @brief Defines the default size of a string (used for reading strings). */
            static const int FILE_DEFAULT_STRING_SIZE = 256;

            /** 
             * @brief Defines the file I/O constants used by the C file I/O functions
             * <code>fscanf</code>  and <code>fprintf</code>.
             * </p>
             */
            struct FileIOConstants
            {
                    /**
                     * @brief Read/write an <code>unsigned short</code>.
                     */
                    static const char* FILE_IO_UNSIGNED_SHORT;

                    /**
                     * @brief Read/write a <code>short</code>.
                     */
                    static const char* FILE_IO_SHORT;

                    /**
                     * @brief Read/write an <code>unsigned int</code>.
                     */
                    static const char* FILE_IO_UNSIGNED_INT;

                    /**
                     * @brief Read/write an <code>int</code>.
                     */
                    static const char* FILE_IO_INT;

                    /**
                     * @brief Read/write an <code>unsigned long</code>.
                     */
                    static const char* FILE_IO_UNSIGNED_LONG;

                    /**
                     * @brief Read/write a <code>long</code>.
                     */
                    static const char* FILE_IO_LONG;

                    /**
                     * @brief Read/write a <code>float</code>.
                     */
                    static const char* FILE_IO_FLOAT;

                    /**
                     * @brief Read/write a <code>double</code>.
                     */
                    static const char* FILE_IO_DOUBLE;

                    /**
                     * @brief Read/write a <code>bool</code>.
                     */
                    static const char* FILE_IO_BOOL;

                    /**
                     * @brief Read/write a <code>char</code>.
                     */
                    static const char* FILE_IO_CHAR;

                    /**
                     * @brief Read/write a <code>wchar_t</code>.
                     */
                    static const char* FILE_IO_WIDE_CHAR;

                    /**
                     * @brief Text version of the boolean value <code>true</code>.
                     */
                    static const String FILE_IO_BOOL_TRUE;

                    /**
                     * @brief Text version of the boolean value <code>false</code>.
                     */
                    static const String FILE_IO_BOOL_FALSE;
            };

            //************************ File I/O Constants **********************//

        private:
            
            /** @brief Holds whether the file is closed or not. */
            bool closed;

            /** @brief Holds whether the file supports reading. */
            bool supportsReading;

            /** @brief Holds whether the file supports writing. */
            bool supportsWriting;

            /** @brief Holds the file's filename. */
            String filename;

            /** @brief Holds the file's mode. */
            FileMode mode;

            /** @brief Holds the underlying file pointer. */
            FILE* file;
    };

}

#endif
