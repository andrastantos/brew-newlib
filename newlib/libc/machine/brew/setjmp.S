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
# During setjmp we need to save all registers not marked in CALL_USED_REGISTERS
# for gcc, that is, all registers that that are available across function calls.
# On top of this, of course we'll have to preserve the stack-frame, so $sp and
# $fp goes in here too.
# Finally we'll have to save the return address, which is in $lr
#
# Thus, the jmpbuf layout is the following:
#
# Register        jmpbuf offset
#   $sp             0x00
#   $fp             0x04
#   $lr             0x08
#   $r8             0x0c
#   $r9             0x10
#   $r10            0x14
#   $r11            0x18
#
# The size of the jump buffer is set by:
#    #define _JBLEN 7
# in ../../include/machine/setjmp.h

# Upon call, $r4 is set to the buffer address
#            $lr is set to the return address
# Upon exit, $r4 is set to 0.
  .text
  .global setjmp
  .type   setjmp,@function
setjmp:
  mem[$a0] <- $sp
  mem[$a0 + 0x04] <- $fp
  mem[$a0 + 0x08] <- $lr
  mem[$a0 + 0x0c] <- $r8
  mem[$a0 + 0x10] <- $r9
  mem[$a0 + 0x14] <- $r10
  mem[$a0 + 0x18] <- $r11
  $a0 <- tiny 0 # Set return value to 0
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
  $sp  <- mem[$a0]
  $fp  <- mem[$a0 + 0x04]
  $lr  <- mem[$a0 + 0x08]
  $r8  <- mem[$a0 + 0x0c]
  $r9  <- mem[$a0 + 0x10]
  $r10 <- mem[$a0 + 0x14]
  $r11 <- mem[$a0 + 0x18]
  $a0 <- $a1
  if $a0 == 0 $pc <- .Lreturn1
  $pc <- $lr
.Lreturn1:
  $a0 <- $a0 + 1
  $pc <- $lr
.Lend2:
  .size  longjmp,.Lend2-longjmp
