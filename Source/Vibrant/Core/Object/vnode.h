/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnode.h
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

#ifndef VIBRANT_NODE_H
#define VIBRANT_NODE_H

#include "varray.h"
#include "vobject.h"
#include "vpointer.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates hierarchical behavior of objects.
     * 
     * @author Chris Culy
     */
    class VAPI Node : public Object
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Default constructor.
             */
            Node ();

            /**
             * @brief Constructs Node object and makes it a child of <code>parent</code>.
             *
             * @param parent The object that should be the new object's parent.
             *      If parent is null, the object is considered to be the root node
             *      (however, parent is null by default so don't use this constructor
             *      in the case of creating the root node).
             */
            Node ( Node *parent );

            /**
             * @brief Default destructor.
             */
            virtual ~Node ();

            /**
             * @brief Returns whether this node has a parent or not.
             * 
             * @return <code>true</code> if this node has a parent,
             *      <code>false</code> if this is the root node.
             */
            bool HasParent () const;

            /**
             * <p>
             * Returns whether this node has one or more children.
             * </p>
             * 
             * @return <code>true</code> if this node has one or more children,
             *      <code>false</code> if this node has no children.
             */
            bool HasChildren () const;

            /**
             * @brief Returns the number of children this object has.
             * 
             * @return The number of children this object has.
             */
            int ChildCount () const;

            /**
             * @brief Adds the object to this object's children.
             * 
             * @param child The child to add.
             * @throws NullPointerException If newChild is null.
             * @see #RemoveChild
             * @see #RemoveChildAt
             */
            void AddChild ( Node* child );

            /**
             * @brief Removes the specified child from this object's children.
             * 
             * @param child The child to remove.
             * @return <code>true</code> if the child was found and removed,
             *      <code>false</code> otherwise.
             * @throws NullPointerException If child is null.
             * @see #RemoveChildAt
             */
            bool RemoveChild ( Node* child );

            /**
             * @brief Removes the child at the given index.
             *
             * @param index The index of the child to remove.
             * @throws IndexOutOfBoundsException If ( index < 0 ) or
             *      ( index > ChildCount () ).
             * @see #RemoveChild
             */
            void RemoveChildAt ( int index );

            /**
             * @brief Retrieves the child at the given index.
             *
             * @param index The index of the child to get.
             * @throws IndexOutOfBoundsException If ( index < 0 ) or
             *      ( index > ChildCount () ).
             */
            Node* GetChild ( int index ) const;

            /**
             * @brief Retrieves the parent.
             */
            Node* GetParent () const;

            /**
             * @brief Updates this node and all its children.
             * 
             * @param time The current system time in milliseconds.
             */
            virtual void Update ( long time ) = 0;

            //************************ General Interface ***********************//
            

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
            

            //*************************** RTTI system **************************//

            /**
             * @see Object#GetType()
             */
            virtual const RTTI* GetType () const;

            /**
             * @brief Retrieves the RTTI for all nodes.
             * 
             * @return The Node RTTI.
             * @see RTTI
             */
            static RTTI* GetRTTI ();

            //*************************** RTTI system **************************//

        private:
            
            /** @brief Holds the node's parent. */
            Node* parent;

            /** @brief Holds the node's children. */
            Array< Node* > children;
    };
    
    typedef Pointer< Node > NodePtr;

}

#endif
