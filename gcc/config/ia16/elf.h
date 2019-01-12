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

#define CC1_SPEC	\
  "%{!mno-protected-mode:%{melks:-mprotected-mode}} " \
  "%{!mno-segment-relocation-stuff:" \
    "%{mcmodel=small|mcmodel=medium:-msegment-relocation-stuff}}"

/* Arrange for the linker script specification (%T...) to appear in LIB_SPEC
   if we are linking in default libraries, but in LINK_SPEC if we are not
   (i.e. -nostdlib or -nodefaultlibs).

   If default libraries are used, then we want them to appear at the end of
   the ld command line, so LIB_SPEC is the right place to use.

   If default libraries are not used, then GCC will not use LIB_SPEC at all,
   so we need to rely on LINK_SPEC to pass the linker script to ld.  -- tkchia
 */
#define LINK_SPEC	\
  "%{!T*:"		\
    "%{nostdlib|nodefaultlibs:" \
      "%{mcmodel=small:"	\
	"%{melks:%Telks-separate.ld;" \
	  "nostdlib|nostartfiles:%Tdos-ms.ld;:%Tdos-mss.ld};" \
	"melks:%Telks-combined.ld;" \
	"nostdlib|nostartfiles:%Tdos-mt.ld;:%Tdos-mts.ld" \
      "}"		\
    "}"			\
  "}"

#define STARTFILE_SPEC	\
  ""

#define ENDFILE_SPEC	\
  ""

#define LIB_SPEC	\
  "%{!T*:"		\
    "%{!nostdlib:"	\
      "%{!nodefaultlibs:" \
	"%{mcmodel=small:" \
	  "%{melks:%Telks-separate.ld;" \
	    "nostartfiles:%Tdos-msl.ld;:%Tdos-mssl.ld};" \
	  "melks:%Telks-combined.ld;" \
	  "nostartfiles:%Tdos-mtl.ld;:%Tdos-mtsl.ld" \
	"}"		\
      "}"		\
    "}"			\
  "}"
