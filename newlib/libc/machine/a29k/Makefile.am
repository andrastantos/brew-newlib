## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(AM_CPPFLAGS)

noinst_LIBRARIES = lib.a

lib_a_SOURCES =
lib_a_CCASFLAGS=$(AM_CCASFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../.. -I ../../../../config
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
