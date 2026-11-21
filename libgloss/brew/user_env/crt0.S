/* crt0.S -- startup file for brew
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

#include <newlib.h> // for configuration-time defines
#include "macros.S"
#include "syscall.h"

#ifdef _HAVE_INITFINI_ARRAY /* renamed from HAVE_INITFINI_ARRAY in newlib 437c5c508 */
#define _init	__libc_init_array
#define _fini	__libc_fini_array
#else
#error "BREW doesn't support a configuration where .init is used. At least not at the moment."
#endif

  .globl  __start
  .weak  _start
  .weak  _stack
#ifdef _HAVE_INITFINI_ARRAY /* renamed from HAVE_INITFINI_ARRAY in newlib 437c5c508 */
  .section ".init"
#else
  .text
#endif
  .type  __start,@function
__start:
_start:
  /* The program starts in TASK mode with whatever $sp its environment set
     up: an OS (such as the Anachron ROM in anachron/sw_new, which sizes it
     from the detected DRAM) or the simulator.  A linker script can still
     dictate the stack by defining _stack, as ld's default script does
     (0x80000000, the top of the simulator's memory); without it, keep the
     incoming $sp.  */
  $r4 <- _stack
  if $r4 == 0 $pc <- 0f
  $sp <- $r4
0:
  $fp <- $fp ^ $fp  /* zero fp to allow unwinders to stop */

  /* Build argc/argv from the simulator's SYS_argc/SYS_argnlen/SYS_argn at
     the top of the stack, above main's frame:

  initial $sp -> | argv[argc-1] string | ... | argv[0] string |
                 | NULL | argv[argc-1] | ... | argv[0] | <- $r11 = argv
                 | padding to 16 bytes                  | <- $sp

     Each string takes its length plus the NUL, rounded up to 4 bytes.
     The syscalls preserve every register except $r4 (the result) and
     $lr (errno), so $r8...$r11 survive them.  $r8 = argc, $r9 = index,
     $r10 = string pointer, $r11 = argv.  */
  $lr <- errno
  SYSCALLM SYS_argc
  $r8 <- $r4
  if signed $r8 >= 0 $pc <- 1f
  $r8 <- $r8 ^ $r8  /* no arguments if the call fails */
1:
  /* Copy the strings, last one first, so argv[0] ends up lowest.  */
  $r9 <- $r8
2:
  if $r9 == 0 $pc <- 3f
  $r9 <- tiny $r9 + -1
  $r4 <- $r9
  $lr <- errno
  SYSCALLM SYS_argnlen
  $r4 <- tiny $r4 + 4
  $r4 <- short $r4 & -4
  $sp <- $sp - $r4
  $r4 <- $r9
  $r5 <- $sp
  $lr <- errno
  SYSCALLM SYS_argn
  $pc <- 2b
3:
  /* Below the strings: the argv array, argc + 1 pointers.  */
  $r10 <- $sp
  $r4 <- tiny $r8 + 1
  $r4 <- short $r4 << 2
  $sp <- $sp - $r4
  $r11 <- $sp
4:
  if $r9 == $r8 $pc <- 5f
  $r4 <- $r9
  $r4 <- short $r4 << 2
  $r4 <- $r4 + $r11
  mem[$r4] <- $r10
  $r4 <- $r9
  $lr <- errno
  SYSCALLM SYS_argnlen
  $r4 <- tiny $r4 + 4
  $r4 <- short $r4 & -4
  $r10 <- $r10 + $r4
  $r9 <- tiny $r9 + 1
  $pc <- 4b
5:
  $r4 <- $r8
  $r4 <- short $r4 << 2
  $r4 <- $r4 + $r11
  $r5 <- $r5 ^ $r5
  mem[$r4] <- $r5
  /* The ABI only needs 4-byte alignment, but give main a 16-byte aligned
     frame (as it had when the stack started at _stack, before argv): code
     with over-aligned locals or arguments (gcc.dg/pr84877.c) relies on it,
     as Brew has no stack realignment.  */
  $sp <- short $sp & -16

  /* zero the bss area */
  $r4 <- __bss_start__
  $r5 <- $r5 ^ $r5
  $r6 <- __bss_end__
  $r6 <- $r6 - $r4
  $sp <- short $sp + (-12) /* Allocate space on stack for arguments */
  CALL memset

  /* Call _fini at exit time for static destructors.  Register it before
     _init runs, so that it runs after everything registered during
     initialization (C++ static objects' destructors via __cxa_atexit):
     handlers run in reverse order of registration.  */
  $r4 <- _fini
  $sp <- short $sp + (-4) /* Allocate space on stack for arguments */
  CALL atexit

  /* Call _init to invoke static constructors, etc.  */
  CALL _init

  $r4 <- $r8
  $r5 <- $r11
  $sp <- short $sp + (-8) /* Allocate space on stack for arguments argc and argv */
  CALL main
  CALL exit

.Lend:
  .size  __start,(.Lend-__start)

/* This object does not need an executable stack.  */
  .section .note.GNU-stack,"",@progbits
