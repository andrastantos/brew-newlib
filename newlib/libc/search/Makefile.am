## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

GENERAL_SOURCES = \
	bsearch.c \
	db_local.h \
	extern.h \
	hash.h \
	ndbm.c \
	page.h \
	qsort.c

## Following are EL/IX level 2 interfaces
if ELIX_LEVEL_1
ELIX_2_SOURCES =
else
ELIX_2_SOURCES = \
	hash.c \
	hash_bigkey.c \
	hash_buf.c \
	hash_func.c \
	hash_log2.c \
	hash_page.c \
	hcreate.c \
	hcreate_r.c \
	tdelete.c \
	tdestroy.c \
	tfind.c \
	tsearch.c \
	twalk.c
endif

## Following are EL/IX level 4 interfaces
if ELIX_LEVEL_1
ELIX_4_SOURCES =
else
if ELIX_LEVEL_2
ELIX_4_SOURCES =
else
if ELIX_LEVEL_3
ELIX_4_SOURCES =
else
ELIX_4_SOURCES = \
	bsd_qsort_r.c \
	qsort_r.c
endif !ELIX_LEVEL_3
endif !ELIX_LEVEL_2
endif !ELIX_LEVEL_1

libsearch_la_LDFLAGS = -Xcompiler -nostdlib

if USE_LIBTOOL
noinst_LTLIBRARIES = libsearch.la
libsearch_la_SOURCES = $(GENERAL_SOURCES) $(ELIX_2_SOURCES) $(ELIX_4_SOURCES)
noinst_DATA = objectlist.awk.in
else
noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(GENERAL_SOURCES) $(ELIX_2_SOURCES) $(ELIX_4_SOURCES)
lib_a_CFLAGS = $(AM_CFLAGS)
noinst_DATA =
endif # USE_LIBTOOL

CHEWOUT_FILES = \
	bsearch.def \
	qsort.def \
	qsort_r.def

CHAPTERS =

include $(srcdir)/../../Makefile.shared
