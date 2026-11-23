/* A setjmp.c for Brew
   Copyright (C) 2022 Andras Tantos

   The authors hereby grant permission to use, copy, modify, distribute,
   and license this software and its documentation for any purpose, provided
   that existing copyright notices are retained in all copies and that this
   notice is included verbatim in any distributions. No written agreement,
   license, or royalty fee is required for any of the authorized uses.
   Modifications to this software may be copyrighted by their authors
   and need not follow the licensing terms described here, provided that
   the new terms are clearly indicated on the first page of each file where
   they apply.  */

# setjmp/longjmp for brew.
#
# setjmp saves the registers a call preserves (the ones gcc's
# CALL_USED_REGISTERS in gcc/config/brew/brew.h leaves 0): $r8-$r11, the
# frame and stack pointers $fp ($r12) and $sp ($r13), and the return address
# in $lr ($r14).
#
# The jmpbuf layout is the following (gdb's brew_get_longjmp_target reads
# the return address at 0x08):
#
# Register        jmpbuf offset
#   $sp             0x00
#   $fp             0x04
#   $lr             0x08
#   $r8             0x0c
#   $r9             0x10
#   $r10            0x14
#   $r11            0x18
#   (unused)        0x1c
#
# The size of the jump buffer is set by:
#    #define _JBLEN 8
# in ../../include/machine/setjmp.h

# Upon call, $r4 is set to the buffer address
#            $lr is set to the return address
# Upon exit, $r4 is set to 0.
  .text
  .global setjmp
  .type   setjmp,@function
setjmp:
  mem[$r4] <- $sp
  mem[$r4 + 0x04] <- $fp
  mem[$r4 + 0x08] <- $lr
  mem[$r4 + 0x0c] <- $r8
  mem[$r4 + 0x10] <- $r9
  mem[$r4 + 0x14] <- $r10
  mem[$r4 + 0x18] <- $r11
  $r4 <- $r4 - $r4 # Set return value to 0
  $pc <- $lr # return
.Lend1:
  .size  setjmp,.Lend1-setjmp

# Upon call, $r4 is set to the buffer address
#            $r5 is set to the desired return code
# Upon exit, $r4 is set to the desired return code, except if it was 0.
#                In that later case, $r4 is set to 1 (to avoid confusion
#                with the return values from initial setup).
  .global  longjmp
  .type  longjmp,@function
longjmp:
  $sp  <- mem[$r4]
  $fp  <- mem[$r4 + 0x04]
  $lr  <- mem[$r4 + 0x08]
  $r8  <- mem[$r4 + 0x0c]
  $r9  <- mem[$r4 + 0x10]
  $r10 <- mem[$r4 + 0x14]
  $r11 <- mem[$r4 + 0x18]
  $r4 <- $r5
  if $r4 == 0 $pc <- .Lreturn1
  $pc <- $lr
.Lreturn1:
  $r4 <- $r4 + 1
  $pc <- $lr
.Lend2:
  .size  longjmp,.Lend2-longjmp

/* This object does not need an executable stack.  */
  .section .note.GNU-stack,"",@progbits
