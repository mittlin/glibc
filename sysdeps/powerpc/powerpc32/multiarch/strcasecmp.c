/* Multiple versions of strcasecmp.
   Copyright (C) 2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef NOT_IN_libc
# ifdef SHARED
#  undef libc_hidden_builtin_def
#  define libc_hidden_builtin_def(name) \
  __hidden_ver1 (__strcasecmp_ppc32, __GI_strcasecmp, __strcasecmp_ppc32);
# endif

# undef strcasecmp
# define strcasecmp __redirect_strcasecmp
# include <string.h>
# undef strcasecmp
# define strcasecmp __strcasecmp_ppc32

extern __typeof (__redirect_strcasecmp) __strcasecmp_ppc32 attribute_hidden;
extern __typeof (__redirect_strcasecmp) __strcasecmp_power7 attribute_hidden;
#endif

#include "string/strcasecmp.c"
#undef strcasecmp

#ifndef NOT_IN_libc
# include <shlib-compat.h>
# include "init-arch.h"

/* Avoid DWARF definition DIE on ifunc symbol so that GDB can handle
   ifunc symbol properly.  */
extern __typeof (__redirect_strcasecmp) __libc_strcasecmp;
libc_ifunc (__libc_strcasecmp,
	    (hwcap & PPC_FEATURE_HAS_VSX)
            ? __strcasecmp_power7
            : __strcasecmp_ppc32);

weak_alias (__libc_strcasecmp, strcasecmp)
#endif