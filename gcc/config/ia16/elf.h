/* GNU Compiler Collection target macros for ia16-*-elf targets.
   Copyright (C) 2007-2017 Free Software Foundation, Inc.
   Contributed by Rask Ingemann Lambertsen <rask@sygehus.dk>
   Changes by Andrew Jenner <andrew@codesourcery.com>
   Very preliminary small code model support by TK Chia

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the Free Software
   Foundation; either version 3 of the License, or (at your option) any
   later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
   details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Controlling the Compilation Driver, gcc.  */

#define DRIVER_SELF_SPECS \
  "%{melks-libc:-melks}", \
  "%{melks:%{!mno-protected-mode:-mprotected-mode}}", \
  "%{mcmodel=small|mcmodel=medium:" \
    "%{!mno-segment-relocation-stuff:-msegment-relocation-stuff}}"

/* For -nostdlib, -nodefaultlibs, and -nostartfiles:  arrange for the linker
   script specification (%T...) to appear in LIB_SPEC if we are linking in
   default libraries, but in LINK_SPEC if we are not (i.e. -nostdlib or
   -nodefaultlibs).

   If default libraries are used, then we want them to appear at the end of
   the ld command line, so LIB_SPEC is the right place to use.

   If default libraries are not used, then GCC will not use LIB_SPEC at all,
   so we need to rely on LINK_SPEC to pass the linker script to ld.

   As for the (undocumented) -r option:  I currently just arrange not to
   pass any linker script at all if -r appears.  (FIXME: This only really
   works if something like -nostdlib is also specified.  One is out of luck
   if they would also like to link in startup files or default libraries
   during -r.)  -- tkchia  */
#define LINK_SPEC	\
  "%{!T*:"		\
    "%{mmsdos-handle-v1:--defsym=__msdos_handle_v1=1} " \
    "%{!r:"		\
      "%{melks-libc:" \
	"%{mcmodel=small:%Telkslibc/elks-small.ld;:%Telkslibc/elks-tiny.ld};" \
	"nostdlib|nodefaultlibs:" \
	"%{mcmodel=small:" \
	  "%{melks:"	\
	    "%{nostdlib|nostartfiles:%Telk-ms.ld;:%Telk-mss.ld};" \
	    "nostdlib|nostartfiles:%Tdos-ms.ld;:%Tdos-mss.ld};" \
	  "melks:"	\
	    "%{nostdlib|nostartfiles:%Telk-mt.ld;:%Telk-mts.ld};" \
	  "nostdlib|nostartfiles:%Tdos-mt.ld;:%Tdos-mts.ld" \
	"}"		\
      "}"		\
    "}"			\
  "}"

#define STARTFILE_SPEC	\
  "%{melks-libc:-l:elkslibc/crt0.o}"

#define ENDFILE_SPEC	\
  ""

#define LIB_SPEC	\
  "%{melks-libc:-l:elkslibc/libc.a;" \
    "!T*:"		\
    "%{!r:"		\
      "%{!nostdlib:"	\
	"%{!nodefaultlibs:" \
	  "%{mnewlib-nano-stdio:" \
	    "%{mnewlib-autofloat-stdio:-lanstdio} -lnstdio;" \
	    "mnewlib-autofloat-stdio:-lastdio} " \
	  "%{mcmodel=small:" \
	    "%{melks:"	\
	      "%{nostartfiles:%Telk-msl.ld;:%Telk-mssl.ld};" \
	      "nostartfiles:%Tdos-msl.ld;:%Tdos-mssl.ld};" \
	    "melks:"	\
	      "%{nostartfiles:%Telk-mtl.ld;:%Telk-mtsl.ld};" \
	    "nostartfiles:%Tdos-mtl.ld;:%Tdos-mtsl.ld" \
	  "}"		\
	"}"		\
      "}"		\
    "}"			\
  "}"
