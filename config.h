/* -*- c -*- ------------------------------------------------------------- *
 *   
 *   Copyright 2001 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software available under the same license
 *   as the "OpenBSD" operating system, distributed at
 *   http://www.openbsd.org/.
 *
 * ----------------------------------------------------------------------- */
/* $Id$ */

/*
 * config.h
 *
 * Sets up a common baseline environment, based on "autoconf" findings...
 */

#ifndef CONFIG_H
#define CONFIG_H 1

/* Must be included before we include any system headers! */
#include "acconfig.h"

/* This is necessary on Solaris with gcc */
#define _XPG4_2
#define _XOPEN_SOURCE
#define __EXTENSIONS__

/* Standard includes */

#include <stdio.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#ifdef STDC_HEADERS
#include <stdlib.h>
#include <stddef.h>
#else
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#endif

#ifdef HAVE_MEMORY_H
#ifndef STDC_HEADERS
#include <memory.h>
#endif
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif 

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#else
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <setjmp.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* If we don't have intmax_t, try creating it */

#ifndef HAVE_INTMAX_T
#ifdef HAVE_LONG_LONG
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
#define PRIdMAX	"Ld"
#define PRIuMAX "Lu"
#define PRIxMAX "Lx"
#define INTMAX_C(x)  (x##LL)
#define UINTMAX_C(x) (x##ULL)
#else
typedef long intmax_t;
typedef unsigned long uintmax_t;
#define PRIdMAX "ld"
#define PRIuMAX "lu"
#define PRIxMAX "lx"
#define INTMAX_C(x)  (x##L)
#define UINTMAX_C(x) (x##UL)
#endif
#endif

/* Even if intmax_t is defined, we may need this (Solaris 8 braindamage) */
#ifndef HAVE_STRTOUMAX
#if defined(HAVE_LONG_LONG) && defined(HAVE_STRTOULL)
#define strtoumax(p,e,b) ((uintmax_t)strtoull(p,e,b))
#else
#define strtoumax(p,e,b) ((uintmax_t)strtoul(p,e,b))
#endif
#endif

/* A lot of this is old BSD code.  Some newer systems don't approve. */

/* The type used by htons(), ntohs() */
#ifndef HAVE_U_SHORT
#ifdef HAVE_UINT16_T
typedef uint16_t u_short;
#else
typedef unsigned short u_short;
#endif
#endif

/* The type used to htonl(), ntohl() */
#ifndef HAVE_U_LONG
#ifdef HAVE_UINT32_T
typedef uint32_t u_long;
#else
typedef unsigned long u_long;
#endif
#endif

/* sysexits.h */

#ifdef HAVE_SYSEXITS_H
#include <sysexits.h>
#else
#define EX_USAGE        64      /* command line usage error */
#define EX_DATAERR      65      /* data format error */
#define EX_NOINPUT      66      /* cannot open input */
#define EX_NOUSER       67      /* addressee unknown */
#define EX_NOHOST       68      /* host name unknown */
#define EX_UNAVAILABLE  69      /* service unavailable */
#define EX_SOFTWARE     70      /* internal software error */
#define EX_OSERR        71      /* system error (e.g., can't fork) */
#define EX_OSFILE       72      /* critical OS file missing */
#define EX_CANTCREAT    73      /* can't create (user) output file */
#define EX_IOERR        74      /* input/output error */
#define EX_TEMPFAIL     75      /* temp failure; user is invited to retry */
#define EX_PROTOCOL     76      /* remote error in protocol */
#define EX_NOPERM       77      /* permission denied */
#define EX_CONFIG       78      /* configuration error */
#endif

/* If we don't have sigsetjmp() et all, setjmp() will have to do */

#ifndef HAVE_SIGSETJMP
#define sigsetjmp(x,y)  setjmp(x)
#define siglongjmp(x,y) longjmp(x,y)
#define sigjmp_buf jmp_buf
#endif

/* How do we annotate unused data items? */

#ifndef UNUSED
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

/* Sometimes IPPORT_TFTP isn't defined */

#ifndef HAVE_IPPORT_TFTP_DEFINITION
#ifndef IPPORT_TFTP
#define IPPORT_TFTP 69
#endif
#endif

#endif
