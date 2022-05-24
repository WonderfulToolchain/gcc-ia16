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

extern const char *rt_specs_file_spec_function (int, const char **);

#define EXTRA_SPEC_FUNCTIONS \
  { "rt-specs-file", rt_specs_file_spec_function },

#define DRIVER_SELF_SPECS \
  "%{mr=*:;:-mr=msdos}", \
  "%:rt-specs-file(rt-specs rt-specs%s %{mr=*:%*})", \
  "%{mdosx:%{mr=msdos:;:%e-mdosx only supported for MS-DOS target}}", \
  "%{mmsdos-handle-v1:" \
    "%{mr=msdos:;:%e-mmsdos-handle-v1 only supported for MS-DOS target}}", \
  "%{mhandle-non-i186:" \
    "%{mr=msdos:;:%e-mhandle-non-i186 only supported for MS-DOS target}}", \
  "%{mhandle-non-i286:" \
    "%{mr=msdos:;:%e-mhandle-non-i286 only supported for MS-DOS target}}", \
  "%{mcmodel=medium:" \
    "%{mdosx:%emedium model not supported in DOS extender mode}}", \
  "%{mdosx:"		\
    "%{march=*:;:-march=i80286} " \
    "%{mno-segelf:;:-msegelf} " \
    "%{fuse-ld=*:;:-fuse-ld=gold} " \
    "%{msegment-relocation-stuff:" \
      "%nwarning: -msegment-relocation-stuff with -mdosx may result in " \
		 "bogus output}}", \
  "%{mr=elks:"		\
    "-nostdinc "	\
    "%{mno-segelf:;:-msegelf} " \
    "%{fuse-ld=*:;:-fuse-ld=gold} " \
    "%{mnewlib-autofloat-stdio:;:-mno-newlib-autofloat-stdio}}", \
  "%{mr=elks|mdosx:%{!mno-protected-mode:-mprotected-mode}}", \
  "%{mr=elks|mdosx|mseparate-code-segment:%{mcmodel=*:;:-mcmodel=small}}", \
  "%{mcmodel=small|mcmodel=medium:" \
    "%{!mdosx:"		\
      "%{!mno-segment-relocation-stuff:-msegment-relocation-stuff}}}", \
  "%{maout-total=*:"	\
    "%{maout-chmem=*:%emay not use both -maout-total= and -maout-chmem=}" \
    "%{maout-stack=*:%emay not use both -maout-total= and -maout-stack=}" \
    "%{maout-heap=*:%emay not use both -maout-total= and -maout-heap=}}", \
  "%{maout-chmem=*:"	\
    "%{maout-stack=*:%emay not use both -maout-chmem= and -maout-stack=}" \
    "%{maout-heap=*:%emay not use both -maout-chmem= and -maout-heap=}}"

/* This is a hack.  When -mr=elks is specified, then, combined with the
   -nostdinc above, this hack will (try to) make GCC use the include files
   under the -mr=elks multilib directory, rather than the Newlib include
   files in the usual locations.

   We also need to extend the hack to
     * rope in the libgcc include directories --- via `include-fixed' ---
       since elks-libc's headers use libgcc's.
     * fall back on the include directories for the default calling
       convention (.../ia16-elf/lib/elkslibc/include/), in case the user
       says e.g. `-mr=elks -mregparmcall' and no include files are
       installed specifically for this calling convention.

   Again, this is a hack.  -- tkchia  */
#define CPP_SPEC	\
  "%{mr=elks:-isystem include-fixed/../include%s " \
	    "-isystem include-fixed%s " \
	    "-isystem include%s " \
	    "-isystem elkslibc/include%s}" \
  "%{mcmodel=medium:%{,c++|,c++-header:%emedium model not supported for C++}}"

#define ASM_SPEC	\
  "%{msegelf:--32-segelf}"

/* For -nostdlib, -nodefaultlibs, and -nostartfiles:  arrange for the linker
   script specification (%T...) to appear in LIB_SPEC if we are linking in
   default libraries, but in LINK_SPEC if we are not (i.e. -nostdlib or
   -nodefaultlibs).  An exception is the main linker script for -mdosx, which
   will always appear in LINK_SPEC.

   If default libraries are used, then we want them to appear at the end of
   the ld command line, so LIB_SPEC is the right place to use.

   If default libraries are not used, then GCC will not use LIB_SPEC at all,
   so we may need to rely on LINK_SPEC to pass the linker script to ld.
	-- tkchia */
