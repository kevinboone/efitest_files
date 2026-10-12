/*============================================================================

  context.h

  The shell's operating environment and settings, including the
  file descriptor table. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

extern void context_init (void);
extern int context_cd (UTF8 *cd);
extern UTF8* context_get_cwd (void);

#ifndef LINUX
extern int context_clear_fd (int fd);
extern int context_get_next_fd (void);
extern void *context_get_fd_data (int fd);
extern int context_store_fd_data (int fd, void *data);
#endif

extern int errno;
