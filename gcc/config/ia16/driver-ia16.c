/* Subroutines for the gcc driver targeting Intel 16-bit x86.
   Copyright (C) 2022 Free Software Foundation, Inc.
   Contributed by TK Chia <https://github.com/tkchia/>

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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "diagnostic.h"
#include "tm.h"

static const char dir_separator_str[] = { DIR_SEPARATOR, 0 };

const char *
rt_specs_file_spec_function (int argc, const char **argv)
{
  int i;
  const char *rel_dir, *full_dir, *rt, *p;
  char *full_spec, c;

  if (argc < 3)
    {
      fatal_error (input_location, "bad usage of spec function %qs", __func__);
      return "";
    }

  rel_dir = argv[0];
  full_dir = argv[1];
  rt = argv[2];

  for (i = 2; i < argc; ++i)
    {
      if (strcmp (argv[i], rt) != 0)
	{
	  error ("specified option %<-mr=%> more than once");
	  return "";
	}
    }

  p = rt;
  while ((c = *p++) != 0)
    if (! ISALNUM (c) && c != '_')
      {
	error ("strange runtime name %qs after %<-mr=%>: bad character %qc",
	       rt, c);
	return "";
      }

  full_spec = ACONCAT ((full_dir, dir_separator_str, "r-", rt, ".spec", NULL));
  if (access (full_spec, R_OK) != 0)
    {
      /*
       * For MS-DOS & ELKS, allow a r-msdos.spec (or r-elks.spec) file to
       * override our built-in specs.  For any other runtime environment,
       * there must be a specs file --- flag a fatal error if none is found.
       */
      if (strcmp (rt, "msdos") == 0 || strcmp (rt, "elks") == 0)
	return "";

      error ("cannot access runtime-specs for %qs expected at %qs",
	     rt, full_spec);
      return "";
    }

  return concat ("%:include(", rel_dir, dir_separator_str,
			       "r-", rt, ".spec%s)", NULL);
}
