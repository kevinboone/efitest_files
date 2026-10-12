/*============================================================================

  compat_stat.h

  Definition of the stat() function, and all the constants that go with it.
  Well, all the constants that make sense to EFI.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#ifdef LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <efi/efi.h>

#include "compat_time.h"

// These values are octal
#define S_IFMT 0170000 
#define S_IFREG 0100000 
#define S_IFDIR 0040000 
#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

struct stat
  {
  int32_t st_mode;
  int64_t st_size;
  time_t st_mtime;
  };

int stat (const char *pathname, struct stat *statbuff);

#endif

