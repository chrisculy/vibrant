/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsockettype.h
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

#ifndef VIBRANT_SOCKETTYPE_H
#define VIBRANT_SOCKETTYPE_H

namespace Vibrant
{
    
    /**
     * @brief Represents the supported socket protocols:
     * 
     * <p>
     * The socket types:
     * <ul>
     *  <li>SOCKET_TCP</li>
     *  <li>SOCKET_UDP</li>
     *  <li>SOCKET_RELIABLE_UDP</li>
     * </ul>
     * </p>
     * 
     * @see Socket
     */
    enum SocketType
    {
        SOCKET_TCP = SOCK_STREAM,
        SOCKET_UDP = SOCK_DGRAM,
        SOCKET_RELIABLE_UDP = 0
    };

}

#endif
