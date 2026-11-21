/* posix.c -- public names for syscalls newlib has no wrapper for
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

/* newlib calls _open etc. through reentrant wrappers (_open_r ...) that
   copy the syscall stubs' errno, newlib's global 'errno', into the
   reentrant errno C code reads.  chdir, chmod and utime have no such
   wrappers in newlib, so define them here the same way.  They are weak,
   so a program can still provide its own.  */

#include <reent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

/* The global errno the stubs set (newlib/libc/reent/reent.c); <errno.h>
   would make 'errno' the reentrant one.  */
extern int errno;

extern int _chdir (const char *path);
extern int _chmod (const char *path, mode_t mode);
extern int _utime (const char *path, const struct utimbuf *times);

#define CALL_WITH_ERRNO(call)                                   \
  do                                                            \
    {                                                           \
      int ret;                                                  \
      errno = 0;                                                \
      if ((ret = (call)) == -1 && errno != 0)                   \
        _REENT_ERRNO (_REENT) = errno;                          \
      return ret;                                               \
    }                                                           \
  while (0)

int __attribute__ ((weak))
chdir (const char *path)
{
  CALL_WITH_ERRNO (_chdir (path));
}

int __attribute__ ((weak))
chmod (const char *path, mode_t mode)
{
  CALL_WITH_ERRNO (_chmod (path, mode));
}

/* newlib's <utime.h> declares no utime ().  */
int utime (const char *path, const struct utimbuf *times);

int __attribute__ ((weak))
utime (const char *path, const struct utimbuf *times)
{
  CALL_WITH_ERRNO (_utime (path, times));
}
