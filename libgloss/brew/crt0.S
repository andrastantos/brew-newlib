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

#ifdef HAVE_INITFINI_ARRAY
#define _init	__libc_init_array
#define _fini	__libc_fini_array
#else
#error "BREW doesn't support a configuration where .init is used. At least not at the moment."
#endif

  .globl  __start
  .weak  _start
#ifdef HAVE_INITFINI_ARRAY
  .section ".init"
#else
  .text
#endif
  .type  __start,@function
__start:
_start:
  $sp <- _stack    /* set the top of stack */
  $fp <- 0         /* zero fp to allow unwinders to stop */

  /* zero the bss area */
  $r4 <- __bss_start__
  $r5 <- 0
  $r6 <- __bss_end__
  $r6 <- $r6 - $r2
  CALL memset

  /* Call _init to invoke static constructors, etc.  */
  CALL _init
  
  /* Call _fini at exit time for static destructors.  */
  $r4 <- _fini
  CALL atexit
  
  /* Set argc and argv.  These are populated by the simulator.  */
  $r4 <- 0x4
  $r5 <- 0x8
  
  CALL main
  CALL exit

.Lend:
  .size  __start,(.Lend-__start)
