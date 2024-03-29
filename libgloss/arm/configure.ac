dnl Process this file with autoconf to produce a configure script.
AC_INIT(redboot-crt0.S)

dnl Support --disable-newlib-supplied-syscalls
AC_ARG_ENABLE(newlib-supplied-syscalls,
[  --disable-newlib-supplied-syscalls disable newlib from supplying syscalls],
[case "${enableval}" in
  yes) newlib_may_supply_syscalls=yes ;;
  no)  newlib_may_supply_syscalls=no ;;
  *)   AC_MSG_ERROR(bad value ${enableval} for newlib-supplied-syscalls option) ;;
 esac], [newlib_may_supply_syscalls=yes])dnl

if test "x$newlib_may_supply_syscalls" = "xyes"; then
  BUILD_CRT0_TRUE='#'
  BUILD_CRT0_FALSE=
else
  BUILD_CRT0_TRUE=
  BUILD_CRT0_FALSE='#'
fi

AC_SUBST(BUILD_CRT0_TRUE)
AC_SUBST(BUILD_CRT0_FALSE)

AC_CONFIG_AUX_DIR(../..)

AC_CANONICAL_SYSTEM
AC_ARG_PROGRAM

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

case "${target}" in
  *-*-elf | *-*-eabi* | *-*-tirtos*)
	objtype=elf-
	;;
  *-*-coff)
	objtype=coff-
	;;
esac

AC_SUBST(objtype)

host_makefile_frag=`cd $srcdir/../config;pwd`/default.mh

dnl We have to assign the same value to other variables because autoconf
dnl doesn't provide a mechanism to substitute a replacement keyword with
dnl arbitrary data or pathnames.
dnl
host_makefile_frag_path=$host_makefile_frag
AC_SUBST(host_makefile_frag_path)
AC_SUBST_FILE(host_makefile_frag)

# Configure cpu init plug-ins
if test -d "${srcdir}/cpu-init"; then
  subdirs="${subdirs} cpu-init"
  AC_CONFIG_FILES(cpu-init/Makefile,
  . ${srcdir}/../../config-ml.in,
  srcdir=${srcdir}
  target=${target}
  with_multisubdir=${with_multisubdir}
  ac_configure_args="${ac_configure_args} --enable-multilib"
  CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
  )
  AC_SUBST(subdirs)
fi

AC_CONFIG_FILES(Makefile,
. ${srcdir}/../../config-ml.in,
srcdir=${srcdir}
target=${target}
with_multisubdir=${with_multisubdir}
ac_configure_args="${ac_configure_args} --enable-multilib"
CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
)
AC_OUTPUT

