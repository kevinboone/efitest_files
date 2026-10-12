/*============================================================================

  compat_unistd.h

  Definitions of the basic file-handling functions that are usually
  in unistd.h

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#ifdef LINUX
#include <unistd.h>
#else
#include <efi/efi.h>
extern int close (int fd);
extern char *getcwd (char *buf, size_t bufsize);
extern int64_t read (int fd, void *buf, size_t count);
extern int64_t write (int fd, void *buf, size_t count);
extern int unlink (const char *path);
#endif
