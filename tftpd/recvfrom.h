/* $Id$ */
/* ----------------------------------------------------------------------- *
 *   
 *   Copyright 2001 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software available under the same license
 *   as the "OpenBSD" operating system, distributed at
 *   http://www.openbsd.org/.
 *
 * ----------------------------------------------------------------------- */

/*
 * recvfrom.h
 *
 * Header for recvfrom substitute
 *
 */

#include "config.h"

int
myrecvfrom(int s, void *buf, int len, unsigned int flags,
	   struct sockaddr *from, int *fromlen,
	   struct sockaddr_in *myaddr);
