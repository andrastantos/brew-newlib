/*
 * sim-write.S -- write interface for moxie simulator
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
 * $r4    -- File descriptor.
 * $r5    -- String to be printed.
 * $r6    -- Length of the string.
 *
 * Output:
 * $r4    -- Length written or -1.
 * errno  -- Set if an error
 */

  .globl   _write
  .type    _write,@function
  .weak    write
  .text
_write:
write:
  SYSCALLM SYS_write
  RET
.Lend:
  .size    _write,.Lend-_write
