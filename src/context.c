/*============================================================================

  context.c

  The shell's operating environment and settings, including the 
  file descriptor table.  

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_errno.h" 
#include "compat_limits.h" 
#include "compat_string.h" 
#include "compat_stdio.h" 
#include "context.h" 
#include "path.h" 

static UTF8 cwd[256]; // TODO

#ifndef LINUX
static void *files[NFILES_MAX];
#endif
int errno = 0;

/*============================================================================

  context_cd

============================================================================*/
int context_cd (UTF8 *cd)
  {
  int ret = 0;
  Path *p = path_new (cwd);

  path_append (p, cd);

  if (path_is_directory (p))
    {
    path_canonicalize (p);
    ret = 0;
    }
  else
    {
    errno = ENOTDIR; 
    ret = -1;
    }
  
  if (ret == 0)
    strcpy (cwd, path_cstr (p)); // TODO -- length
  
  path_destroy (p);
  return ret;
  }


/*============================================================================

  context_clear_fd

============================================================================*/
#ifndef LINUX
int context_clear_fd (int fd)
  {
  if (fd < 0 || fd >= NFILES_MAX)
    {
    errno = EINVAL;
    return -1;
    }
  files[fd] = NULL;
  return 0;  
  }
#endif


/*============================================================================

  context_get_next_fd

============================================================================*/
#ifndef LINUX
int context_get_next_fd (void)
  {
  for (int i = 0; i < NFILES_MAX; i++)
    {
    if (files[i] == NULL) return i;
    }

  return -1;
  errno = ENFILE;
  }
#endif

/*============================================================================

  context_init

============================================================================*/
void context_init (void)
  {
#ifdef LINUX
  strcpy (cwd, "/");
#else
  strcpy (cwd, "/0");
#endif
  }

/*============================================================================

  context_get_cwd

============================================================================*/
UTF8* context_get_cwd (void)
  {
  return cwd;
  }

/*============================================================================

  context_get_fd_data

============================================================================*/
#ifndef LINUX
void *context_get_fd_data (int fd)
  {
  if (fd < 0 || fd >= NFILES_MAX)
    {
    errno = EINVAL;
    return NULL;
    }
  void *data = files[fd];
  if (data)
    return data;
  
  errno = EBADF;
  return NULL;  
  }
#endif

/*============================================================================

  context_store_fd_data

============================================================================*/
#ifndef LINUX
int context_store_fd_data (int fd, void *data)
  {
  if (fd < 0 || fd >= NFILES_MAX)
    {
    errno = EINVAL;
    return -1;
    }
  files[fd] = data;
  return 0;  
  }
#endif


