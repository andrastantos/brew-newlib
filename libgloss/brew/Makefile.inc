## Copyright (c) 2008, 2010 Anthony Green, 2022 Andras Tantos
##
## The authors hereby grant permission to use, copy, modify, distribute,
## and license this software and its documentation for any purpose, provided
## that existing copyright notices are retained in all copies and that this
## notice is included verbatim in any distributions. No written agreement,
## license, or royalty fee is required for any of the authorized uses.
## Modifications to this software may be copyrighted by their authors
## and need not follow the licensing terms described here, provided that
## the new terms are clearly indicated on the first page of each file where
## they apply.

## Makefile fragment for libgloss/brew, the board support code for the
## brew target.

## Two board support packages, one per environment (the simulator's
## --environment user|operating; gcc -menvironment=user|operating). Each is
## built from, and installed into, a subdirectory named after its environment,
## with the same file names: <env>/crt0.o and <env>/libbrew.a. Sources shared
## by both are in this directory.
##
## user_env:      TASK mode under an OS or the simulator, which provides the
##                syscalls (syscall-template.S) and sets up $sp.
## operating_env: bare metal from reset (SCHEDULER mode); drives the console
##                and simulator-control devices directly.

if !HAVE_MULTISUBDIR
multilibtool_DATA += \
	%D%/brew-elf-common.ld \
	%D%/sim.ld
endif

## Headers: macros.S here, brew-calls.h / devices.h in each environment.
AM_CPPFLAGS_%C%_user_env = -I$(srcdir)/%D% -I$(srcdir)/%D%/user_env
AM_CPPFLAGS_%C%_operating_env = -I$(srcdir)/%D% -I$(srcdir)/%D%/operating_env

libobjs_a_SOURCES += \
	%D%/user_env/crt0.S \
	%D%/operating_env/crt0.S

## Built for both environments from the sources in this directory.
## mcount.c: call-graph profiling for -p/-pg (_mcount, gmon.out).
%C%_SHARED_SOURCES = \
	%D%/sbrk.c \
	%D%/mcount.c

## ---------------------------------------------------------------- user_env

%C%_user_envdir = $(multilibtooldir)/user_env
%C%_user_env_DATA = %D%/user_env/crt0.o
%C%_user_env_LIBRARIES = %D%/user_env/libbrew.a

## Every syscall stub is syscall-template.S with FN_NAME=_<name> and
## SYSCALL_NO=SYS_<name>, or the BREW_<name> number named in
## %C%_SYSCALL_NO_<name>.
%C%_USER_SYSCALLS = exit open close read write lseek unlink getpid kill fstat \
	stat chdir chmod utime time gettimeofday times link isatty getentropy
%C%_SYSCALL_NO_isatty = BREW_isatty
%C%_SYSCALL_NO_getentropy = BREW_getentropy

%C%_user_env_libbrew_a_SOURCES = \
	%D%/user_env/posix.c \
	$(%C%_SHARED_SOURCES)
%C%_user_env_libbrew_a_LIBADD = \
	$(patsubst %,%D%/user_env/syscall-%.$(OBJEXT),$(%C%_USER_SYSCALLS))

%D%/user_env/syscall-%.$(OBJEXT): %D%/user_env/syscall-template.S \
		%D%/user_env/brew-calls.h %D%/macros.S | %D%/user_env/$(am__dirstamp)
	$(AM_V_CPPAS)$(CPPASCOMPILE) -D FN_NAME=_$* \
	  -D SYSCALL_NO=$(or $(%C%_SYSCALL_NO_$*),SYS_$*) -c -o $@ $<

## ----------------------------------------------------------- operating_env

%C%_operating_envdir = $(multilibtooldir)/operating_env
%C%_operating_env_DATA = %D%/operating_env/crt0.o
%C%_operating_env_LIBRARIES = %D%/operating_env/libbrew.a

## Device drivers, plus ENOSYS stubs (nosys.c with FN_NAME=_<name>) for what
## has no device behind it.
%C%_OPERATING_NOSYS = open close lseek unlink stat chdir chmod utime time \
	gettimeofday times link getentropy
## newlib has no public wrappers for these _<name> calls (user_env has
## them in posix.c), so their stubs also define <name> as a weak alias.
%C%_PUBLIC_ALIASES = chdir chmod utime
## Stubs a program or board may replace (see nosys.c).
%C%_WEAK_STUBS = getentropy

%C%_operating_env_libbrew_a_SOURCES = \
	%D%/operating_env/devices.S \
	%D%/operating_env/read.c \
	%D%/operating_env/write.c \
	%D%/operating_env/exit.c \
	%D%/operating_env/kill.c \
	%D%/operating_env/getpid.c \
	%D%/operating_env/isatty.c \
	%D%/operating_env/fstat.c \
	$(%C%_SHARED_SOURCES)
%C%_operating_env_libbrew_a_LIBADD = \
	$(patsubst %,%D%/operating_env/nosys-%.$(OBJEXT),$(%C%_OPERATING_NOSYS))

%D%/operating_env/nosys-%.$(OBJEXT): %D%/operating_env/nosys.c \
		| %D%/operating_env/$(am__dirstamp)
	$(AM_V_CC)$(COMPILE) -D FN_NAME=_$* \
	  $(if $(filter $*,$(%C%_PUBLIC_ALIASES)),-D ALIAS_NAME=$*) \
	  $(if $(filter $*,$(%C%_WEAK_STUBS)),-D WEAK) -c -o $@ $<
