/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vfilestream.cpp
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

//#include "vbinarystream.h"
#include "vexception.h"
#include "vfilestream.h"
#include "vstring.h"
#include "vtextstream.h"

namespace Vibrant
{
    
    FileStream::FileStream ( const String& filename, const File::FileMode mode )
    {
        if ( filename.IsEmpty () )
        {
            throw IllegalArgumentException ( "FileStream::FileStream - Cannot create a file stream from an empty filename(path)." );
        }

        // Create the file and set that the stream owns it.
        this->file = new File ( filename );
        this->ownsFile = true;
        
        // Set the file length to the default (maximum size).
        this->length = ULONG_MAX;
    }
    
    FileStream::FileStream ( File* file )
    {
        if ( file == null )
        {
            throw NullPointerException ( "FileStream::FileStream - Cannot create a file stream from a null file." );
        }

        // Set the file and that we do not own it.
        this->file = file;
        this->ownsFile = false;
        
        // Set the file length to the default (maximum size).
        this->length = ULONG_MAX;
    }
    
    FileStream::~FileStream ()
    {
        // If the stream owns the file, then delete it now.
        if ( this->ownsFile )
        {
            if ( this->file != null )
            {
                delete this->file;
                this->file = null;
            }
        }
    }
    
    bool FileStream::Read ( byte* buffer, const int& offset, const int& count )
    {
        // Check if the file is closed.
        if ( this->file->IsClosed () )
        {
            return false;
        }
        
        // TODO: Implement this.
        return false;
    }
    
    bool FileStream::Read ( byte& data )
    {
        // Check if the file is closed.
        if ( this->file->IsClosed () )
        {
            return false;
        }
        
        // TODO: Implement this.
        return false;
    }
    
    bool FileStream::Write ( const byte* buffer, const int& offset, const int& count )
    {
        // TODO: Implement this.
        return false;
    }
    
    bool FileStream::Write ( const byte& data )
    {
        // Check if the file is closed.
        if ( this->file->IsClosed () )
        {
            return false;
        }
        
        // TODO: Implement this.
        return false;
    }
    
    void FileStream::Flush ()
    {
        // Check if the file is closed.
        if ( !this->file->IsClosed () )
        {
            // Flush the file.
            this->file->Flush ();
        }
    }
    
    void FileStream::Close ()
    {
        this->Flush ();
        this->file->Close ();
    }
    
    unsigned long FileStream::Seek ( const unsigned long& offset, const long& position )
    {
        // Check if the file is closed.
        if ( this->file->IsClosed () )
        {
            return 0;
        }

        // Cap the seek position.
        unsigned long seekPosition = ( (unsigned long) position >= this->length ) ? this->length - 1 : (unsigned long) position;
        
        // Seek using the underlying file.
        return this->file->Seek ( offset, seekPosition );
    }
    
    void FileStream::SetPosition ( const unsigned long& position )
    {
        this->Seek ( position, 0 );
    }
    
    unsigned long FileStream::GetPosition ()
    {
        return this->file->GetPosition ();
    }
    
    void FileStream::SetLength ( unsigned long length )
    {
        // Check if the file is closed.
        if ( this->file->IsClosed () )
        {
            return;
        }

        // When the length has decreased, resize (and
        // truncate) the data appropriately.
        if ( length < this->length )
        {
            // Close the file and store the old position before resizing it.
            unsigned long oldPosition = this->GetPosition ();
            this->file->Close ();
            
            // Get the beginning of the file's data (get "length" bytes).
            File oldFile;
            oldFile.Open ( this->file->GetFilename (), File::FILE_READ_BINARY );
            byte* buffer = new byte[ this->length ];
            oldFile.Read ( buffer, 0, this->length );
            oldFile.Close ();
            
            // Open the file for overwrite and write the data.
            File newFile;
            newFile.Open ( this->file->GetFilename (), File::FILE_WRITE_OVERWRITE_BINARY );
            newFile.Write ( buffer, 0, this->length );
            newFile.Close ();
            
            // Reopen this file in the proper mode and seek to the proper position.
            this->file->Open ( this->file->GetFilename (), this->file->GetMode () );
            this->file->Seek ( oldPosition );
        }
        this->length = length;
    }
    
    unsigned long FileStream::GetLength ()
    {
        return this->length;
    }
    
    bool FileStream::CanSeek ()
    {
        return true;
    }
    
    bool FileStream::CanRead ()
    {
        return this->file->CanRead ();
    }
    
    bool FileStream::CanWrite ()
    {
        return this->file->CanWrite ();
    }
    
    bool FileStream::CanTimeout ()
    {
        return false;
    }
    
    void FileStream::SetReadTimeout ( long timeout )
    {
        throw NotSupportedOperationException ( "FileStream::SetReadTimeout - File streams cannot timeout." );
    }
    
    void FileStream::SetWriteTimeout ( long timeout )
    {
        throw NotSupportedOperationException ( "FileStream::SetWriteTimeout - File streams cannot timeout." );
    }
    
    long FileStream::GetReadTimeout ()
    {
        throw NotSupportedOperationException ( "FileStream::GetReadTimeout - File streams cannot timeout." );
    }
    
    long FileStream::GetWriteTimeout ()
    {
        throw NotSupportedOperationException ( "FileStream::GetWriteTimeout - File streams cannot timeout." );
    }
    
    Stream& FileStream::operator<< ( const unsigned short val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteUnsignedShort ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const short val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteShort ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const unsigned int val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteUnsignedInt ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const int val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteInt ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const unsigned long val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteUnsignedLong ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const long val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteLong ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const float val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteFloat ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const double val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteDouble ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const bool val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteBool ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const char val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteCharacter ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator<< ( const String val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->WriteString ( val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( unsigned short& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadUnsignedShort ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( short& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadShort ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( unsigned int& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadUnsignedInt ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( int& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadInt ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( unsigned long& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadUnsignedLong ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( long& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadLong ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( float& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadFloat ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( double& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadDouble ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( bool& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadBool ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( char& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadCharacter ( &val );
        }
        return *this;
    }
    
    Stream& FileStream::operator>> ( String& val )
    {
        // Only write if there is space in the stream.
        if ( this->file->GetPosition () + sizeof( val ) < this->length )
        {
            this->file->ReadString ( &val );
        }
        return *this;
    }

}
