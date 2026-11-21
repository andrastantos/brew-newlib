/*-
 * Copyright (c) 1983, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* Call-graph profiling (gcc -p/-pg, gprof) for brew, shared by both
   run-time environments.  Adapted from libgloss/rx/mcount.c, itself a
   subset of glibc's mcount.c, gmon.c and gmon.h.

   gcc calls _mcount (frompc, selfpc) as an ordinary function at the
   start of every profiled function (PROFILE_HOOK in gcc/config/brew):
   frompc is the return address into the caller, selfpc the address of
   the function being entered.  Referencing _mcount pulls this object in,
   and its constructor starts profiling and registers _mcleanup with
   atexit, which writes gmon.out; no separate startup file is needed.

   Only the call graph is recorded: there is no timer to sample the PC
   with, so gmon.out has no histogram.  In the operating environment,
   which has no file system, open fails and _mcleanup prints a message
   instead.  */

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>

/* Each from-hash bucket covers HASHFRACTION * sizeof (unsigned long) =
   8 bytes of text, as in glibc.  Call sites closer together than that
   share a from address, which still lies in the right caller.  */
#define HASHFRACTION	2

/* Percent of text space to allocate for tostructs, with bounds.  */
#define ARCDENSITY	3
#define MINARCS		50
#define MAXARCS		(1 << 20)

#define GMON_MAGIC	"gmon"
#define GMON_VERSION	1

#define ROUNDDOWN(x, y)	(((x) / (y)) * (y))
#define ROUNDUP(x, y)	((((x) + (y) - 1) / (y)) * (y))

struct tostruct
{
  unsigned long selfpc;
  unsigned long count;
  unsigned long link;
};

enum profiling_state
{
  GMON_PROF_OFF,
  GMON_PROF_ON,
  GMON_PROF_BUSY,
  GMON_PROF_ERROR
};

struct gmonparam
{
  enum profiling_state state;
  unsigned long *froms;
  unsigned long fromssize;
  struct tostruct *tos;
  long tolimit;
  unsigned long lowpc;
  unsigned long highpc;
  unsigned long textsize;
  long log_hashfraction;
};

/* gmon.out header and call-graph record, as written to the file.  */
struct gmon_hdr
{
  char cookie[4];
  char version[4];
  char spare[3 * 4];
};

#define GMON_TAG_CG_ARC	1

struct gmon_cg_arc_record
{
  char tag;
  char from_pc[sizeof (char *)];
  char self_pc[sizeof (char *)];
  char count[4];
};

void _mcount (unsigned long, unsigned long);
void _monstartup (unsigned long, unsigned long);
void _mcleanup (void);

/* Text bounds, from the linker script (ld's default script provides
   both).  */
extern char __executable_start[] __attribute__ ((weak));
extern char _etext[] __attribute__ ((weak));

static struct gmonparam _gmonparam;

void
_mcount (unsigned long frompc, unsigned long selfpc)
{
  struct gmonparam *p = &_gmonparam;
  unsigned long *frompcindex;
  struct tostruct *top;
  struct tostruct *prevtop;
  unsigned long toindex;

  /* Not profiling, or called recursively (from a profiled function that
     _mcount uses).  Not thread-safe.  */
  if (p->state != GMON_PROF_ON)
    return;
  p->state = GMON_PROF_BUSY;

  /* Calls from outside the profiled text (crt0, a signal handler on the
     stack) aren't recorded.  */
  frompc -= p->lowpc;
  if (frompc >= p->textsize)
    goto done;

  frompcindex = p->froms + (frompc >> p->log_hashfraction);
  toindex = *frompcindex;

  if (toindex == 0)
    {
      /* First time traversing this arc.  */
      toindex = ++p->tos[0].link;
      if (toindex >= p->tolimit)
	goto overflow;
      *frompcindex = toindex;
      top = p->tos + toindex;
      top->selfpc = selfpc;
      top->count = 1;
      top->link = 0;
      goto done;
    }

  top = p->tos + toindex;
  if (top->selfpc == selfpc)
    {
      /* Arc at the front of the chain: the usual case.  */
      top->count++;
      goto done;
    }

  /* Look down the chain; move the arc to the front once found.  */
  for (;;)
    {
      if (top->link == 0)
	{
	  /* Not in the chain: allocate a new tostruct at its head.  */
	  toindex = ++p->tos[0].link;
	  if (toindex >= p->tolimit)
	    goto overflow;
	  top = p->tos + toindex;
	  top->selfpc = selfpc;
	  top->count = 1;
	  top->link = *frompcindex;
	  *frompcindex = toindex;
	  goto done;
	}

      prevtop = top;
      top = p->tos + top->link;
      if (top->selfpc == selfpc)
	{
	  top->count++;
	  toindex = prevtop->link;
	  prevtop->link = top->link;
	  top->link = *frompcindex;
	  *frompcindex = toindex;
	  goto done;
	}
    }

 done:
  p->state = GMON_PROF_ON;
  return;

 overflow:
  p->state = GMON_PROF_ERROR;
  write (2, "mcount: tos overflow\n", 21);
}

