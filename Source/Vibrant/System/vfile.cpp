/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vfile.cpp
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

#include "vexception.h"
#include "vfile.h"
#include "vstring.h"

namespace Vibrant
{
    
    // --------------------- File Mode Constants (Used by fopen) --------------------- //
    // ------------------------------------------------------------------------------- //

    const char* File::FileModeConstants::FILE_READ_TEXT = "r";
    const char* File::FileModeConstants::FILE_READ_BINARY = "rb";
    const char* File::FileModeConstants::FILE_WRITE_OVERWRITE_TEXT = "w";
    const char* File::FileModeConstants::FILE_WRITE_OVERWRITE_BINARY = "wb";
    const char* File::FileModeConstants::FILE_READ_WRITE_TEXT = "r+";
    const char* File::FileModeConstants::FILE_READ_WRITE_BINARY = "rb+";
    const char* File::FileModeConstants::FILE_READ_WRITE_OVERWRITE_TEXT = "w+";
    const char* File::FileModeConstants::FILE_READ_WRITE_OVERWRITE_BINARY = "wb+";
    const char* File::FileModeConstants::FILE_APPEND_TEXT = "a";
    const char* File::FileModeConstants::FILE_APPEND_BINARY = "ab";
    const char* File::FileModeConstants::FILE_APPEND_READ_TEXT = "a+";
    const char* File::FileModeConstants::FILE_APPEND_READ_BINARY = "ab+";
    
    // ------------------------------------------------------------------------------- //
    // --------------------- File Mode Constants (Used by fopen) --------------------- //
    

    // --- File I/O Constants (Used by fread/fwrite and fscanf/fprintf) --- //
    // -------------------------------------------------------------------- //

    const char* File::FileIOConstants::FILE_IO_UNSIGNED_SHORT = "%hu";
    const char* File::FileIOConstants::FILE_IO_SHORT = "%hd";
    const char* File::FileIOConstants::FILE_IO_UNSIGNED_INT = "%u";
    const char* File::FileIOConstants::FILE_IO_INT = "%d";
    const char* File::FileIOConstants::FILE_IO_UNSIGNED_LONG = "%lu";
    const char* File::FileIOConstants::FILE_IO_LONG = "%ld";
    const char* File::FileIOConstants::FILE_IO_FLOAT = "%f";
    const char* File::FileIOConstants::FILE_IO_DOUBLE = "%lf";
    const char* File::FileIOConstants::FILE_IO_BOOL = "%s";
    const char* File::FileIOConstants::FILE_IO_CHAR = "%hc";
    const char* File::FileIOConstants::FILE_IO_WIDE_CHAR = "%lc";
    
    // -------------------------------------------------------------------- //
    // --- File I/O Constants (Used by fread/fwrite and fscanf/fprintf) --- //
    

    // ------------------ Used for writing boolean values as text. ------------------ //
    // ------------------------------------------------------------------------------ //

    const String File::FileIOConstants::FILE_IO_BOOL_TRUE = String ( "true" );
    const String File::FileIOConstants::FILE_IO_BOOL_FALSE = String ( "false" );
    
    // ------------------------------------------------------------------------------ //
    // ------------------ Used for writing boolean values as text. ------------------ //
    

    File::File ( const String& filename, FileMode mode )
    {
        // The file has not been opened yet.
        this->closed = true;
        // Set defaults (these are changed when the file is opened).
        this->supportsReading = false;
        this->supportsWriting = false;
        
        // Open the file, but only if the filename is non-empty.
        if ( !filename.IsEmpty () )
        {
            this->Open ( filename, mode );
        }
    }
    
    File::~File ()
    {
        // Close the file (if it's not already closed).
        this->Close ();
    }
    
