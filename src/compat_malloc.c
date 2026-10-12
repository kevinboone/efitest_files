/*============================================================================

  compat_malloc.c

  Implementations of malloc() and free() which, in an EFI build, are just
  wrappers around EFI API calls.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifdef LINUX
#else
#include <efi/efi.h>
#include <efi/efilib.h>
#include "defs.h"
#endif

#include "compat_malloc.h"

#ifndef LINUX
void *malloc (size_t l)
  {
  return AllocatePool (l);
  }

void free (void *s)
  {
  return FreePool (s);
  }
#endif