void
_monstartup (unsigned long lowpc, unsigned long highpc)
{
  struct gmonparam *p = &_gmonparam;
  unsigned long tossize;
  char *cp;

  /* calloc may itself be profiled.  */
  p->state = GMON_PROF_BUSY;

  p->lowpc = ROUNDDOWN (lowpc, HASHFRACTION * sizeof (*p->froms));
  p->highpc = ROUNDUP (highpc, HASHFRACTION * sizeof (*p->froms));
  p->textsize = p->highpc - p->lowpc;
  p->log_hashfraction = ffs (HASHFRACTION * sizeof (*p->froms)) - 1;
  p->fromssize = p->textsize / HASHFRACTION;
  p->tolimit = p->textsize * ARCDENSITY / 100;
  if (p->tolimit < MINARCS)
    p->tolimit = MINARCS;
  else if (p->tolimit > MAXARCS)
    p->tolimit = MAXARCS;
  tossize = p->tolimit * sizeof (struct tostruct);

  cp = calloc (p->fromssize + tossize, 1);
  if (cp == NULL)
    {
      write (2, "monstartup: out of memory\n", 26);
      p->tos = NULL;
      p->state = GMON_PROF_ERROR;
      return;
    }

  p->tos = (struct tostruct *) cp;
  p->froms = (unsigned long *) (cp + tossize);
  p->tos[0].link = 0;
  p->state = GMON_PROF_ON;
}

static void
write_call_graph (int fd)
{
#define NARCS_PER_WRITE	32
  struct gmon_cg_arc_record raw_arc[NARCS_PER_WRITE];
  unsigned long from_index;
  unsigned long from_len;
  unsigned long to_index;
  unsigned long frompc;
  int nfilled = 0;
  int i;

  for (i = 0; i < NARCS_PER_WRITE; i++)
    raw_arc[i].tag = GMON_TAG_CG_ARC;

  from_len = _gmonparam.fromssize / sizeof (*_gmonparam.froms);
  for (from_index = 0; from_index < from_len; from_index++)
    {
      if (_gmonparam.froms[from_index] == 0)
	continue;

      frompc = _gmonparam.lowpc
	       + (from_index << _gmonparam.log_hashfraction);

      for (to_index = _gmonparam.froms[from_index];
	   to_index != 0;
	   to_index = _gmonparam.tos[to_index].link)
	{
	  struct gmon_cg_arc_record *arc = raw_arc + nfilled;

	  memcpy (arc->from_pc, &frompc, sizeof (arc->from_pc));
	  memcpy (arc->self_pc, &_gmonparam.tos[to_index].selfpc,
		  sizeof (arc->self_pc));
	  memcpy (arc->count, &_gmonparam.tos[to_index].count,
		  sizeof (arc->count));

	  if (++nfilled == NARCS_PER_WRITE)
	    {
	      write (fd, raw_arc, sizeof raw_arc);
	      nfilled = 0;
	    }
	}
    }

  if (nfilled > 0)
    write (fd, raw_arc, nfilled * sizeof (raw_arc[0]));
}

static void
write_gmon (void)
{
  struct gmon_hdr ghdr;
  unsigned long version = GMON_VERSION;
  int fd;

  fd = open ("gmon.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (fd < 0)
    {
      write (2, "_mcleanup: could not create gmon.out\n", 37);
      return;
    }

  memset (&ghdr, 0, sizeof (ghdr));
  memcpy (ghdr.cookie, GMON_MAGIC, sizeof (ghdr.cookie));
  memcpy (ghdr.version, &version, sizeof (ghdr.version));
  write (fd, &ghdr, sizeof (ghdr));

  write_call_graph (fd);

  close (fd);
}

void
_mcleanup (void)
{
  if (_gmonparam.state != GMON_PROF_ERROR && _gmonparam.tos != NULL)
    {
      _gmonparam.state = GMON_PROF_OFF;
      write_gmon ();
    }

  if (_gmonparam.tos != NULL)
    {
      free (_gmonparam.tos);
      _gmonparam.tos = NULL;
    }
  _gmonparam.state = GMON_PROF_OFF;
}

static void __attribute__ ((constructor))
_mcount_start (void)
{
  if (__executable_start == NULL || _etext == NULL
      || _etext <= __executable_start)
    {
      write (2, "monstartup: no text bounds\n", 27);
      return;
    }

  _monstartup ((unsigned long) __executable_start, (unsigned long) _etext);
  atexit (_mcleanup);
}
