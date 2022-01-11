/*
 * sim-open.S -- open interface for moxie simulator
 * 
 * Copyright (c) 2022 Andras Tantos
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

#include "syscall.h"
#include "macros.S"

/*
 * Input:
 * $r4        -- File name to open.
 * $r5        -- open mode.
 * -0x12($fp) -- optionally, the permission bits to set the file to.
 *
 * Output:
 * $r4	  -- file descriptor or -1.
 * errno  -- Set if an error
 */

	.globl	_open
	.type	_open,@function
	.weak	open
	.text
_open:
open:
	SYSCALLM SYS_open
	RET
.Lend:
	.size	_open,.Lend-_open
