/*
 * syscall-template.S -- generic syscall interface for brew
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
#include "brew-calls.h"
#include "macros.S"

/* Every syscall follows the same, generic layout:
 * Input:
 * $lr        -- the current value of errno
 * $r4        -- first argument (if any)
 * $r5        -- second argument (if any)
 * $r6        -- third argument (if any)
 * $r7        -- fourth argument (if any)
 *            -- all other arguments (if any) are on the stack.
 *
 * Output:
 * $r4        -- first return value (if any)
 * $r5        -- second return value (if any)
 * $r6        -- third return value (if any)
 * $r7        -- fourth return value (if any)
 * $lr        -- the new value of errno
 *
 * In other words, this is normal function calling conventions,
 * with the addition of errno passed in and out in $lr (see
 * "Syscalls" in brew/docs_src/abi.rst).
 *
 * errno here is newlib's global 'errno' (newlib/libc/reent/reent.c),
 * not the reentrant one C code reads through __errno (): the _r
 * wrappers (_open_r etc.) clear it before calling us and copy it to
 * _REENT->_errno when the call leaves it non-zero.
 */

  .global  FN_NAME
  .extern  errno
  .type    FN_NAME,@function
  .text
FN_NAME:
  /* NOTE: if stack changes - for example if these things get inlined,
     parameters on stack (open comes to mind) would shift too. So, if
     this code is touched, interp.c in binutils would need to be changed
     accordingly
  */
  $sp <- short $sp + (-4)
  mem[$sp] <- $lr
  $lr <- mem[errno]
  syscall
  .hword  SYSCALL_NO
  mem[errno] <- $lr
  $lr <- mem[$sp]
  $sp <- short $sp + 4
  $pc <- $lr
.Lend:
  .size    FN_NAME,.Lend-FN_NAME

/* This object does not need an executable stack.  */
  .section .note.GNU-stack,"",@progbits
