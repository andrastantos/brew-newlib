dnl This is the newlib/libc/sys/linux/linuxthreads configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([attr.c])

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../../../../..)

NEWLIB_CONFIGURE(../../../..)

dnl We have to enable libtool after NEWLIB_CONFIGURE because if we try and
dnl add it into NEWLIB_CONFIGURE, executable tests are made before the first
dnl line of the macro which fail because appropriate LDFLAGS are not set.
_LT_DECL_SED
_LT_PROG_ECHO_BACKSLASH
AC_PROG_AWK
if test "${use_libtool}" = "yes"; then
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
fi

if test -n "${machine_dir}"; then
  MACHINE_OBJLIST=machine/${machine_dir}/objectlist.awk.in
  MACHINE_LIB=machine/${machine_dir}/lib.a
fi
AC_SUBST(MACHINE_OBJLIST)
AC_SUBST(MACHINE_LIB)

AC_CONFIG_SUBDIRS(machine)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
