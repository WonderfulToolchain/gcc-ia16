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

#include <dirent.h>
#include <strings.h>
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "diagnostic.h"
#include "tm.h"
#include "hashtab.h"

static const char dir_separator_str[] = { DIR_SEPARATOR, 0 };

static bool
string_is_just (const char *s, char c)
{
  return s[0] == c && s[1] == 0;
}

static int
string_hash_eq (const void *elem1, const void *elem2)
{
  return elem1 == elem2
	 || strcmp ((const char *) elem1, (const char *)elem2) == 0;
}

/*
 * TODO:
 * 1) Document the whole r-*.spec & r-*.d mechanism properly in gcc-ia16's
 *    info file.
 * 2) Maybe loosen the restrictions on file names.  -- tkchia
 */
const char *
rt_specs_files_spec_function (int argc, const char **argv)
{
  int i;
  const char *rel_dir, *full_dir, *rt, *p;
  char *full_spec, *subdir, *full_subdir, *res, c;
  DIR *dp;

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

  if (verbose_flag)
    fnotice (stderr, "%s: accepting specs file r-%s.spec\n", __func__, rt);

  res = concat ("%:include(", rel_dir, dir_separator_str,
			      "r-", rt, ".spec%s)", NULL);

  subdir = ACONCAT ((dir_separator_str, "r-", rt, ".d", NULL));
  full_subdir = ACONCAT ((full_dir, subdir, NULL));
  dp = opendir (full_subdir);
  if (dp)
    {
      struct dirent *ep;

      if (verbose_flag)
	fnotice (stderr, "%s: searching %s for extra specs files\n", __func__,
			 full_subdir);

      while ((ep = readdir (dp)) != NULL)
	{
	  const char *name = ep->d_name, *ext;

	  p = name;
	  while ((c = *p++) != '.')
	    if (! ISALNUM (c) && c != '_')
	      break;
	  ext = p;

	  if (c != '.'
	      || (strcasecmp (ext, "spec") != 0
		  && strcasecmp (ext, "specs") != 0
		  && strcasecmp (ext, "spe") != 0))
	    {
	      if (verbose_flag)
		fnotice (stderr, "%s: skipping %s, filename not accepted\n",
				 __func__, name);
	    }
	  else
	    {
	      full_spec = ACONCAT ((full_subdir, dir_separator_str,
				    name, NULL));
	      if (access (full_spec, R_OK) != 0)
		{
		  if (verbose_flag)
		    fnotice (stderr, "%s: skipping %s, inaccessible\n",
				     __func__, name);
		}
	      else
		{
		  if (verbose_flag)
		    fnotice (stderr, "%s: accepting extra specs file %s\n",
				     __func__, name);
		  /*
		   * FIXME?  This will take time that is quadratic in the
		   * number of specs files in the subdirectory.
		   */
		  res = reconcat (res, res, " %:include(", rel_dir, subdir,
							   dir_separator_str,
							   name, "%s)", NULL);
		}
	    }
	}

      closedir (dp);
    }

  return res;
}

const char *
check_rt_switches_spec_function (int argc, const char **argv)
{
  const char **fix_argv = XALLOCAVEC (const char *, argc);
  int fix_argc, part = 0, i, j;
  htab_t impl_sw_htab = htab_create_alloc (10, htab_hash_string,
					   string_hash_eq, NULL,
					   xcalloc, free),
	 warn_sw_htab = htab_create_alloc (10, htab_hash_string,
					   string_hash_eq, NULL,
					   xcalloc, free);
  void **slot;

  /*
   * gcc.c splits e.g. `-maout' into two words, `-' & `maout'.  Ugh.  Join
   * everything back together before further processing.
   */
  i = j = 0;
  while (j < argc)
    {
      const char *arg = argv[j];
      if (string_is_just (arg, '-') && j != argc - 1)
	{
	  fix_argv[i] = ACONCAT (("-", argv[j + 1], NULL));
	  j += 2;
	}
      else
	{
	  fix_argv[i] = argv[j];
	  ++j;
	}
      ++i;
    }
  fix_argc = i;

  for (i = 0; i < fix_argc; ++i)
    {
      const char *arg = fix_argv[i];
      if (string_is_just (arg, '^'))
	{
	  ++part;
	  if (part > 2)
	    break;
	}
      else
	{
	  switch (part)
	    {
	    case 0:
	      slot = htab_find_slot (impl_sw_htab, arg, INSERT);
	      *slot = (void *) arg;
	      break;

	    case 1:
	      slot = htab_find_slot (warn_sw_htab, arg, INSERT);
	      *slot = (void *) arg;
	      break;

	    default:
	      if (htab_find_slot (impl_sw_htab, arg, NO_INSERT))
		;  /* option implemented, do nothing */
	      else if (htab_find_slot (warn_sw_htab, arg, NO_INSERT))
		warning (0, "%qs not supported for this target; ignored", arg);
	      else
		error ("this target does not support %qs", arg);
	    }
	}
    }

  htab_delete (impl_sw_htab);
  htab_delete (warn_sw_htab);

  if (part != 2)
    fatal_error (input_location, "bad usage of spec function %qs", __func__);

  return "";
}

const char *
cpp_sys_defs_spec_function (int argc, const char **argv)
{
  const char *is, *q;
  char *os, *p;
  unsigned char c;
  int i;

  if (argc < 1)
    return "";

  is = argv[0];
  for (i = 1; i < argc; ++i)
    {
      if (strcmp (argv[i], is) != 0)
	{
	  fatal_error (input_location, "bad usage of spec function %qs",
		       __func__);
	  return "";
	}
    }

  os = (char *) xmalloc (sizeof ("-Asystem=") + sizeof ("-D__IA16_SYS_")
			 + 2 * strlen (is));

  p = stpcpy (os, "-Asystem=");
  q = is;
  while ((c = *q++) != 0)
    if (ISALNUM (c) || (char) c == '_')
      *p++ = c;

  p = stpcpy (p, " -D__IA16_SYS_");
  q = is;
  while ((c = *q++) != 0)
    if (ISALNUM (c) || (char) c == '_')
      *p++ = TOUPPER (c);

  *p = 0;
  return os;
}
