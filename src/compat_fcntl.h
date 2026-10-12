/*============================================================================

  compat_fcntl.h

  Definition of the open() function, which conventionally is in fcntl.h,
  along with the file opening constants.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#ifdef LINUX
#include <fcntl.h>
#else

// Please note that most of the Linux O_XX constants make no sense to EFI.
// There is no O_APPEND, because EFI's Simple File Protocol doesn't support
//   appending to a file.

//Octal
#define O_RDONLY 0 
#define O_WRONLY 1 
#define O_CREAT  100 

/** open() behaves as on Linux, except that we don't provide the 3-parameter
    version that includes file modes. VFAT filesystems don't really support
    any of these modes. */
int open (const char *pathname, int flags);

#endif

