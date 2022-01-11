/*
 * sim-time.S -- time interface for moxie simulator
 * 
 * Copyright (c) 2022 Andras Tantos
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

#include "syscall.h"
#include "macros.S"

/*
 * Input:
 * $r4    -- address of time_t value to receive time or NULL.
 *
 * Output:
 * $r4    -- return time in seconds since jan1st 1970, or -1 on error.
 * errno  -- Set if an error
 */

  .globl   _time
  .type    _time,@function
  .weak    time
  .text
_time:
time:
  SYSCALLM SYS_time
  RET
.Lend:
  .size    _time,.Lend-_time
