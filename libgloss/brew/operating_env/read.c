/* read.c -- read from the console
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
#include "devices.h"

/* Every file descriptor reads the console. Waits for the first byte, then
   returns what has arrived without waiting further, up to the end of a line.  */
int
_read (int fd, char *buf, int len)
{
  int n = 0;

  if (len <= 0)
    return 0;
  while ((__brew_console_base[CON_STATUS] & CON_STAT_RX_VALID) == 0)
    ;
  do
    {
      char c = __brew_console_base[CON_DATA];
      buf[n++] = c;
      if (c == '\n')
	break;
    }
  while (n < len && (__brew_console_base[CON_STATUS] & CON_STAT_RX_VALID) != 0);
  return n;
}
