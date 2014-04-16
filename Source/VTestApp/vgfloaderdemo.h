/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgfloaderdemo.h
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

#ifndef VIBRANT_VGFLOADER_DEMO_H
#define VIBRANT_VGFLOADER_DEMO_H

#include "vexception.h"
#include "vgfloader.h"
#include "vlog.h"
#include "vmatrix.h"
#include "vstring.h"

using namespace Vibrant;

/**
 * @brief Parses the given filename (and changes it to the correct state).
 * 
 * @param filename The filename to parse.
 */
void ParseFilename ( String& filename );

/**
 * @brief Runs the VGF loader demo.
 * 
 * @return 0 on success; non-zero otherwise.
 */
int VGFLoaderDemo ();

#endif
