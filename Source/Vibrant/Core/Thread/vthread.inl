/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vthread.inl
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision: 130 $
 * $Author: Chris $
 * $Date: 2008-01-16 22:31:42 -0500 (Wed, 16 Jan 2008) $
 */

namespace Vibrant
{
    
    inline const int Thread::GetPriority ()
    {
        return priority;
    }
    
    inline const unsigned int Thread::GetID ()
    {
        return id;
    }
    
    inline const String& Thread::GetName ()
    {
        return name;
    }

}
