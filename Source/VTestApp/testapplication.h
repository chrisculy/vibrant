/*
 * =======================================
 * ================ Osprey ===============
 * =======================================
 *
 * 
 * File: testapplication.h
 * 
 * 
 * --  Copyright (c) 2009-2010 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#ifndef TESTAPPLICATION_H_
#define TESTAPPLICATION_H_

#include "vconfig.h"
#include "vinput.h"
#include "vinputsystem.h"
#include "vlog.h"
#include "vmesh.h"
#include "vstring.h"
#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vwindowsapplication.h"
    
using namespace Vibrant;

namespace Osprey
{

    /**
     * A simple test application used as a scratch pad for initial development work on Osprey.
     */
    class TestApplication : public WindowsApplication
    {
        public:
            /**
             * @see WindowsApplication#WindowsApplication(Config, HINSTANCE)
             */
            TestApplication ( Config* config, HINSTANCE hInstance );
    
            /**
             * @brief Destructor.
             */
            ~TestApplication ();
    
            /**
             * @see Input#keyDown
             */
            bool OnKeyDown ( Input* input, KeyEventParam param );
    
            /**
             * @see Application#run()
             */
            void Run ();
    
        private:
            /** @brief Holds the logger. */
            Log logger;
    };

}

#endif

#endif
