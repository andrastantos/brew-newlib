## Process this file with automake to generate Makefile.in

AM_CPPFLAGS = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

noinst_LIBRARIES = lib.a

AM_CCASFLAGS = $(AM_CPPFLAGS)

lib_a_SOURCES = setjmp.S assert.c clearerr.c creat.c fclose.c feof.c \
	ferror.c fflush.c fgetc.c fgetpos.c fgets.c fileno.c fiprintf.S \
	fiscanf.S fopen.c fprintf.S fputc.c fputs.c fread.c freopen.c \
	fscanf.S fseek.c fsetpos.c ftell.c fwrite.c getc.c getchar.c \
	gets.c impure.c iprintf.S iscanf.S memcmp.c memcpy.c memmove.c \
	memset.c perror.c printf.S putc.c putchar.c puts.c remove.c \
	rename.c rewind.c scanf.S setbuf.c setvbuf.c siprintf.S siscanf.S \
	sleep.c sniprintf.S snprintf.S sprintf.S sscanf.S stdio.c strcat.c \
	strchr.c strcmp.c strcpy.c strcspn.c strlen.c strncat.c strncmp.c \
	strncpy.c strpbrk.c strrchr.c strspn.c strxfrm.c tmpfile.c \
	tmpnam.c ungetc.c usleep.c vfiprintf.c vfiscanf.c vfprintf.c \
	vfscanf.c viprintf.c viscanf.c vprintf.c vscanf.c vsiprintf.c \
	vsiscanf.c vsniprintf.c vsnprintf.c vsprintf.c vsscanf.c \
	stack_reg_va.S spu_clock_svcs.c spu_clock_stop.c spu_timer_flih.S \
	spu_timer_slih.c spu_timer_slih_reg.c spu_timer_svcs.c \
	spu_timer_stop.c spu_timer_free.c spu_timebase.c fdopen.c

if HAVE_SPU_EA
lib_a_SOURCES += calloc_ea.c free_ea.c malloc_ea.c memchr_ea.c memcmp_ea.c \
	memcpy_ea.c memmove_ea.c memset_ea.c mmap_ea.c mremap_ea.c msync_ea.c \
	munmap_ea.c posix_memalign_ea.c realloc_ea.c strcat_ea.c strchr_ea.c \
	strcmp_ea.c strcpy_ea.c strcspn_ea.c strlen_ea.c strncat_ea.c strncmp_ea.c \
	strncpy_ea.c strpbrk_ea.c strrchr_ea.c strspn_ea.c strstr_ea.c read_ea.c \
	pread_ea.c readv_ea.c write_ea.c pwrite_ea.c writev_ea.c spu-mcount.S \
	spu-gmon.c
endif

lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../.. -I ../../../../config
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host

