/*============================================================================

  compat_stdio.c

  Implementation of myprint(), which is just a wrapper around the corresponding
  nanoprintf function.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#else
#include <efi/efi.h>
#include <efi/efilib.h>
#endif

#include "compat_stdio.h"
#include "compat_string.h"

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 1

// Compile nanoprintf in this translation unit.
#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf.h"

int myprintf (const char *format, ...)
  {
  char buffer[1024]; // TODO TODO TODO
  va_list val;
  va_start (val, format);
  int const rv = npf_vsnprintf (buffer, sizeof (buffer), format, val);
  va_end (val);
#ifdef LINUX
  fputs (buffer, stdout);
#else
  Print (L"%a", buffer);  
#endif
  return rv;
  }


