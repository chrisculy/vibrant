/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: veventsystem.h
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

#ifndef VIBRANT_EVENTSYSTEM_H
#define VIBRANT_EVENTSYSTEM_H

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the event system, which includes
     * the definitions and functionality needed for event listeners.
     * 
     * @see Event
     * @author Chris Culy
     */
    class EventSystem
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Encapsulates the listener interface.
             * 
             * @author Chris Culy
             */
            template< typename Sender, typename Parameter >
            class Listener
            {
                public:
                    
                    /**
                     * @brief Notifies the listener of an event from the
                     * given sender with the given parameter.
                     * 
                     * @param sender The sender of the event.
                     * @param parameter The parameter of the event (if there is one).
                     * @return <code>true</code> if the listener handled the event;
                     *      <code>false</code> otherwise.
                     */
                    virtual bool Notify ( Sender* sender, Parameter parameter ) = 0;
            };

            /**
             * @brief Encapsulates event listeners.
             * 
             * @author Chris Culy
             */
            template< typename EventHandler, typename Sender, typename Parameter >
            class EventListener : public EventSystem::Listener< Sender, Parameter >
            {
                    /** @brief The function pointer signature for listener callbacks. */
                    typedef bool (EventHandler::*EventHandlerCallback) ( Sender* sender, Parameter parameter );

                public:
                    
                    /**
                     * @brief Constructor.
                     * 
                     * @param eventHandler The object that will handle the event.
                     * @param callback The member function callback that is called
                     *      when the listener is notified.
                     */
                    EventListener ( EventHandler* eventHandler, EventHandlerCallback callback );

                    /**
                     * @see EventSystem::Listener#Notify
                     */
                    bool Notify ( Sender* sender, Parameter parameter );

                private:
                    
                    /** @brief Holds the object that will handle the event. */
                    EventHandler* eventHandler;

                    /** @brief Holds the member function callback that is called
                     * when the listener is notified that the event has been fired. */
                    EventHandlerCallback callback;
            };

            /**
             * @brief Makes a listener from the given event handling
             * object and a given member function of the correct signature.
             * 
             * @param eventHandler The object that will handle the event.
             * @param callback The member function callback that is called
             *      when the listener is notified.
             * @return An event listener created from the given information.
             */
            template< typename EventHandler, typename Sender, typename Parameter >
            static EventSystem::EventListener< EventHandler, Sender, Parameter >* MakeListener ( EventHandler* eventHandler,
                bool(EventHandler::*callback) ( Sender* sender, Parameter parameter ) );

            /**
             * @see EventSystem#MakeListener
             */
            template< typename EventHandler, typename Sender, typename Parameter >
            static EventSystem::EventListener< EventHandler, Sender, Parameter >* MakeListener ( EventHandler& eventHandler,
                bool(EventHandler::*callback) ( Sender* sender, Parameter parameter ) );
            
            //************************ General Interface ***********************//
    };

}

// Include inline definitions.
#include "veventsystem.inl"

#endif
