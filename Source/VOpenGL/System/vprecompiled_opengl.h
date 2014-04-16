/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vprecompiled_opengl.h
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

#ifndef VIBRANT_PRECOMPILED_OPENGL_H
#define VIBRANT_PRECOMPILED_OPENGL_H

// Include the main engine precompiled header.
// Note: windows.h must be included before OpenGL headers
// (and is included in the precompiled header).
#include "vprecompiled.h"

// Include OpenGL headers.

#include <GL/glee.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Used to specifiy offsets into OpenGL buffers (i.e. vertex or index buffer offsets).
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif
