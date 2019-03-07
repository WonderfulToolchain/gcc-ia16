/*
 * Experimental support for calling near functions (in the default text
 * segment) from far functions marked __attribute__ ((far_section)).
 *
 *   Copyright (C) 2019 Free Software Foundation, Inc.
 *   Written By TK Chia
 * 
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or (at your option) any
 * later version.
 * 
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 * 
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with this program;
 * see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>

__attribute__ ((__regparmcall__)) void __far
__ia16_far_builtin_apply_thunk (void (*func) (), void *args, size_t size)
{
  __builtin_return (__builtin_apply (func, args, size));
}
