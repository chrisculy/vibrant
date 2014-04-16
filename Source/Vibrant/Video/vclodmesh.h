/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vclodmesh.h
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

#ifndef VIBRANT_CLODMESH_H
#define VIBRANT_CLODMESH_H

#include "vmesh.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates continuous level of detail 3D meshes.
     * 
     * @author Chris Culy
     */
    class VAPI CLODMesh : public Mesh
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            CLODMesh ();

            /**
             * @brief Destructor.
             */
            ~CLODMesh ();
            
            //************************ General Interface ***********************//
    };

}

#endif
