dnl This is the newlib/libm/machine configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([i386])

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../../..)

NEWLIB_CONFIGURE(../..)

dnl We have to add the following lines because automake detects the
dnl references to libtool libraries from aclocal and tries to verify that
dnl AM_PROG_LIBTOOL is being used.  This must be added after
dnl the call to NEWLIB_CONFIGURE.
_LT_DECL_SED
_LT_PROG_ECHO_BACKSLASH
if test "${use_libtool}" = "yes"; then
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
fi

machlib=

if test -n "${libm_machine_dir}"; then
  case ${libm_machine_dir} in
	aarch64) AC_CONFIG_SUBDIRS(aarch64) ;;
	arm) AC_CONFIG_SUBDIRS(arm) ;;
	i386) AC_CONFIG_SUBDIRS(i386) ;;
	nds32) AC_CONFIG_SUBDIRS(nds32) ;;
	pru) AC_CONFIG_SUBDIRS(pru) ;;
	spu) AC_CONFIG_SUBDIRS(spu) ;;
	riscv) AC_CONFIG_SUBDIRS(riscv) ;;
	x86_64) AC_CONFIG_SUBDIRS(x86_64) ;;
	powerpc) AC_CONFIG_SUBDIRS(powerpc) ;;
	sparc) AC_CONFIG_SUBDIRS(sparc) ;;
	mips) AC_CONFIG_SUBDIRS(mips) ;;
  esac;
  if test "${use_libtool}" = "yes"; then
    machlib=${libm_machine_dir}/lib${libm_machine_dir}.${aext}
  else
    machlib=${libm_machine_dir}/lib.${aext}
  fi
fi

AC_SUBST(libm_machine_dir)
AC_SUBST(machlib)

AM_CONDITIONAL(HAVE_LIBM_MACHINE_DIR, test x${libm_machine_dir} != x)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT



