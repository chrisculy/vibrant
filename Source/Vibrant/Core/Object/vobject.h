/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vobject.h
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

#ifndef VIBRANT_OBJECT_H
#define VIBRANT_OBJECT_H

#include "varray.h"
#include "vevent.h"
#include "vhashtable.h"
#include "vpointable.h"
#include "vpointer.h"
#include "vreader.h"
#include "vrtti.h"
#include "vserializable.h"
#include "vstring.h"
#include "vwriter.h"

namespace Vibrant
{
    
    // Forward declaration of the Controller class.
    // Note: This must be declared and then
    // included at the end of the file because
    // Controller is derived from Object and
    // Object has to be defined first.
    // (It is included so that something that has
    // a declaration from this file will also have
    // the definition-this is used by Pointer.)
    class Controller;
    
    /**
     * @brief Defines behavior for all objects within the engine.
     * 
     * <p>
     * Includes such things as streaming capabilities, run-time type
     * identification, identification through integer IDs and string IDs,
     * smart pointers, and controllers(anything that alters a
     * characteristic over time)
     * </p>
     * 
     * @see Controller
     * @see Pointable
     * @see Pointer
     * @see Reader
     * @see RTTI
     * @see Serializable
     * @see Writer
     * @author Chris Culy
     */
    class VAPI Object : public Pointable, public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Destructor.
             */
            virtual ~Object ();

            //************************ General Interface ***********************//
            

            //******************* String name and ID# system *******************//

            /**
             * @brief Sets the object's name identifier.
             *
             * @param name The new name for the object.
             * @throws NullPointerException If name is null.
             * @see #GetName
             */
            virtual void SetName ( const String name );

            /**
             * @brief Retrieves the object's name identifier.
             *
             * @return The object's name, or null if the object has no name.
             * @see #SetName
             */
            virtual String GetName () const;

            /**
             * @brief Retrieves the object's unique identification number.
             *
             * @return The object's identification number.
             * @see #GetNextID
             */
            virtual unsigned int GetID () const;

            /**
             * @brief Retrieves the next available identification number.
             *
             * @return The next available identification number.
             * @see #GetID
             */
            static unsigned int GetNextID ();

            /**
             * @brief Retrieves an object by its name.
             * 
             * @param name The name of the desired object.
             * @return The first object to be named <code>name</code>.
             */
            virtual Pointer< Object > GetObject ( String name ) const;

            /**
             * @brief Retrieves an object by its id.
             * 
             * @param id The desired object's unique id.
             * @return The specified object.
             */
            virtual Pointer< Object > GetObject ( unsigned int id ) const;

            /**
             * @brief Retreives all objects by a specified name.
             * 
             * @param name The name of the object(s).
             * @return All objects with the specified name.
             */
            virtual Pointer< Object >* GetAllObjects ( String name ) const;

            //******************* String name and ID# system *******************//
            

            //*************************** RTTI system **************************//

            /**
             * @brief Retrieves the object's type.
             * 
             * @return The object's type.
             * @see RTTI
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all objects.
             * 
             * @return The Object RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            /**
             * @brief Returns whether this type is exactly equal
             * to the specified type or not.
             *
             * @param type The type to compare to.
             * @return <code>true</code> if this object's type is exactly equal to
             *      <code>type</code>; <code>false</code> otherwise.
             * @see #IsExactlyTypeOf
             * @see RTTI
             */
            virtual bool IsExactly ( const RTTI* type ) const;

            /**
             * @brief Returns whether this type is derived
             * from the specified type or not.
             *
             * @param type The type to compare to.
             * @return <code>true</code> if this object's type is derived from
             *      <code>type</code>; <code>false</code> otherwise.
             * @see #IsDerivedTypeOf
             * see RTTI
             */
            virtual bool IsDerived ( const RTTI* type ) const;

            /**
             * @brief Returns whether this type is exactly equal
             * to the specified object's type or not.
             *
             * @param obj The object to compare to.
             * @return <code>true</code> if this object's type is exactly equal to
             *      the type of <code>obj</code>; <code>false</code> otherwise.
             * @see #IsExactly
             * @see RTTI
             */
            virtual bool IsExactlyTypeOf ( const Object* obj ) const;

            /**
             * @brief Returns whether this type is derived
             * from the specified object's type or not.
             *
             * @param obj The object to compare to.
             * @return <code>true</code> if this object's type is derived from
             *      the type of <code>obj</code>; <code>false</code> otherwise.
             * @see #IsDerived
             * @see RTTI
             */
            virtual bool IsDerivedTypeOf ( const Object* obj ) const;

            //*************************** RTTI system **************************//
            

            //************************ Controller system ***********************//

            /**
             * @brief Adds the specified controller to this object's controllers.
             * 
             * @param controller The controller to add.
             */
            virtual void AddController ( Controller* controller );

            /**
             * @brief Removes the specified controller from this object's controllers.
             * 
             * @param controller The controller to remove.
             */
            virtual void RemoveController ( Controller* controller );

            /**
             * @brief Removes all of this object's controllers.
             */
            virtual void RemoveAllControllers ();

            /**
             * @brief Gets the controller at the specified index in
             * this object's list of controllers.
             * 
             * @param index The index of the desired controller.
             * @return The specified controller.
             */
            virtual Pointer< Controller > GetController ( int index ) const;

            /**
             * @brief Retrieves the number of controllers that the object has.
             * 
             * @return The number of controllers that the object has.
             */
            virtual int ControllerCount () const;

            /**
             * @brief Goes through the object's controllers and updates them.
             * 
             * @param time The application's current time (in milliseconds).
             * @returns <code>true</code> if all controllers updated successfully;
             *  <code>false</code> otherwise.
             */
            virtual bool UpdateControllers ( long time );

            //************************ Controller system ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            virtual const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            virtual void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            virtual void Read ( Reader* reader );

            //************************ Streaming system ************************//
            

            //************************* Copying system *************************//

            /**
             * @brief Copies the object. This is implemented by streaming the object to
             * a buffer and then loading it back in to a new location in memory.
             * 
             * @param createNewName Specifies whether a unique should be
             *      auto-generated using {@link #uniqueNameCharacter} or not.
             * @return A smart pointer to a copy of this object.
             */
            virtual Pointer< Object > Copy ( bool createNewName = true ) const;

            /**
             * @brief This character is appended to a name when an object
             * is copied and the name needs to be unique. For example,
             *
             * <pre>
             *      ObjectPtr obj1 = < smart pointer to some Object instance >;
             *      obj1->SetName ( "myObject" );
             *      
             *      ObjectPtr obj2 = obj1->Copy ();
             *      // Since createNewName is true
             *      // by default, we don't set it. Now, if
             *      // Object::uniqueNameCharacter was '$', then
             *      // obj->GetName () would return "myObject$".
             * </pre>
             */
            static char uniqueNameCharacter;

            //************************* Copying system *************************//

        protected:
            
            /**
             * @brief Default constructor (protected to make this an abstract class).
             */
            Object ();

            /**
             * @brief Holds all objects that are currently alive.
             */
            static Hashtable< unsigned int, Object* >* liveObjects;

        private:
            
            /** @brief Holds the name of the object. */
            String name;

            /** @brief Holds the unique ID of the object. */
            unsigned int id;

            /** @brief Holds the next available ID. */
            static unsigned int nextID;

            /** @brief Holds the object's controllers. */
            Array< Pointer< Controller > > controllers;
    };
    
    typedef Pointer< Object > ObjectPtr;

}

// Include the actual definition of Controller.
// (Controller was declared above Object.)
#include "vcontroller.h"

#endif
