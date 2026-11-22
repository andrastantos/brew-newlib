/* nosys.c -- calls the operating environment can't provide
 *
 * Copyright (c) 2026  Andras Tantos
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */
#include <errno.h>

/* Compiled once per function, with -DFN_NAME=_open etc. There is no file
   system or clock: fail with ENOSYS. Arguments are ignored.

   With -DWEAK the stub is weak, so a definition elsewhere replaces it even
   when it is linked from a library after libbrew.a.  _getentropy is: bare
   metal has no entropy source, and without one newlib's arc4random (which
   libstdc++'s std::random_device uses by default) kills the program with
   SIGKILL.  A board with a hardware random source provides
   int _getentropy (void *buf, size_t len), returning 0 on success.  */
#ifdef WEAK
__attribute__ ((weak))
#endif
int
FN_NAME (void)
{
  errno = ENOSYS;
  return -1;
}

#ifdef ALIAS_NAME
/* The public name, for calls newlib has no wrapper for (chmod etc.).  */
#define STR_(x) #x
#define STR(x) STR_(x)
int ALIAS_NAME (void) __attribute__ ((weak, alias (STR (FN_NAME))));
#endif
