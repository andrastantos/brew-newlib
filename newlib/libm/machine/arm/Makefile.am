## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = -I $(newlib_basedir)/../newlib/libm/common $(NEWLIB_CFLAGS) \
	$(CROSS_CFLAGS) $(TARGET_CFLAGS)

LIB_SOURCES = \
	e_sqrt.c \
	ef_sqrt.c \
	s_ceil.c \
	s_floor.c \
	s_fma_arm.c \
	s_nearbyint.c \
	s_rint.c \
	s_round.c \
	s_trunc.c \
	sf_ceil.c \
	sf_floor.c \
	sf_fma_arm.c \
	sf_nearbyint.c \
	sf_rint.c \
	sf_round.c \
	sf_trunc.c \
	feclearexcept.c \
	fe_dfl_env.c\
	fegetenv.c \
	fegetexceptflag.c \
	fegetround.c \
	feholdexcept.c \
	fegetexcept.c \
	feraiseexcept.c \
	fesetenv.c \
	fesetexceptflag.c \
	fesetround.c \
	fetestexcept.c \
	feupdateenv.c \
	feenableexcept.c \
	fedisableexcept.c


noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(LIB_SOURCES)
lib_a_CFLAGS = $(AM_CFLAGS)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
noinst_DATA =

include $(srcdir)/../../../Makefile.shared

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../.. -I ../../../../config
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
