/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsystem.h
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

#ifndef VSYSTEM_H
#define VSYSTEM_H

// Get all the important, static headers.
#include "vprecompiled.h"

namespace Vibrant
{
    
    // Compiler Specific Macros.
#ifdef _MSC_VER
#define GNU_TEMPLATE
#define GNU_TYPENAME
#define MSC_TYPENAME typename
#else
#define GNU_TEMPLATE template
#define GNU_TYPENAME typename
#define MSC_TYPENAME
#endif
    
    // System #define; one of:
#define SYSTEM_WINDOWS
    //#define SYSTEM_LINUX
    //#define SYSTEM_MAC
    //#define SYSTEM_GENERIC

    // Define debug mode:
#define VIBRANT_DEBUG_MODE
    
#ifdef SYSTEM_WINDOWS
    // Include definitions.
#define VIBRANT_AUDIO_INCLUDE_FILE "vwindowsaudio.h"
#define VIBRANT_CODEMODULE_INCLUDE_FILE "vwindowscodemodule.h"
#define VIBRANT_INPUT_INCLUDE_FILE "vwindowsinput.h"
#define VIBRANT_MUTEX_INCLUDE_FILE "vwindowsmutex.h"
#define VIBRANT_THREAD_INCLUDE_FILE "vwindowsthread.h"
#define VIBRANT_TIME_INCLUDE_FILE "vwindowstime.h"
    // Forward Class Declarations.
    class WindowsAudio;
    class WindowsCodeModule;
    class WindowsInput;
    class WindowsMutex;
    class WindowsThread;
    class WindowsTime;
    // Defines.
#define VIBRANT_AUDIO      WindowsAudio
#define VIBRANT_CODEMODULE WindowsCodeModule
#define VIBRANT_INPUT      WindowsInput
#define VIBRANT_MUTEX      WindowsMutex
#define VIBRANT_THREAD     WindowsThread
#define VIBRANT_TIME       WindowsTime
    // Typedefs.
    typedef SOCKET SystemSocket;
    typedef SOCKADDR SystemSocketAddress;
    typedef SOCKADDR_IN SystemSocketInternetAddress;
    typedef IN_ADDR SystemInternetAddress;
    typedef addrinfo SystemAddressInfo;
    typedef HMODULE CodeModuleHandle;
#else
#ifdef SYSTEM_LINUX
// Include definitions.
#define VIBRANT_AUDIO_INCLUDE_FILE "vlinuxaudio.h"
#define VIBRANT_CODEMODULE_INCLUDE_FILE "vlinuxcodemodule.h"
#define VIBRANT_INPUT_INCLUDE_FILE "vlinuxinput.h"
#define VIBRANT_MUTEX_INCLUDE_FILE "vlinuxmutex.h"
#define VIBRANT_THREAD_INCLUDE_FILE "vlinuxthread.h"
#define VIBRANT_TIME_INCLUDE_FILE "vlinuxtime.h"
// Forward Class Declarations.
class LinuxAudio;
class LinuxCodeModule;
class LinuxInput;
class LinuxMutex;
class LinuxThread;
class LinuxTime;
// Defines.
#define VIBRANT_AUDIO      LinuxAudio
#define VIBRANT_CODEMODULE LinuxCodeModule
#define VIBRANT_INPUT      LinuxInput
#define VIBRANT_MUTEX      LinuxMutex
#define VIBRANT_THREAD     LinuxThread
#define VIBRANT_TIME       LinuxTime
#elif defined SYSTEM_MAC
// Include definitions.
#define VIBRANT_AUDIO_INCLUDE_FILE "vmacaudio.h"
#define VIBRANT_CODEMODULE_INCLUDE_FILE "vmaccodemodule.h"
#define VIBRANT_INPUT_INCLUDE_FILE "vmacinput.h"
#define VIBRANT_MUTEX_INCLUDE_FILE "vmacmutex.h"
#define VIBRANT_THREAD_INCLUDE_FILE "vmacthread.h"
#define VIBRANT_TIME_INCLUDE_FILE "vmactime.h"
// Forward Class Declarations.
class MacAudio;
class MacCodeModule;
class MacInput;
class MacMutex;
class MacThread;
class MacTime;
// Defines.
#define VIBRANT_AUDIO      MacAudio
#define VIBRANT_CODEMODULE MacCodeModule
#define VIBRANT_INPUT      MacInput
#define VIBRANT_MUTEX      MacMutex
#define VIBRANT_THREAD     MacThread
#define VIBRANT_TIME       MacTime
#elif defined SYSTEM_GENERIC
// Include definitions.
#define VIBRANT_AUDIO_INCLUDE_FILE "vaudio.h"
#define VIBRANT_CODEMODULE_INCLUDE_FILE "vgenericcodemodule.h"
#define VIBRANT_INPUT_INCLUDE_FILE "vinput.h"
#define VIBRANT_MUTEX_INCLUDE_FILE "vgenericmutex.h"
#define VIBRANT_THREAD_INCLUDE_FILE "vgenericthread.h"
#define VIBRANT_TIME_INCLUDE_FILE "vgenerictime.h"
// Forward Class Declarations.
class Audio;
class Input;
class GenericCodeModule;
class GenericMutex;
class GenericThread;
class GenericTime;
// Defines.
#define VIBRANT_AUDIO      Audio
#define VIBRANT_CODEMODULE GenericCodeModule
#define VIBRANT_INPUT      Input
#define VIBRANT_MUTEX      GenericMutex
#define VIBRANT_THREAD     GenericThread
#define VIBRANT_TIME       GenericTime
#endif
// BSD Sockets Networking Typedefs.
typedef int SystemSocket;
typedef sockaddr SystemSocketAddress;
typedef sockaddr_in SystemSocketInternetAddress;
typedef in_addr SystemInternetAddress;
typedef addrinfo SystemAddressInfo;
// General Typedefs.
typedef int CodeModuleHandle;
#endif

}

#endif