    void File::Open ( const String& filename, FileMode mode )
    {
        // Set the file's filename and mode.
        this->filename = filename;
        this->mode = mode;
        
        // Attempt to open the file.
#ifdef _MSC_VER
        fopen_s ( &(this->file), filename.CString (), File::GetFileModeConstant ( mode ) );
#else
        this->file = fopen ( filename.CString (), File::GetFileModeConstant ( mode ) );
#endif
        
        // Check for errors.
        if ( this->file == null )
        {
            throw FileIOException ( "File::open - The file could not be opened." );
        }

        // The file is now open.
        this->closed = false;
        
        // Store whether we can read and write.
        switch ( mode )
        {
            case FILE_READ_TEXT:
            case FILE_READ_BINARY:
                this->supportsReading = true;
                this->supportsWriting = false;
                break;
            case FILE_WRITE_OVERWRITE_TEXT:
            case FILE_WRITE_OVERWRITE_BINARY:
            case FILE_APPEND_TEXT:
            case FILE_APPEND_BINARY:
                this->supportsReading = false;
                this->supportsWriting = true;
                break;
            case FILE_READ_WRITE_TEXT:
            case FILE_READ_WRITE_BINARY:
            case FILE_READ_WRITE_OVERWRITE_TEXT:
            case FILE_READ_WRITE_OVERWRITE_BINARY:
            case FILE_APPEND_READ_TEXT:
            case FILE_APPEND_READ_BINARY:
                this->supportsReading = true;
                this->supportsWriting = true;
                break;
            default:
                throw IllegalArgumentException ( "File::open - The file mode is not supported." );
        }
    }
    
    void File::Close ()
    {
        // Only close the file if the file is valid and open.
        if ( !this->closed && this->file != null )
        {
            fclose ( this->file );
            this->closed = true;
            this->file = null;
        }
    }
    
    bool File::Read ( byte* buffer, const unsigned long offset, const unsigned long count )
    {
        // Check if we can read.
        if ( !this->CanRead () )
        {
            throw FileIOException ( "File::read - The file does not support reading." );
        }

        // Make sure the file is open.
        if ( this->closed )
        {
            return false;
        }
        
        // Read text or binary depending on the file's mode.
        if ( IsTextMode ( this->mode ) )
        {
            return this->ReadText ( buffer, offset, count );
        }
        else
        {
            return this->ReadBytes ( buffer, offset, count );
        }
    }
    
    bool File::Write ( const byte* buffer, const unsigned long offset, const unsigned long count )
    {
        // Check if we can write.
        if ( !this->CanWrite () )
        {
            throw FileIOException ( "File::write - The file does not support writing." );
        }

        // Make sure the file is open.
        if ( this->closed )
        {
            return false;
        }
        
        // Write text or binary depending on the file's mode.
        if ( IsTextMode ( this->mode ) )
        {
            return this->WriteText ( buffer, offset, count );
        }
        else
        {
            return this->WriteBytes ( buffer, offset, count );
        }
    }
    
    void File::Flush ()
    {
        // Check if the file is open.
        if ( !this->closed )
        {
            // Check for errors.
            if ( fflush ( this->file ) == EOF )
            {
                // TODO: Log an error.
            }
        }
    }
    
    unsigned long File::Seek ( const unsigned long& offset, const long& position )
    {
        // Check if the stream is closed.
        if ( this->closed )
        {
            return 0;
        }

        // Passing -1 as the position means to use the current position.
        unsigned long newPosition = ftell ( this->file );
        if ( position == -1 )
        {
            newPosition += offset;
        }
        // Compute the new position normally.
        else
        {
            newPosition = position + offset;
        }

        // TODO: Write VMath::clamp(T value, T low, T high).
        if ( newPosition < 0 )
        {
            newPosition = 0;
        }

        // Perform the actual seek, checking for errors.
        if ( fseek ( this->file, newPosition, SEEK_SET ) != 0 )
        {
            // TODO: Log an error.
        }
        
        return ftell ( this->file );
    }
    
    void File::SetPosition ( const unsigned long& position )
    {
        this->Seek ( position, 0 );
    }
    
    unsigned long File::GetPosition ()
    {
        if ( !this->closed )
        {
            return ftell ( this->file );
        }
        return 0;
    }
    
    bool File::IsClosed ()
    {
        return this->closed;
    }
    
    bool File::IsOpen ()
    {
        return !this->closed;
    }
    
    bool File::CanRead ()
    {
        return this->supportsReading;
    }
    
    bool File::CanWrite ()
    {
        return this->supportsWriting;
    }
    
