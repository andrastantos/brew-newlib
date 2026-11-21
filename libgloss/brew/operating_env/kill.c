/* kill.c -- send a signal
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
#include <unistd.h>

/* The program is the only process (getpid() returns 1). There is nothing to
   report a signal to, so the default action ends the program with exit
   status 128 + the signal, as a shell reports it; abort() therefore exits
   with 134.  */
int
_kill (int pid, int sig)
{
  if (pid != 1 && pid != 0 && pid != -1)
    {
      errno = ESRCH;
      return -1;
    }
  if (sig == 0)
    return 0;
  _exit (128 + sig);
}
