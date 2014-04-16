/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vevent.inl
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

#include "veventsystem.h"
#include "vlinkedlist.h"

namespace Vibrant
{
    
    template< typename Sender, typename Parameter > Event< Sender, Parameter >::Event ()
    {
        /* stub function */
    }
    
    template< typename Sender, typename Parameter > Event< Sender, Parameter >::~Event ()
    {
        /* stub function */
    }
    
    template< typename Sender, typename Parameter > inline void Event< Sender, Parameter >::Subscribe ( EventSystem::Listener< Sender,
        Parameter >* listener, bool acceptsHandledEvents )
    {
        ( acceptsHandledEvents ) ? listeners.PushBack ( listener ) : listenersUnhandledEventsOnly.PushBack ( listener );
    }
    
    template< typename Sender, typename Parameter > inline void Event< Sender, Parameter >::Unsubscribe ( EventSystem::Listener< Sender,
        Parameter >* listener, bool acceptsHandledEvents )
    {
        ( acceptsHandledEvents ) ? listeners.Remove ( listener ) : listenersUnhandledEventsOnly.Remove ( listener );
    }
    
    template< typename Sender, typename Parameter > inline bool Event< Sender, Parameter >::Fire ( Sender* sender, Parameter parameter )
    {
        // Holds whether the event has been handled.
        bool handled = false;
        
        // Go through the event's listeners that are only notified
        // if the event has not already been handled and notify them.
        GNU_TYPENAME LinkedList< EventSystem::Listener< Sender, Parameter >* >::GNU_TEMPLATE Iterator< EventSystem::Listener< Sender,
            Parameter >* > iter = listenersUnhandledEventsOnly.StartIterator ();
        while ( iter != listenersUnhandledEventsOnly.EndIterator () )
        {
            handled |= iter.GetObject ()->Notify ( sender, parameter );
            iter.Next ();
            
            // If the event has been handled, we are done notifying these listeners.
            if ( handled )
            {
                break;
            }
        }

        // Go through the event's normal listeners and notify them.
        iter = listeners.StartIterator ();
        while ( iter != listeners.EndIterator () )
        {
            handled |= iter.GetObject ()->Notify ( sender, parameter );
            iter.Next ();
        }
        
        return handled;
    }

}
