dnl This is the newlib/libc/machine/sh configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([asm.h])

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../../../..)

AC_NO_EXECUTABLES

NEWLIB_CONFIGURE(../../..)

AC_EGREP_CPP([sh5], [
#if __SH5__
  sh5
#endif
], [have_sh64=yes], [have_sh64=no])
AM_CONDITIONAL(SH64, [test $have_sh64 = yes])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