    String File::GetFilename ()
    {
        return this->filename;
    }
    
    File::FileMode File::GetMode ()
    {
        return this->mode;
    }
    
    unsigned long File::GetSize ()
    {
        // Close the file, and reopen it in binary mode to get the file size.
        unsigned long oldPosition = this->GetPosition ();
        bool reopenFile = false;
        if ( this->IsOpen () )
        {
            reopenFile = true;
            this->Close ();
        }

        // If we fail to open the file in binary mode, then
        // return zero as the size.
        long size = -1L;
        this->Open ( this->filename, FILE_READ_BINARY );
        if ( this->IsOpen () )
        {
            // Seek to the end of the file and get the position,
            // which is the number of bytes in the file.
            fseek ( this->file, 0, SEEK_END );
            size = ftell ( this->file );
            
            // Check if any errors occured.
            if ( size == -1L )
            {
                // TODO: Log an error.
                // TODO: This is probably wrong.
                size = 0;
            }
        }
        // Otherwise, we have failed to open the file
        // properly and return zero as the size.
        else
        {
            size = 0;
        }

        // If the file was originally open, reopen it in
        // its proper mode and seek to the old position.
        if ( reopenFile )
        {
            this->Open ( this->filename, this->mode );
            this->SetPosition ( oldPosition );
        }
        
        // Return the calculated file size.
        return size;
    }
    
    bool File::Exists ( const String& filename )
    {
        // Attempt to open the given file.
        std::ifstream testFileExistence;
        testFileExistence.open ( filename.CString () );
        
        // If the file open successfully, it
        // exists; otherwise it doesn't.
        if ( testFileExistence.is_open () )
        {
            testFileExistence.close ();
            return true;
        }
        testFileExistence.close ();
        return false;
    }
    
    bool File::IsTextMode ( FileMode mode )
    {
        switch ( mode )
        {
            case FILE_APPEND_TEXT:
            case FILE_APPEND_READ_TEXT:
            case FILE_READ_TEXT:
            case FILE_READ_WRITE_TEXT:
            case FILE_READ_WRITE_OVERWRITE_TEXT:
            case FILE_WRITE_OVERWRITE_TEXT:
                return true;
            default:
                return false;
        }
    }
    
    bool File::IsBinaryMode ( FileMode mode )
    {
        switch ( mode )
        {
            case FILE_APPEND_BINARY:
            case FILE_APPEND_READ_BINARY:
            case FILE_READ_BINARY:
            case FILE_READ_WRITE_BINARY:
            case FILE_READ_WRITE_OVERWRITE_BINARY:
            case FILE_WRITE_OVERWRITE_BINARY:
                return true;
            default:
                return false;
        }
    }
    
