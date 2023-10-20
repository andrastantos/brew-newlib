/* termios tcflag symbolic contants definitions.  Linux/generic version.
   Copyright (C) 2019-2022 Free Software Foundation, Inc.
   Modified by Andras Tantos

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <https://www.gnu.org/licenses/>.  */

#pragma once

#define	TCSANOW     0    // Act now
#define	TCSADRAIN   1    // Act after drain
#define	TCSAFLUSH   2    // Act after flush

typedef unsigned char    cc_t;
typedef unsigned int     speed_t;
typedef unsigned int     tcflag_t;

#define NCCS 32
struct termios {
    tcflag_t c_iflag;     /* input mode flags */
    tcflag_t c_oflag;     /* output mode flags */
    tcflag_t c_cflag;     /* control mode flags */
    tcflag_t c_lflag;     /* local mode flags */
    cc_t c_line;          /* line discipline */
    cc_t c_cc[NCCS];      /* control characters */
    speed_t c_ispeed;     /* input speed */
    speed_t c_ospeed;     /* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
};


/* c_iflag bits */
#define IGNBRK     0000001  /* Ignore break condition.  */
#define BRKINT     0000002  /* Signal interrupt on break.  */
#define IGNPAR     0000004  /* Ignore characters with parity errors.  */
#define PARMRK     0000010  /* Mark parity and framing errors.  */
#define INPCK      0000020  /* Enable input parity check.  */
#define ISTRIP     0000040  /* Strip 8th bit off characters.  */
#define INLCR      0000100  /* Map NL to CR on input.  */
#define IGNCR      0000200  /* Ignore CR.  */
#define ICRNL      0000400  /* Map CR to NL on input.  */
#define IUCLC      0001000  /* Map uppercase characters to lowercase on input (not in POSIX). */
#define IXON       0002000  /* Enable start/stop output control.  */
#define IXANY      0004000  /* Enable any character to restart output.  */
#define IXOFF      0010000  /* Enable start/stop input control.  */
#define IMAXBEL    0020000  /* Ring bell when input queue is full (not in POSIX). */
#define IUTF8      0040000  /* Input is UTF8 (not in POSIX). */

/* c_oflag bits */
#define OPOST      0000001  /* Post-process output.  */
#define OLCUC      0000002  /* Map lowercase characters to uppercase on output. (not in POSIX). */
#define ONLCR      0000004  /* Map NL to CR-NL on output.  */
#define OCRNL      0000010  /* Map CR to NL on output.  */
#define ONOCR      0000020  /* No CR output at column 0.  */
#define ONLRET     0000040  /* NL performs CR function.  */
#define OFILL      0000100  /* Use fill characters for delay.  */
#define OFDEL      0000200  /* Fill is DEL.  */
#if defined __USE_MISC || defined __USE_XOPEN
# define NLDLY     0000400  /* Select newline delays:  */
# define   NL0     0000000  /* Newline type 0.  */
# define   NL1     0000400  /* Newline type 1.  */
# define CRDLY     0003000  /* Select carriage-return delays:  */
# define   CR0     0000000  /* Carriage-return delay type 0.  */
# define   CR1     0001000  /* Carriage-return delay type 1.  */
# define   CR2     0002000  /* Carriage-return delay type 2.  */
# define   CR3     0003000  /* Carriage-return delay type 3.  */
# define TABDLY    0014000  /* Select horizontal-tab delays:  */
# define   TAB0    0000000  /* Horizontal-tab delay type 0.  */
# define   TAB1    0004000  /* Horizontal-tab delay type 1.  */
# define   TAB2    0010000  /* Horizontal-tab delay type 2.  */
# define   TAB3    0014000  /* Expand tabs to spaces.  */
# define BSDLY     0020000  /* Select backspace delays:  */
# define   BS0     0000000  /* Backspace-delay type 0.  */
# define   BS1     0020000  /* Backspace-delay type 1.  */
# define FFDLY     0100000  /* Select form-feed delays:  */
# define   FF0     0000000  /* Form-feed delay type 0.  */
# define   FF1     0100000  /* Form-feed delay type 1.  */
#endif
#define VTDLY      0040000  /* Select vertical-tab delays:  */
#define   VT0      0000000  /* Vertical-tab delay type 0.  */
#define   VT1      0040000  /* Vertical-tab delay type 1.  */
#ifdef __USE_MISC
# define XTABS     0014000
#endif

/* c_lflag bits */
#define ISIG       0000001   /* Enable signals.  */
#define ICANON     0000002   /* Canonical input (erase and kill processing).  */
#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
# define XCASE     0000004
#endif
#define ECHO       0000010   /* Enable echo.  */
#define ECHOE      0000020   /* Echo erase character as error-correcting backspace. */
#define ECHOK      0000040   /* Echo KILL.  */
#define ECHONL     0000100   /* Echo NL.  */
#define NOFLSH     0000200   /* Disable flush after interrupt or quit.  */
#define TOSTOP     0000400   /* Send SIGTTOU for background output.  */
#ifdef __USE_MISC
# define ECHOCTL   0001000  /* If ECHO is also set, terminal special characters are echoed as ^X (not in POSIX). */
# define ECHOPRT   0002000  /* If ICANON and ECHO are also set, characters are printed as they are being erased (not in POSIX). */
# define ECHOKE    0004000  /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT (not in POSIX). */
# define FLUSHO    0010000  /* Output is being flushed. This flag is toggled by typing the DISCARD character (not in POSIX). */
# define PENDIN    0040000  /* All characters in the input queue are reprinted when the next character is read (not in POSIX). */
#endif
#define IEXTEN     0100000  /* Enable implementation-defined input processing. */
#ifdef __USE_MISC
# define EXTPROC   0200000
#endif

/* c_cflag bits.  */
#define CSIZE      0000060
#define   CS5      0000000
#define   CS6      0000020
#define   CS7      0000040
#define   CS8      0000060
#define CSTOPB     0000100
#define CREAD      0000200
#define PARENB     0000400
#define PARODD     0001000
#define HUPCL      0002000
#define CLOCAL     0004000

#ifdef __cplusplus
extern "C" {
#endif

// For now, only implement these functions.
extern int tcgetattr(int fd,struct termios *termios_p);
extern int tcsetattr(int fd,int optional_actions,const struct termios *termios_p);

#ifdef __cplusplus
}
#endif

