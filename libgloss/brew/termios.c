/* termios.c -- terminal control.
 *
 * Copyright (c) 2023 Andras Tantos
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

// We use local includes to make sure we pick up the headers we're building with instead of any pre-installed ones.
// This is because the libgloss target folder is not by default part of the system includes during build.
#include "termios.h"
#include "ioctl.h"
#include <errno.h>

int tcgetattr(int fd,struct termios *termios_p)
{
  return ioctl(fd,TCGETS,termios_p);
}


int tcsetattr(int fd,int optional_actions,const struct termios *termios_p)
{
  int cmd;

  switch (optional_actions) {
    case TCSANOW:
      cmd = TCSETS;
    break;
    case TCSADRAIN:
      cmd = TCSETSW;
    break;
    case TCSAFLUSH:
      cmd = TCSETSF;
    break;
    default:
      errno = EINVAL;
      return -1;
    }
  return ioctl(fd,cmd,termios_p);
}
