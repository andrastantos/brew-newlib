/* macros.S -- common macros for brew.
 * 
 * Copyright (c) 2022  Andras Tantos
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

/* Stack is pre-decrement for push, and post-increment for pop */

  .macro CALL label, temp_reg=$r3
  \temp_reg <- $pc + 16
  $sp <- $sp - 4
  mem[$sp] <- \temp_reg
  $pc <- \label
  .endm

  .macro RET
  $sp <- $sp + 4
  $pc <- mem[$sp,(-4)]
  .endm

  .macro SYSCALLM syscall_no
    syscall
    .hword \syscall_no
.endm
