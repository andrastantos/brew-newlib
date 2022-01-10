/* Definitions for decoding the brew opcode table.
   Copyright (C) 2009-2021 Free Software Foundation, Inc.
   Contributed by Andras Tantos.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* TODO: right now this is not changed from the moxie baseline at all. It should be!!!! */

/* Form 1 instructions come in different flavors:

    Some have no arguments                          (BREW_F1_NARG)
    Some only use the A operand                     (BREW_F1_A)
    Some use A and B registers                      (BREW_F1_AB)
    Some use A and consume a 4 byte immediate value (BREW_F1_A4)
    Some use just a 4 byte immediate value          (BREW_F1_4)
    Some use just a 4 byte memory address           (BREW_F1_M)
    Some use B and an indirect A                    (BREW_F1_AiB)
    Some use A and an indirect B                    (BREW_F1_ABi)
    Some consume a 4 byte immediate value and use X (BREW_F1_4A)
    Some use B and an indirect A plus 2 byte offset (BREW_F1_AiB2)
    Some use A and an indirect B plus 2 byte offset (BREW_F1_ABi2)

  Form 2 instructions also come in different flavors:

    Some have no arguments                          (BREW_F2_NARG)
    Some use the A register and an 8-bit value      (BREW_F2_A8V)

  Form 3 instructions also come in different flavors:

    Some have no arguments                          (BREW_F3_NARG)
    Some have a 10-bit PC relative operand          (BREW_F3_PCREL).  */

#define BREW_F1_NARG 0x100
#define BREW_F1_A    0x101
#define BREW_F1_AB   0x102
/* #define BREW_F1_ABC  0x103 */
#define BREW_F1_A4   0x104
#define BREW_F1_4    0x105
#define BREW_F1_AiB  0x106
#define BREW_F1_ABi  0x107
#define BREW_F1_4A   0x108
#define BREW_F1_AiB2 0x109
#define BREW_F1_ABi2 0x10a
#define BREW_F1_M    0x10b

#define BREW_F2_NARG 0x200
#define BREW_F2_A8V  0x201

#define BREW_F3_NARG  0x300
#define BREW_F3_PCREL 0x301

#define BREW_BAD     0x400

#define BREW_NARG               0x500 /* Instructions with no arguments */
#define BREW_ABD                0x501 /* Binary Instructions */
#define BREW_ABD_NO_D_PC        0x502 /* Binary Instructions that can't target PC */
#define BREW_ABD_NO_A_PC        0x503 /* Binary Instructions that can't use PC as the first source */
#define BREW_ABD_NO_B_PC        0x504 /* Binary Instructions that can't use PC as the second source */
#define BREW_ABD_NO_SAME_AB     0x505 /* Binary Instructions where A and B must be different */
#define BREW_AD                 0x506 /* Unary Instructions with only A as the source */
#define BREW_BD                 0x507 /* Unary Instructions with only B as the source */
#define BREW_AiD                0x508 /* Binary Insturctions with immediate and A */
#define BREW_iBD                0x509 /* Binary Insturctions with immediate and B */
#define BREW_iD                 0x50a /* Unary Instructions with immediate source */

#define BREW_REG_PC 0x0
#define BREW_REG_SP 0x1 /* R1 is of course a general purpose register, but the ABI defines it as SP, so let's have an alias for that */
#define BREW_REG_FP 0x2 /* R2 is of course a general purpose register, but the ABI defines it as FP, so let's have an alias for that */
#define BREW_REG_R(x) (x)

#define BREW_NO_TPC 0
#define BREW_ALLOW_TPC 1

#define BREW_REG_TPC 0xf /* Special register index for TPC. Not used in encoding as is all the time, but returned by the register name parser. */

#define BREW_REG_FLAG_MASK 0xf000
#define BREW_REG_FLAG_FLOAT 0x2000 /* Used to mark register operands for F0...FE. These are aliases for R0...RE for floating point operations */
#define BREW_REG_FLAG_SIGNED 0x4000 /* Used to mark register operands for S0...SE. These are aliases for R0...RE for signed operations */
