## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(AM_CPPFLAGS)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = calloc.c callocr.c malloc.c mallocr.c realloc.c reallocr.c \
		free.c write.c assert.c puts.c putchar.c printf.c abort.c \
		exit.c misc.c clock.c
lib_a_CFLAGS = $(AM_CFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../.. -I ../../../../config
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
