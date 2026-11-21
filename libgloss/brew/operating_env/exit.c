/* exit.c -- end the program
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
#include "devices.h"

/* Ends the simulation (simulator and RTL test bench) with STATUS. On
   hardware the write does nothing, so stop here.  */
void __attribute__ ((noreturn))
_exit (int status)
{
  *(volatile uint32_t *) &__brew_simctl_base[SIMCTL_EXIT] = (uint32_t) status;
  for (;;)
    ;
}