#define LINK_SPEC	\
  "%{!T*:"		\
    "%{mdosx:"		\
	"%Tdx-m%(cmodel_ld);" \
      "mr=elks:"	\
	"%Telks-%(cmodel_long_ld);" \
      "nostdlib|nodefaultlibs:" \
	"%{mtsr:"	\
	    "%{nostdlib|nostartfiles:%Tdtr-m%(cmodel_ld);" \
	      ":%Tdtr-m%(cmodel_s_ld)};" \
	  "nostdlib|nostartfiles:" \
	    "%Tdos-m%(cmodel_ld);" \
	  ":%Tdos-m%(cmodel_s_ld)}" \
    "}"			\
  "} "			\
  "%{mr=elks:"	\
    "-m i386elks "	\
    "%{maout-total=*:--defsym=_total=%*} " \
    "%{maout-chmem=*:--defsym=_chmem=%*} " \
    "%{maout-stack=*:--defsym=_stack=%*} " \
    "%{maout-heap=*:--defsym=_heap=%*}} " \
  "%{!mr=elks:"	\
    "%{maout-heap=*:--defsym=__heaplen_val=%*}}"

#define STARTFILE_SPEC	\
  "%{mr=elks:"	\
      "-l:crt0.o;"	\
    "mdosx:"		\
      "-l:dx-%(cmodel_c0_a)}"

#define ENDFILE_SPEC	\
  ""

#define LIB_SPEC	\
  "%{mr=msdos:"	\
      "%{mnewlib-nano-stdio:" \
	"%{!mno-newlib-autofloat-stdio:-lanstdio} -lnstdio;" \
	":%{!mno-newlib-autofloat-stdio:-lastdio} -lfstdio} " \
      "%{mdosx:"	\
	  "-l:dx-%(cmodel_lc_a);" \
        ":"		\
	  "%{mmsdos-handle-v1:-ldosv1} " \
	  "%{mhandle-non-i286:" \
	      "%{march=i80286|march=i286:-lck186};" \
	    "mhandle-non-i186:" \
	      "%{march=any|march=i8086|march=i8088:;" \
		"march=*:-lck086}} " \
	  "%{mtsr:" \
	      "%{nostartfiles:%Tdtr-m%(cmodel_l_ld);:%Tdtr-m%(cmodel_sl_ld)};"\
	    "nostartfiles:" \
	      "%Tdos-m%(cmodel_l_ld);" \
	    ":%Tdos-m%(cmodel_sl_ld)}" \
      "};"		\
      ":"		\
      "-lc -lgcc -lc"	\
  "}"

#define EXTRA_SPECS	\
  { "cmodel_ld", "%{mcmodel=medium:m.ld;mcmodel=small:s.ld;:t.ld}" }, \
  { "cmodel_c0_a", "%{mcmodel=medium:m-c0.a;mcmodel=small:s-c0.a;:t-c0.a}" }, \
  { "cmodel_lc_a", "%{mcmodel=medium:m-lc.a;mcmodel=small:s-lc.a;:t-lc.a}" }, \
  { "cmodel_s_ld", "%{mcmodel=medium:ms.ld;mcmodel=small:ss.ld;:ts.ld}" }, \
  { "cmodel_l_ld", "%{mcmodel=medium:ml.ld;mcmodel=small:sl.ld;:tl.ld}" }, \
  { "cmodel_sl_ld", "%{mcmodel=medium:msl.ld;mcmodel=small:ssl.ld;:tsl.ld}" },\
  { "cmodel_long_ld", "%{mcmodel=*:%*.ld;:tiny.ld}" }

#define POST_LINK_SPEC	\
  "%{!mno-post-link:"	\
    "%{mdosx|mr=elks:" \
      "%{mdosx:%:if-exists-else(../lib/../bin/elf2dosx%s elf2dosx);" \
	     ":%:if-exists-else(../lib/../bin/elf2elks%s elf2elks)} " \
      "%{v} "		\
      "%{mcmodel=tiny:--tiny} " \
      "%{maout-total=*:--total-data %*} " \
      "%{maout-chmem=*:--chmem %*} " \
      "%{maout-stack=*:--stack %*} " \
      "%{maout-heap=*:--heap %*} " \
      "%{o*:%*} %{!o*:a.out}}}"
