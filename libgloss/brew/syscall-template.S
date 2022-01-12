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
 * $r3        -- pointer to errno
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
 * errno      -- updated as(if) needed
 * 
 * In other words, this is normal function calling conventions,
 * with the addition of $r3 pointing to errno on entry.
 */

  .globl   FN_NAME
  .type    FN_NAME,@function
  .text
FN_NAME:
  syscall
  .hword  SYSCALL_NO
  RET
.Lend:
  .size    FN_NAME,.Lend-FN_NAME
