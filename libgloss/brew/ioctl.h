/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   Modified by Andras Tantos.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#pragma once

#define TCGETS     0x5401
#define TCSETS     0x5402
#define TCSETSW    0x5403
#define TCSETSF    0x5404
#define FIONREAD   0x541B
#define TIOCINQ    FIONREAD

#ifdef __cplusplus
extern "C" {
#endif

extern int ioctl(int __fd, unsigned long int __request, ...);

#ifdef __cplusplus
}
#endif
