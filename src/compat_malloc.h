/*============================================================================

  compat_malloc.h

  Definitions of malloc() and free() which, in an EFI build, are just
  wrappers around EFI API calls.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#include "defs.h"
extern void *malloc (size_t length); 
extern void free (void *s);

