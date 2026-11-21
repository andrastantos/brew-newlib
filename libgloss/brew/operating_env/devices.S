/* devices.S -- default device addresses for the operating environment
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

/* Weak, so that a definition at link time (--defsym, a linker script)
   takes precedence.  See devices.h.  */
  .weak __brew_console_base
  .set  __brew_console_base, 0x00020000
  .weak __brew_simctl_base
  .set  __brew_simctl_base,  0x00020200

/* This object does not need an executable stack.  */
  .section .note.GNU-stack,"",@progbits
