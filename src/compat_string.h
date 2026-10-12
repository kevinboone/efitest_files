/*============================================================================

  compat_string.h

  String handling functions. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

extern long unsigned int strlen (const char *s);
extern int strcmp (const char *a, const char *b);
extern char *strcpy (char *dst, const char *src);
extern char *strdup (const char *s);

/** Note that strerror only returns meaningful text values for the
    EXXX constants that the program actually uses. Some of the EXX
    constants in compat_error.h will result in "unknown error"
    being returned. */
extern char *strerror (int errnum);

