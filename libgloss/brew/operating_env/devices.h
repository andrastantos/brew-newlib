/* devices.h -- I/O devices used by the operating environment's libbrew.a
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

#pragma once

#include <stdint.h>

/* Base addresses of the devices. The defaults (devices.S) follow the
   Anachron FPGA system and the simulator's defaults; override them at link
   time with -Wl,--defsym=__brew_console_base=ADDRESS (and likewise for
   __brew_simctl_base), to match the simulator's --console-base and
   --simctl-base.  */
extern volatile uint8_t __brew_console_base[];
extern volatile uint8_t __brew_simctl_base[];

/* Console (the Anachron UART, apb_uart.py; the simulator's brew_con). All
   registers are 8 bits wide.  */
#define CON_DATA      0x0
#define CON_STATUS    0x1
#define CON_STAT_RX_VALID  0x01
#define CON_STAT_TX_READY  0x02

/* Simulator control (the simulator's brew_simctl; GPIO4 on the FPGA system,
   which the RTL test bench uses the same way): a write ends the simulation
   with the written value as exit status.  */
#define SIMCTL_EXIT   0x0
