## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(AM_CPPFLAGS)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = _exit.c access.c chmod.c chown.c close.c creat.c crt1.c \
	execv.c execve.c fork.c fstat.c getpid.c isatty.c \
	kill.c lseek.c open.c pipe.c read.c \
	sbrk.c stat.c time.c trap.S unlink.c utime.c wait.c write.c \
	times.c gettime.c
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

all-local: crt0.o

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../.. -I ../../../../config
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
