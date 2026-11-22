/* timespec_get.c -- C11 timespec_get for Brew.
 *
 * Copyright (c) 2026 Andras Tantos
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

/* newlib's <time.h> declares timespec_get for every target, but only
   Cygwin defines it.  This one reads the time through gettimeofday, so
   its resolution is a microsecond.  In the operating environment
   _gettimeofday fails (ENOSYS) unless the board defines its own, and
   timespec_get then returns 0.  */

#include <time.h>
#include <sys/time.h>

int
timespec_get (struct timespec *ts, int base)
{
  struct timeval tv;

  if (base != TIME_UTC || gettimeofday (&tv, NULL) != 0)
    return 0;
  ts->tv_sec = tv.tv_sec;
  ts->tv_nsec = tv.tv_usec * 1000L;
  return base;
}
