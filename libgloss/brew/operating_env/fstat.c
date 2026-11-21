/* fstat.c -- standard streams are the console
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
#include <string.h>
#include <sys/stat.h>

/* Reports the standard streams as character devices, so stdio line-buffers
   them. There is no file system.  */
int
_fstat (int fd, struct stat *st)
{
  if (fd < 0 || fd > 2)
    {
      errno = EBADF;
      return -1;
    }
  memset (st, 0, sizeof (*st));
  st->st_mode = S_IFCHR;
  return 0;
}
