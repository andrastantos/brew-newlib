/* write.c -- write to the console
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
#include "devices.h"

/* Every file descriptor writes the console.  */
int
_write (int fd, const char *buf, int len)
{
  int i;

  for (i = 0; i < len; ++i)
    {
      while ((__brew_console_base[CON_STATUS] & CON_STAT_TX_READY) == 0)
	;
      __brew_console_base[CON_DATA] = buf[i];
    }
  return len;
}
