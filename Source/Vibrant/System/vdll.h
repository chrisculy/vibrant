/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vdll.h
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

#ifndef VIBRANT_DLL_H
#define VIBRANT_DLL_H

// Define DLL macros.
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#ifdef DLL_BUILD
#define VAPI DLLEXPORT
#else
#define VAPI DLLIMPORT
#endif

#endif
