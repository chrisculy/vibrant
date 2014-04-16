/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vevent.h
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

#ifndef VIBRANT_EVENT_H
#define VIBRANT_EVENT_H

#include "veventsystem.h"
#include "vlinkedlist.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates an event.
     * 
     * <p>
     * Note: The order of listeners that only handle
     * unhandled events matters, because the order in
     * which the listeners subscribed is the order in
     * which they are notified. Thus, if one listener
     * subscribes first and handles the event when it is
     * fired, then the other listeners are not notified
     * (because they only handle unhandled events).
     * (This can be specialized by deriving from Event and
     * overriding the Fire() function.)
     * </p>
     * 
     * <p>
     * <b>Sample Usage</b><br><br>
     * <pre><code>
     * class MySender
     * {
     *     public:
     *         Event<MySender, int> senderEvent;
     * };
     * 
     * class MyListener
     * {
     *     bool OnSenderEvent ( MySender* sender, int arg )
     *     {
     *         std::cout << "Handled MySender event with arg = " << arg << ".\n";
     *         return false;
     *     }
     * };
     * 
     * void SomeFunction ()
     * {
     *     MySender mySender;
     *     MyListener myListener;
     *     
     *     mySender.senderEvent.Subscribe ( EventSystem::MakeListener ( &myListener, &MyListener::OnSenderEvent ) );
     *     mySender.senderEvent.Fire ( &mySender, 2 );
     * }
     * </code></pre>
     * </p>
     * 
     * @see EventSystem
     * @author Chris Culy
     */
    template< typename Sender, typename Parameter >
    class Event
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Event ();

            /**
             * @brief Destructor.
             */
            ~Event ();

            /**
             * @brief Allows a listener to subscribe to this event so
             * that it is notified when the event is fired.
             * 
             * @param listener The listener that wants to subscribe to this event.
             * @param acceptsHandledEvents Whether the listener accepts already handled
             *      events or just events that have not yet been handled (by other
             *      listeners that only handle unhandled events).
             */
            void Subscribe ( EventSystem::Listener< Sender, Parameter >* listener, bool acceptsHandledEvents = true );

            /**
             * @brief Allows a listener to unsubscribe from this event so
             * that it is no longer notified when the event is fired.
             * 
             * @param listener The listener that wants to unsubscribe from this event.
             * @param acceptsHandledEvents Whether the listener accepted already handled
             *      events or just events that had not yet been handled (by other
             *      listeners that only handle unhandled events).
             */
            void Unsubscribe ( EventSystem::Listener< Sender, Parameter >* listener, bool acceptsHandledEvents = true );

            /**
             * @brief Fires the event and notifies all listeners to the event.
             * 
             * @param sender The sender of the event.
             * @param parameter The parameter for the event (if there is one).
             * @return <code>true</code> if the event was handled by any of
             *      its listeners;<code>false</code> otherwise.
             */
            bool Fire ( Sender* sender, Parameter parameter );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the event's listeners (normal). */
            LinkedList< EventSystem::Listener< Sender, Parameter >* > listeners;

            /** @brief Holds the event's listeners (that only handle unhandled events). */
            LinkedList< EventSystem::Listener< Sender, Parameter >* > listenersUnhandledEventsOnly;

            /** @brief Copy constructor (hidden to disallow usage). */
            Event ( const Event& );

            /** @brief Assignment operator (hidden to disallow usage). */
            Event& operator= ( const Event& );
    };

}

// Include inline definitions.
#include "vevent.inl"

#endif

