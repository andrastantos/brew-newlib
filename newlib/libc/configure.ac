dnl This is the newlib/libc configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([sys.tex])

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../..)

dnl Support --enable-newlib-io-pos-args used by libc/stdio
AC_ARG_ENABLE(newlib-io-pos-args,
[  --enable-newlib-io-pos-args enable printf-family positional arg support],
[case "${enableval}" in
  yes) newlib_io_pos_args=yes ;;
  no)  newlib_io_pos_args=no ;;
  *)   AC_MSG_ERROR(bad value ${enableval} for newlib-io-pos-args option) ;;
 esac], [newlib_io_pos_args=no])dnl

dnl Support --enable-newlib-nano-malloc used by libc/stdlib
AC_ARG_ENABLE(newlib_nano_malloc,
[  --enable-newlib-nano-malloc    Use small-footprint nano-malloc implementation],
[case "${enableval}" in
   yes) newlib_nano_malloc=yes ;;
   no)  newlib_nano_malloc=no ;;
   *) AC_MSG_ERROR(bad value ${enableval} for newlib-nano-malloc) ;;
 esac],[newlib_nano_malloc=])

dnl Support --enable-newlib-nano-formatted-io used by libc/stdio
AC_ARG_ENABLE(newlib_nano_formatted_io,
[  --enable-newlib-nano-formatted-io    Use small-footprint nano-formatted-IO implementation],
[case "${enableval}" in
   yes) newlib_nano_formatted_io=yes ;;
   no)  newlib_nano_formatted_io=no ;;
   *) AC_MSG_ERROR(bad value ${enableval} for newlib-nano-formatted-io) ;;
 esac],[newlib_nano_formatted_io=no])
AM_CONDITIONAL(NEWLIB_NANO_FORMATTED_IO, test x$newlib_nano_formatted_io = xyes)

dnl Support --enable-retargetable-locking used by libc/sys
AC_ARG_ENABLE(newlib-retargetable-locking,
[  --enable-newlib-retargetable-locking    Allow locking routines to be retargeted at link time],
[case "${enableval}" in
   yes) newlib_retargetable_locking=yes ;;
   no)  newlib_retargetable_lock=no ;;
   *) AC_MSG_ERROR(bad value ${enableval} for newlib-retargetable-locking) ;;
 esac],[newlib_retargetable_locking=no])
AM_CONDITIONAL(NEWLIB_RETARGETABLE_LOCKING, test x$newlib_retargetable_locking = xyes)

NEWLIB_CONFIGURE(..)

AM_CONDITIONAL(NEWLIB_NANO_MALLOC, test x$newlib_nano_malloc = xyes)

dnl We have to enable libtool after NEWLIB_CONFIGURE because if we try and
dnl add it into NEWLIB_CONFIGURE, executable tests are made before the first
dnl line of the macro which fail because appropriate LDFLAGS are not set.
_LT_DECL_SED
_LT_PROG_ECHO_BACKSLASH
if test "${use_libtool}" = "yes"; then
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
fi

AC_CONFIG_SUBDIRS(machine sys)

CRT0=
if test "x${have_crt0}" = "xyes"; then
  CRT0=crt0.o
fi
AC_SUBST(CRT0)

dnl For each directory which we may or may not want, we define a name
dnl for the library and an automake conditional for whether we should
dnl build the library.

LIBC_SIGNAL_LIB=
LIBC_SIGNAL_DEF=
if test -n "${signal_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_SIGNAL_LIB=${signal_dir}/lib${signal_dir}.${aext}
  else
    LIBC_SIGNAL_LIB=${signal_dir}/lib.${aext}
  fi
  LIBC_SIGNAL_DEF=${signal_dir}/stmp-def
fi
AC_SUBST(LIBC_SIGNAL_LIB)
AC_SUBST(LIBC_SIGNAL_DEF)
AM_CONDITIONAL(HAVE_SIGNAL_DIR, test x${signal_dir} != x)

LIBC_STDIO_LIB=
LIBC_STDIO_DEF=
if test -n "${stdio_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_STDIO_LIB=${stdio_dir}/lib${stdio_dir}.${aext}
  else
    LIBC_STDIO_LIB=${stdio_dir}/lib.${aext}
  fi
  LIBC_STDIO_DEF=${stdio_dir}/stmp-def
fi
AC_SUBST(LIBC_STDIO_LIB)
AC_SUBST(LIBC_STDIO_DEF)
AM_CONDITIONAL(HAVE_STDIO_DIR, test x${stdio_dir} != x)

LIBC_STDIO64_LIB=
LIBC_STDIO64_DEF=
if test -n "${stdio64_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_STDIO64_LIB=${stdio64_dir}/lib${stdio64_dir}.${aext}
  else
    LIBC_STDIO64_LIB=${stdio64_dir}/lib.${aext}
  fi
  LIBC_STDIO64_DEF=${stdio64_dir}/stmp-def
