/*============================================================================

  textutil.c

  General text formatting functions. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_stdio.h" 
#include "nanoprintf.h"

static char *size_suffix[] = {"", "K", "M", "G", "T"};

/*============================================================================

  textutil_humanize_size

============================================================================*/
void textutil_humanize_size (long int n, char *buffer, int max)
  {
  char suffixes = sizeof(size_suffix) / sizeof(size_suffix[0]);
  int i = 0;
  double float_n = n;
  if (n > 1024) 
    {
    for (i = 0; (n / 1024) > 0 && i < suffixes - 1; i++, n /= 1024)
    float_n = n / 1024.0;
    }

  npf_snprintf (buffer, max, "%6.1lf%s", float_n, size_suffix[i]);
  }


