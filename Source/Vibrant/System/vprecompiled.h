/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vprecompiled.h
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

#ifndef VIBRANT_PRECOMPILED_H
#define VIBRANT_PRECOMPILED_H

// TODO: Remove this later to check if there are any valid DLL warnings.
#if defined (_MSC_VER)
#pragma warning(disable: 4251)
#endif

#include "vdll.h"

#ifdef WIN32

// Windows System Defines.

#define NTDDI_VERSION NTDDI_XPSP2
#define _WIN32_WINNT 0x0502
#define WINVER 0x0502
#define WIN32_LEAN_AND_MEAN

// Windows Includes.

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>

// Windows Defines.

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam) ((int)(short) LOWORD (lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam) ((int)(short) HIWORD (lParam))
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif
#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam) ((short) HIWORD (wParam))
#endif

#else

// Unix/Mac/Linux Includes.

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#endif

// Cross-Platform Includes.

#include <fstream>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <math.h>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>

// Global Typedefs/Defines.

#ifndef null
#define null 0
#endif

namespace Vibrant
{
    typedef unsigned char byte;
}

#endif
