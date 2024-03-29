dnl This is the newlib/libm configure.in file.
dnl Process this file with autoconf to produce a configure script.

AC_INIT([newlib],[NEWLIB_VERSION])
AC_CONFIG_SRCDIR([libm.texi])

AC_ARG_ENABLE(newlib_hw_fp,
[  --enable-newlib-hw-fp    Turn on hardware floating point math],
[case "${enableval}" in
   yes) newlib_hw_fp=true ;;
   no)  newlib_hw_fp=false ;;
   *) AC_MSG_ERROR(bad value ${enableval} for --enable-newlib-hw-fp) ;;
 esac],[newlib_hw_fp=false])
AM_CONDITIONAL(NEWLIB_HW_FP, test x$newlib_hw_fp = xtrue)

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

dnl Can't be done in NEWLIB_CONFIGURE because that confuses automake. 
AC_CONFIG_AUX_DIR(../..)

NEWLIB_CONFIGURE(..)

dnl We have to enable libtool after NEWLIB_CONFIGURE because if we try and
dnl add it into NEWLIB_CONFIGURE, executable tests are made before the first
dnl line of the macro which fail because appropriate LDFLAGS are not set.
_LT_DECL_SED
_LT_PROG_ECHO_BACKSLASH
if test "${use_libtool}" = "yes"; then
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
fi

AC_CONFIG_SUBDIRS(machine)

LIBM_MACHINE_LIB=
if test -n "${libm_machine_dir}"; then
  if test "${use_libtool}" = "yes"; then
    LIBM_MACHINE_LIB=machine/${libm_machine_dir}/lib${libm_machine_dir}.${aext}
  else
    LIBM_MACHINE_LIB=machine/lib.${aext}
  fi
fi

AC_SUBST(LIBM_MACHINE_LIB)

AC_CONFIG_FILES([Makefile math/Makefile mathfp/Makefile common/Makefile complex/Makefile fenv/Makefile])
AC_OUTPUT
