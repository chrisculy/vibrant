/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputdemo.h
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

#ifndef VIBRANT_INPUTDEMO_H
#define VIBRANT_INPUTDEMO_H

#include "vinput.h"
#include "vlog.h"

using namespace Vibrant;

/**
 * @brief Demonstrates the input system.
 * 
 * @author Chris Culy
 */
class InputDemo
{
    public:
        
        //************************ General Interface ***********************//

        /**
         * @brief Handles key down events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnKeyDown ( Input* input, KeyEventParam param );

        /**
         * @brief Handles key up events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnKeyUp ( Input* input, KeyEventParam param );

        /**
         * @brief Handles mouse button down events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnMouseButtonDown ( Input* input, MouseButtonEventParam param );

        /**
         * @brief Handles mouse button up events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnMouseButtonUp ( Input* input, MouseButtonEventParam param );

        /**
         * @brief Handles mouse button double click events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnMouseButtonDoubleClick ( Input* input, MouseButtonEventParam param );

        /**
         * @brief Handles mouse move events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnMouseMove ( Input* input, MouseMoveEventParam param );

        /**
         * @brief Handles mouse scroll events.
         * 
         * @param input The input system.
         * @param param The event's parameter (information).
         */
        bool OnMouseScroll ( Input* input, MouseScrollEventParam param );

        //************************ General Interface ***********************//

    private:
        
        /** @brief Holds the default logger. */
        Log vlog;
};

/** 
 * @brief Runs the input demo.
 * 
 * @return 0 on success; non-zero otherwise.
 */
int VInputDemo ();

#endif
