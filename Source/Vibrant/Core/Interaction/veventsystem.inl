/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: veventsystem.inl
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

namespace Vibrant
{
    
    template< typename EventHandler, typename Sender, typename Parameter >
    EventSystem::EventListener< EventHandler, Sender, Parameter >::EventListener ( EventHandler* eventHandler,
        EventHandlerCallback callback )
    {
        this->eventHandler = eventHandler;
        this->callback = callback;
    }
    
    template< typename EventHandler, typename Sender, typename Parameter >
    bool EventSystem::EventListener< EventHandler, Sender, Parameter >::Notify ( Sender* sender, Parameter parameter )
    {
        return ( eventHandler->*callback ) ( sender, parameter );
    }
    
    template< typename EventHandler, typename Sender, typename Parameter >
    EventSystem::EventListener< EventHandler, Sender, Parameter >* EventSystem::MakeListener ( EventHandler* eventHandler,
        bool(EventHandler::*callback) ( Sender* sender, Parameter parameter ) )
    {
        return new EventSystem::EventListener< EventHandler, Sender, Parameter > ( eventHandler, callback );
    }
    
    template< typename EventHandler, typename Sender, typename Parameter >
    EventSystem::EventListener< EventHandler, Sender, Parameter >* EventSystem::MakeListener ( EventHandler& eventHandler,
        bool(EventHandler::*callback) ( Sender* sender, Parameter parameter ) )
    {
        return new EventSystem::EventListener< EventHandler, Sender, Parameter > ( &eventHandler, callback );
    }

}
