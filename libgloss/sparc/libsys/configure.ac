# Configure.in for libgloss/sparc/libsys
# Copyright (c) 1996 Cygnus Support
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# and/or other materials related to such
# distribution and use acknowledge that the software was developed
# at Cygnus Support, Inc.  Cygnus Support, Inc. may not be used to
# endorse or promote products derived from this software without
# specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

dnl Process this file with autoconf to produce a configure script.
AC_INIT(libsys-crt0.S)

AC_CONFIG_AUX_DIR(../../..)

AC_PROG_INSTALL

LIB_AC_PROG_CC
AS=${AS-as}
AC_SUBST(AS)
AR=${AR-ar}
AC_SUBST(AR)
LD=${LD-ld}
AC_SUBST(LD)
AC_PROG_RANLIB
LIB_AM_PROG_AS

host_makefile_frag=${srcdir}/../../config/default.mh

dnl We have to assign the same value to other variables because autoconf
dnl doesn't provide a mechanism to substitute a replacement keyword with
dnl arbitrary data or pathnames.
dnl
host_makefile_frag_path=$host_makefile_frag
AC_SUBST(host_makefile_frag_path)
AC_SUBST_FILE(host_makefile_frag)

AC_OUTPUT(Makefile)
