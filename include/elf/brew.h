/* brew core ELF support for BFD.
   Copyright 2021 Free Software Foundation, Inc.
   Contributed by Andras Tantos

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifndef _ELF_BREW_H
#define _ELF_BREW_H

#include "elf/reloc-macros.h"

/* NOTE: if these types are changed, the corresponding case in readelf.c  */
/*       (around line 14170) needs to change as well.                     */
/*       Right now, the only relocation we have is a 32-bit absolute one, */
/*       which is type 1.                                                 */
/*       Later we might have a 32-bit PC-relative relocation as well.     */
/*       Let's make sure that that one gets type 2 or something.          */
/*       If NONE moves around, the case around line 14657 in readelf.c    */
/*       needs to change too.                                             */

/* Relocation types.  */
START_RELOC_NUMBERS (elf_brew_reloc_type)
  RELOC_NUMBER(R_BREW_NONE,      0)
  RELOC_NUMBER(R_BREW_32,        1)
  RELOC_NUMBER(R_BREW_16,        2)
  RELOC_NUMBER(R_BREW_16_SPCREL, 3)
END_RELOC_NUMBERS (R_BREW_max)

#endif /* _ELF_BREW_H */
