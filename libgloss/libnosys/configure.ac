# Copyright (c) 1995, 1996 Cygnus Support
#
# The authors hereby grant permission to use, copy, modify, distribute,
# and license this software and its documentation for any purpose, provided
# that existing copyright notices are retained in all copies and that this
# notice is included verbatim in any distributions. No written agreement,
# license, or royalty fee is required for any of the authorized uses.
# Modifications to this software may be copyrighted by their authors
# and need not follow the licensing terms described here, provided that
# the new terms are clearly indicated on the first page of each file where
# they apply.
#
# Process this file with autoconf to produce a configure script.
#
AC_INIT(close.c)
AC_CONFIG_HEADER(config.h)

AC_CONFIG_AUX_DIR(../..)

AC_CANONICAL_SYSTEM
AC_ARG_PROGRAM

AC_PROG_INSTALL

AC_DEFINE(HAVE_GNU_LD, 1, [Using GNU LD])
dnl Make sure syscall names match those being used by newlib
case "${target}" in
  *-*-cygwin*)
	;;
  a29k-amd-udi)
	;;
  aarch64*-*-*)
	;;
  arc-*-*)
	;;
  arm*-*-*)
	;;
  bfin-*-*)
	;;
  cris-*-* | crisv32-*-*)
	;;
  d10v*)
	;;
  h8300*-*-*)
	;;	
  h8500-*-*)
	;;	
  i[3456]86-*-sco*)
	;;
  lm32-*-*)
	;;
  m32r-*-*)
	;;
  mn10?00-*-*)
	;;
  riscv*-*-*)
	;;
  powerpcle-*-pe)
	;;
  sh*-*-*)
	;;
  sparc-sun-sunos*)
	;;
  sparc64-*-*)
	;;
  v850*-*-*)
	;;
  w65-*-*)
	;;	
  xstormy16-*-*)
	;;
  z8k-*-*)
	;;
  *)
	AC_DEFINE(MISSING_SYSCALL_NAMES, 1, [Missing syscall names])
	;;
esac

dnl Make sure we know if elf format used
case "${target}" in
  *-*-elf)
        AC_DEFINE(HAVE_ELF, 1, [Using ELF format])

        AC_CACHE_CHECK([for .previous assembler directive],
                         libc_cv_asm_previous_directive, [dnl
        libc_cv_asm_previous_directive=no
        cat > conftest.s <<EOF
.section foo_section
.previous
EOF
        if AC_TRY_COMMAND(${CC-cc} -c $CFLAGS conftest.s 1>&AC_FD_CC); then
          libc_cv_asm_previous_directive=yes
        fi
        rm -f conftest*])

	if test "x${libc_cv_asm_previous_directive}" = "xyes"; then
          AC_DEFINE(HAVE_ASM_PREVIOUS_DIRECTIVE, 1, [.previous directive allowed])
	fi

        AC_CACHE_CHECK([for .popsection assembler directive],
                         libc_cv_asm_popsection_directive, [dnl
        libc_cv_asm_popsection_directive=no
        cat > conftest.s <<EOF
.pushsection foo_section
.popsection
EOF
        if AC_TRY_COMMAND(${CC-cc} -c $CFLAGS conftest.s 1>&AC_FD_CC); then
          libc_cv_asm_popsection_directive=yes
        fi
        rm -f conftest*])

	if test "x${libc_cv_asm_popsection_directive}" = "xyes"; then
          AC_DEFINE(HAVE_ASM_POPSECTION_DIRECTIVE, 1, [.pushsection/.popsection directives allowed])
	fi

        AC_CACHE_CHECK([for section attributes],
                         libc_cv_section_attributes, [dnl
        libc_cv_section_attributes=no
        cat > conftest.c <<EOF
int secttest __attribute__ ((section (".gnu.warning.secttest"))) = 10;
int main() {}
EOF
        if AC_TRY_COMMAND(${CC-cc} -c $CFLAGS conftest.c 1>&AC_FD_CC); then
          libc_cv_section_attributes=yes
        fi
        rm -f conftest*])
	if test "x${libc_cv_section_attributes}" = "xyes"; then
          AC_DEFINE(HAVE_SECTION_ATTRIBUTES, 1, [support for section attributes])
	fi
        ;;
esac

AC_CACHE_CHECK([for symbol prefix], libc_cv_symbol_prefix, [dnl
cat > conftest.c <<\EOF
foo () { }
EOF
dnl
libc_cv_symbol_prefix=''
if AC_TRY_COMMAND([${CC-cc} -S conftest.c -o - | fgrep "\$foo" > /dev/null]);
then
  libc_cv_symbol_prefix='$'
else
  if AC_TRY_COMMAND([${CC-cc} -S conftest.c -o - | fgrep "_foo" > /dev/null]);
  then
    libc_cv_symbol_prefix=_
  fi
fi
rm -f conftest* ])
AC_DEFINE_UNQUOTED(__SYMBOL_PREFIX, "$libc_cv_symbol_prefix", [symbol prefix])

LIB_AC_PROG_CC
AS=${AS-as}
AC_SUBST(AS)
AR=${AR-ar}
AC_SUBST(AR)
LD=${LD-ld}
AC_SUBST(LD)
AC_PROG_RANLIB
LIB_AM_PROG_AS

host_makefile_frag=${srcdir}/../config/default.mh

dnl We have to assign the same value to other variables because autoconf
dnl doesn't provide a mechanism to substitute a replacement keyword with
dnl arbitrary data or pathnames.
dnl
host_makefile_frag_path=$host_makefile_frag
AC_SUBST(host_makefile_frag_path)
AC_SUBST_FILE(host_makefile_frag)

AC_CONFIG_FILES(Makefile,
ac_file=Makefile . ${srcdir}/../../config-ml.in,
srcdir=${srcdir}
target=${target}
with_multisubdir=${with_multisubdir}
ac_configure_args="${ac_configure_args} --enable-multilib"
CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
)
AC_OUTPUT


