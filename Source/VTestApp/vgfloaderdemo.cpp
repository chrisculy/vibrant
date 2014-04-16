/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgfloaderdemo.cpp
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

#include "vfilestream.h"
#include "vgfloaderdemo.h"
#include "vstring.h"
#include "vxmlwriter.h"

void ParseFilename ( String& filename )
{
    filename.Replace ( "\\", "\\\\" );
}

int VGFLoaderDemo ()
{
    
    Mesh* mesh = new Mesh ();
    String filename;
    //std::cout << "Enter filename (VGF) (no spaces): ";
    //std::cin >> filename;
    filename = "D:\\Programming\\alterr\\Skiing.vgf";
    ParseFilename ( filename );
    try
    {
        VGFLoader::Load ( filename, mesh );
    }
    catch ( NullPointerException e )
    {
        //vlog << "VGFLoader::load (): mesh was null.\n";
        return -1;
    }
    catch ( IllegalArgumentException e )
    {
        //vlog << "VGFLoader::load (): invalid file path.\n";
        return -1;
    }

    //std::cout << "Enter output file (file must already exist-no spaces): ";
    //std::cin >> filename;
    filename = "D:\\Programming\\alterr\\Skiing.xml";
    ParseFilename ( filename );
    File* file = new File ( filename, File::FILE_WRITE_OVERWRITE_TEXT );
    Stream* stream = new FileStream ( file );
    XMLWriter* writer = new XMLWriter ( stream );
    
    // Write the mesh.
    mesh->Write ( writer );
    
    // Write to the file.
    writer->Write ();
    
    delete writer;
    delete stream;
    
    system ( "pause" );
    return 0;
}
