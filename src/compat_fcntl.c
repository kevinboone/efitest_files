/*============================================================================

  compat_fcntl.c

  Definition of the open() function, which conventionally is defined in 
  in fcntl.h.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/
#include "defs.h"
#include "compat_errno.h"
#include "compat_fcntl.h"
#include "compat_malloc.h"
#include "compat_stdio.h"
#include "context.h"
#include "efiutil.h"
#include "efifiles.h"
#include "filesystems.h"
#include "path.h"

#ifdef LINUX
#else

int open (const char *path, int flags)
  {
  int ret = 0;

  Path *p = path_new (path); 
  path_canonicalize (p);

  uint64_t mode = EFI_FILE_MODE_READ;
  if (flags & O_WRONLY) 
    mode |= EFI_FILE_MODE_WRITE;
  else 
    mode |= EFI_FILE_MODE_READ;
  if (flags & O_CREAT) 
    mode |= EFI_FILE_MODE_CREATE;

  int fd = context_get_next_fd();
  if (fd >= 0)
    {
    EFI_FILE_HANDLE h;
    CHAR16 *efipath;
    EFI_FILE_HANDLE root = filesystems_get_root_from_path 
        (path_cstr (p), &efipath);
    if (root)
      {
      EFI_STATUS err = efi_files_open_file (root, efipath, mode, &h); 
      if (err == EFI_SUCCESS)
	{
	if (context_store_fd_data (fd, h) == 0)
	  ret = 0;
	else
	  ret = -1; // errno should have been set
        }
      else
        {
        ret = -1;
        errno = efi_util_status_to_errno (err);
        }
      free (efipath);
      }
    else
      ret = -1; // errno should have been set
    }
  else
    {
    ret = -1;
    errno = ENFILE;
    } 

  path_destroy (p);
  return ret;
  }

#endif

