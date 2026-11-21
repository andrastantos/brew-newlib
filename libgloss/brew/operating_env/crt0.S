/* crt0.S -- startup file for brew, operating environment
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

/* Bare-metal startup: the CPU comes out of reset in SCHEDULER mode at
   address 0 (the simulator's --environment operating, the Anachron FPGA
   system) and nothing provides syscalls; libbrew.a of this environment
   drives the devices directly.

   __start lives in its own section, .reset, which the compiler driver
   places at address 0 (--section-start=.reset=0) when no linker script is
   given; everything else goes above the I/O devices (-Ttext-segment).  A
   custom linker script must place .reset at the reset vector itself.

   The image is expected to be loaded as linked (by the simulator, a
   debugger or a boot loader), so .data is not copied from ROM.  */

#include <newlib.h> // for configuration-time defines
#include "macros.S"

#ifdef _HAVE_INITFINI_ARRAY /* renamed from HAVE_INITFINI_ARRAY in newlib 437c5c508 */
#define _init	__libc_init_array
#define _fini	__libc_fini_array
#else
#error "BREW doesn't support a configuration where .init is used. At least not at the moment."
#endif

  .globl  __start
  .weak  _start
  .section .reset,"ax",@progbits
  .type  __start,@function
__start:
_start:
  $sp <- _stack     /* the reset value of $sp is undefined */
  $fp <- $fp ^ $fp  /* zero fp to allow unwinders to stop */

  /* zero the bss area */
  $r4 <- __bss_start__
  $r5 <- $r5 ^ $r5
  $r6 <- __bss_end__
  $r6 <- $r6 - $r4
  $sp <- short $sp + (-12) /* Allocate space on stack for arguments */
  CALL memset

  /* Call _fini at exit time for static destructors; registered before _init
     runs, as in the user environment's crt0.  */
  $r4 <- _fini
  $sp <- short $sp + (-4) /* Allocate space on stack for arguments */
  CALL atexit

  /* Call _init to invoke static constructors, etc.  */
  CALL _init

  /* No command line: argc = 0, argv = { NULL }.  */
  $r4 <- $r4 ^ $r4
  $r5 <- .Lnull_argv
  $sp <- short $sp + (-8) /* Allocate space on stack for arguments argc and argv */
  CALL main
  CALL exit

.Lend:
  .size  __start,(.Lend-__start)

  .section .rodata
  .p2align 2
.Lnull_argv:
  .int 0

/* This object does not need an executable stack.  */
  .section .note.GNU-stack,"",@progbits
