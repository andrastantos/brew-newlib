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
# Currently, those are $r11...$14.
# On top of this, of course we'll have to preserve the stack-frame, so $sp and
# $fp goes in here too.
# Finally we'll have to save the return address, which is in $r3
#
# Thus, the jmpbuf layout is the following:
#
# Register        jmpbuf offset
#   $sp             0x00
#   $fp             0x04
#   $r3             0x08
#   $r11            0x0c
#   $r12            0x10
#   $r13            0x14
#   $r14            0x18

# Upon call, $r4 is set to the buffer address
#            $r3 is set to the return address
# Upon exit, $r4 is set to 0.
  .text
  .global setjmp
  .type   setjmp,@function
setjmp:
  mem[$r4] <- $sp
  mem[$r4, 0x04] <- $fp
  mem[$r4, 0x08] <- $r3
  mem[$r4, 0x0c] <- $r11
  mem[$r4, 0x10] <- $r12
  mem[$r4, 0x14] <- $r13
  mem[$r4, 0x18] <- $r14
  $r4 <- $r4 - $r4 # Set return value to 0
  $pc <- $r3 # return
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
  $fp  <- mem[$r4, 0x04]
  $r3  <- mem[$r4, 0x08]
  $r11 <- mem[$r4, 0x0c]
  $r12 <- mem[$r4, 0x10]
  $r13 <- mem[$r4, 0x14]
  $r14 <- mem[$r4, 0x18]
  $r4 <- $r5
  if $r4 == 0 $pc <- .Lreturn1
  $pc <- $r3
.Lreturn1:
  $r4 <- $r4 + 1
  $pc <- $r3
.Lend2:
  .size  longjmp,.Lend2-longjmp