fi
AC_SUBST(LIBC_STDIO64_LIB)
AC_SUBST(LIBC_STDIO64_DEF)
AM_CONDITIONAL(HAVE_STDIO64_DIR, test x${stdio64_dir} != x)

LIBC_POSIX_LIB=
LIBC_POSIX_DEF=
if test -n "${posix_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_POSIX_LIB=${posix_dir}/lib${posix_dir}.${aext}
  else
    LIBC_POSIX_LIB=${posix_dir}/lib.${aext}
  fi
  LIBC_POSIX_DEF=${posix_dir}/stmp-def
fi
AC_SUBST(LIBC_POSIX_LIB)
AC_SUBST(LIBC_POSIX_DEF)
AM_CONDITIONAL(HAVE_POSIX_DIR, test x${posix_dir} != x)

LIBC_XDR_LIB=
LIBC_XDR_DEF=
if test -n "${xdr_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_XDR_LIB=${xdr_dir}/lib${xdr_dir}.${aext}
  else
    LIBC_XDR_LIB=${xdr_dir}/lib.${aext}
  fi
  LIBC_XDR_DEF=${xdr_dir}/stmp-def
fi
AC_SUBST(LIBC_XDR_LIB)
AC_SUBST(LIBC_XDR_DEF)
AM_CONDITIONAL(HAVE_XDR_DIR, test x${xdr_dir} != x)

LIBC_SYSCALL_LIB=
if test -n "${syscall_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_SYSCALL_LIB=${syscall_dir}/lib${syscall_dir}.${aext}
  else
    LIBC_SYSCALL_LIB=${syscall_dir}/lib.${aext}
  fi
fi
AC_SUBST(LIBC_SYSCALL_LIB)
AM_CONDITIONAL(HAVE_SYSCALL_DIR, test x${syscall_dir} != x)

LIBC_UNIX_LIB=
if test -n "${unix_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_UNIX_LIB=${unix_dir}/lib${unix_dir}.${aext}
  else
    LIBC_UNIX_LIB=${unix_dir}/lib.${aext}
  fi
fi
AC_SUBST(LIBC_UNIX_LIB)
AM_CONDITIONAL(HAVE_UNIX_DIR, test x${unix_dir} != x)

LIBC_EXTRA_LIB=
LIBC_EXTRA_DEF=
extra_dir=

AC_SUBST(LIBC_EXTRA_LIB)
AC_SUBST(LIBC_EXTRA_DEF)
AC_SUBST(extra_dir)

dnl We always recur into sys and machine, and let them decide what to
dnl do.  However, we do need to know whether they will produce a library.

LIBC_SYS_LIB=
if test -n "${sys_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_SYS_LIB=sys/${sys_dir}/lib${sys_dir}.${aext}
  else
    LIBC_SYS_LIB=sys/lib.${aext}
  fi
fi
AC_SUBST(LIBC_SYS_LIB)
AC_SUBST(sys_dir)

dnl Autoconf 2.59 doesn't support the AC_TYPE_LONG_DOUBLE macro. Instead of:
dnl   AC_TYPE_LONG_DOUBLE
dnl   AM_CONDITIONAL(HAVE_LONG_DOUBLE, test x"$ac_cv_type_long_double" = x"yes")
dnl we specify our own long double test.
AC_CACHE_CHECK([Checking long double support], [acnewlib_cv_type_long_double],[dnl
cat > conftest.c <<EOF
int main() {
long double x = 0.0L;
return 0;
}
EOF
if AC_TRY_COMMAND([${CC} $CFLAGS $CPPFLAGS -c conftest.c 1>&AS_MESSAGE_LOG_FD])
then
  acnewlib_cv_type_long_double=yes
else
  acnewlib_cv_type_long_double=no
fi
rm -f conftest*])
AM_CONDITIONAL(HAVE_LONG_DOUBLE, test x"$acnewlib_cv_type_long_double" = x"yes")

dnl iconv library will be compiled if --enable-newlib-iconv option is enabled
AM_CONDITIONAL(ENABLE_NEWLIB_ICONV, test x${newlib_iconv} != x)

if test -n "${machine_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBC_MACHINE_LIB=machine/${machine_dir}/lib${machine_dir}.${aext}
  else
    LIBC_MACHINE_LIB=machine/lib.${aext}
  fi
fi
AC_SUBST(LIBC_MACHINE_LIB)
AC_SUBST(machine_dir)
AC_SUBST(shared_machine_dir)

AC_CONFIG_FILES([Makefile argz/Makefile ctype/Makefile errno/Makefile locale/Makefile misc/Makefile reent/Makefile search/Makefile stdio/Makefile stdio64/Makefile stdlib/Makefile string/Makefile time/Makefile posix/Makefile signal/Makefile syscalls/Makefile unix/Makefile iconv/Makefile iconv/ces/Makefile iconv/ccs/Makefile iconv/ccs/binary/Makefile iconv/lib/Makefile ssp/Makefile xdr/Makefile])
AC_OUTPUT