    bool File::ReadUnsignedShort ( unsigned short* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_UNSIGNED_SHORT, val );
    }
    
    bool File::ReadShort ( short* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_SHORT, val );
    }
    
    bool File::ReadUnsignedInt ( unsigned int* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_UNSIGNED_INT, val );
    }
    
    bool File::ReadInt ( int* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_INT, val );
    }
    
    bool File::ReadUnsignedLong ( unsigned long* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_UNSIGNED_LONG, val );
    }
    
    bool File::ReadLong ( long* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_LONG, val );
    }
    
    bool File::ReadFloat ( float* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_FLOAT, val );
    }
    
    bool File::ReadDouble ( double* val )
    {
        return this->Read ( FileIOConstants::FILE_IO_DOUBLE, val );
    }
    
    bool File::ReadBool ( bool* val )
    {
        // Read in the human readable boolean ("true"/"false").
        String string;
        if ( !this->ReadString ( &string ) )
        {
            return false;
        }

        // Set the return boolean.
        *val = ( string == FileIOConstants::FILE_IO_BOOL_TRUE );
        return true;
    }
    
    bool File::ReadCharacter ( vchar* val )
    {
#ifdef UNICODE
        return this->Read ( FileIOConstants::FILE_IO_WIDE_CHAR, val );
#else
        return this->Read ( FileIOConstants::FILE_IO_CHAR, val );
#endif
    }
    
    bool File::ReadString ( String* val )
    {
        // Set the string size to the default.
        unsigned long size = File::FILE_DEFAULT_STRING_SIZE;
        
        // If we are in a binary mode, read in the
        // length of the string at the beginning.
        if ( File::IsBinaryMode ( this->mode ) )
        {
            this->ReadUnsignedLong ( &size );
        }

        // Create a buffer to read the string into.
        vchar* buffer = new char[ size + 1 ];
        
        // Set up to read in the characters of the string.
        bool result = true;
        unsigned long index = 0;
        
        // If we are in binary mode, then read the
        // given amount of characters.
        if ( File::IsBinaryMode ( this->mode ) )
        {
            // Read text until the buffer is full or we hit whitespace.
            while ( index < size && result )
            {
                result = this->ReadCharacter ( &( buffer[ index ] ) );
                index++;
            }
        }
        else
        {
            // Read text until the buffer is full or we hit whitespace.
            while ( index < size && result )
            {
                result = this->ReadCharacter ( &( buffer[ index ] ) );
                index++;
                
                if ( String::IsWhitespace ( buffer[ index - 1 ] ) )
                {
                    break;
                }
            }
        }

        // Append the null terminator.
        buffer[ index ] = '\0';
        // Set the return string.
        *val = buffer;
        
        // Check for errors.
        if ( !result )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    bool File::WriteUnsignedShort ( const unsigned short& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_UNSIGNED_SHORT, val );
    }
    
    bool File::WriteShort ( const short& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_SHORT, val );
    }
    
    bool File::WriteUnsignedInt ( const unsigned int& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_UNSIGNED_INT, val );
    }
    
    bool File::WriteInt ( const int& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_INT, val );
    }
    
    bool File::WriteUnsignedLong ( const unsigned long& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_UNSIGNED_LONG, val );
    }
    
    bool File::WriteLong ( const long& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_LONG, val );
    }
    
    bool File::WriteFloat ( const float& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_FLOAT, val );
    }
    
    bool File::WriteDouble ( const double& val )
    {
        return this->Write ( FileIOConstants::FILE_IO_DOUBLE, val );
    }
    
    bool File::WriteBool ( const bool& val )
    {
        // Write a human readable boolean ("true"/"false").
        if ( val )
        {
            return this->WriteString ( FileIOConstants::FILE_IO_BOOL_TRUE );
        }
        else
        {
            return this->WriteString ( FileIOConstants::FILE_IO_BOOL_FALSE );
        }
    }
    
    bool File::WriteCharacter ( const vchar& val )
    {
#ifdef UNICODE
        return this->Write ( FileIOConstants::FILE_IO_WIDE_CHAR, val );
#else
        return this->Write ( FileIOConstants::FILE_IO_CHAR, val );
#endif
    }
    
    bool File::WriteString ( const String& val )
    {
        // Get the size of the string.
        unsigned long size = val.Size ();
        
        // If we are in a binary mode, write out the
        // length of string at the beginning.
        if ( File::IsBinaryMode ( this->mode ) )
        {
            this->WriteUnsignedLong ( size );
        }

        // Write out the text (in the same way it is read in).
        const char* buffer = val.CString ();
        bool result = true;
        unsigned long index = 0;
        while ( index < size && result )
        {
            result = this->WriteCharacter ( buffer[ index ] );
            index++;
        }

        // Check for errors.
        if ( !result )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    template< typename T > bool File::Read ( const char* type, T* val )
    {
        int result = 0;
        // Read in the proper mode (text or binary).
        if ( File::IsTextMode ( this->mode ) )
        {
            // Read in the value.
#ifdef _MSC_VER
            result = fscanf_s ( this->file, type, val );
#else
            result = fscanf ( this->file, type, val );
#endif
        }
        else
        {
            unsigned short count = sizeof(T);
            result = this->ReadBytes ( (byte*) val, 0, count );
        }

        // Check for errors.
        if ( result == 0 )
        {
            // TODO: Log a "Failed to match data." error.
            return false;
        }
        else if ( result == EOF )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    template< typename T > bool File::Write ( const char* type, const T& val )
    {
        int result = 0;
        // Write in the proper mode (text or binary).
        if ( File::IsTextMode ( this->mode ) )
        {
            // Write out the value.
#ifdef _MSC_VER
            result = fprintf_s ( this->file, type, val );
#else
            result = fprintf ( this->file, type, val );
#endif
        }
        else
        {
            unsigned short count = sizeof(T);
            result = this->WriteBytes ( (byte*) ( &val ), 0, count );
        }

        // Check for errors.
        if ( result < 0 )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    bool File::ReadText ( byte* buffer, const unsigned long offset, const unsigned long count )
    {
        // Get the first character.
        int ch = fgetc ( this->file );
        
        unsigned long counter = 0;
        unsigned long index = offset;
        // Get characters until we are done.
        while ( ch != EOF && counter < count )
        {
            buffer[ index ] = ch;
            ch = fgetc ( this->file );
            counter++;
            index++;
        }

        // Check for errors.
        if ( ferror ( this->file ) != 0 )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    bool File::ReadBytes ( byte* buffer, const unsigned long offset, const unsigned long count )
    {
        unsigned int bytesRead = fread ( &( buffer[ offset ] ), sizeof(byte), count, this->file );
        // Check for errors.
        if ( bytesRead != count )
        {
            if ( ferror ( this->file ) != 0 )
            {
                // TODO: Log an error.
                return false;
            }
        }
        
        return true;
    }
    
    bool File::WriteText ( const byte* buffer, const unsigned long offset, const unsigned long count )
    {
        int result = 0;
        unsigned long counter = 0;
        unsigned long index = offset;
        
        // Put characters until we are done.
        while ( result != EOF && counter < count )
        {
            result = fputc ( buffer[ index ], this->file );
            counter++;
            index++;
        }

        // Check for errors.
        if ( ferror ( this->file ) != 0 )
        {
            // TODO: Log an error.
            return false;
        }
        
        return true;
    }
    
    bool File::WriteBytes ( const byte* buffer, const unsigned long offset, const unsigned long count )
    {
        unsigned int bytesWritten = fwrite ( &( buffer[ offset ] ), sizeof(byte), count, this->file );
        
        // Check for errors.
        if ( bytesWritten != count )
        {
            if ( ferror ( this->file ) != 0 )
            {
                // TODO: Log an error.
                return false;
            }
        }
        
        return true;
    }
    
    const char* File::GetFileModeConstant ( FileMode mode )
    {
        switch ( mode )
        {
            case FILE_READ_TEXT:
                return File::FileModeConstants::FILE_READ_TEXT;
            case FILE_READ_BINARY:
                return File::FileModeConstants::FILE_READ_BINARY;
            case FILE_WRITE_OVERWRITE_TEXT:
                return File::FileModeConstants::FILE_WRITE_OVERWRITE_TEXT;
            case FILE_WRITE_OVERWRITE_BINARY:
                return File::FileModeConstants::FILE_WRITE_OVERWRITE_BINARY;
            case FILE_READ_WRITE_TEXT:
                return File::FileModeConstants::FILE_READ_WRITE_TEXT;
            case FILE_READ_WRITE_BINARY:
                return File::FileModeConstants::FILE_READ_WRITE_BINARY;
            case FILE_READ_WRITE_OVERWRITE_TEXT:
                return File::FileModeConstants::FILE_READ_WRITE_OVERWRITE_TEXT;
            case FILE_READ_WRITE_OVERWRITE_BINARY:
                return File::FileModeConstants::FILE_READ_WRITE_OVERWRITE_BINARY;
            case FILE_APPEND_TEXT:
                return File::FileModeConstants::FILE_APPEND_TEXT;
            case FILE_APPEND_BINARY:
                return File::FileModeConstants::FILE_APPEND_BINARY;
            case FILE_APPEND_READ_TEXT:
                return File::FileModeConstants::FILE_APPEND_READ_TEXT;
            case FILE_APPEND_READ_BINARY:
                return File::FileModeConstants::FILE_APPEND_READ_BINARY;
                // Unsupported file mode.
            default:
                throw IllegalArgumentException ( "File::GetFileModeConstant - File mode not supported." );
        }
    }

}
