/*============================================================================

  compat_limits.h

  Sizes, etc 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#define PATH_MAX 1024
// Max number of open files
#define NFILES_MAX 20
// Max number of mounted volumes
// Right now, keep this to 10, so we can use a single digit as the
//  start of every path ("/0/..."
#define NVOL_MAX 10
