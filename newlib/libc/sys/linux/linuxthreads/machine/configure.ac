dnl This is the newlib/libc/sys configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([i386])

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../../../../../..)

NEWLIB_CONFIGURE(../../../../..)

dnl We have to enable libtool after NEWLIB_CONFIGURE because if we try and
dnl add it into NEWLIB_CONFIGURE, executable tests are made before the first
dnl line of the macro which fail because appropriate LDFLAGS are not set.
_LT_DECL_SED
_LT_PROG_ECHO_BACKSLASH
if test "${use_libtool}" = "yes"; then
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
fi

if test -n "${machine_dir}"; then
  case ${machine_dir} in
	i386) AC_CONFIG_SUBDIRS(i386) ;;
  esac;
fi

AM_CONDITIONAL(HAVE_MACHINE_DIR, test x${machine_dir} != x)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
