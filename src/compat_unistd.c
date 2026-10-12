/*============================================================================

  compat_unistd.c

  Implementations of fundamental file-handling functions. All are wrappers
  around the EFI file functions in efifiles.c. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX
#include <efi/efi.h>
#include <efi/efilib.h>
#endif

#include "defs.h"
#include "compat_malloc.h"
#include "compat_unistd.h"
#include "compat_string.h"
#include "compat_stdio.h"
#include "context.h"
#include "efifiles.h"
#include "efiutil.h"
#include "filesystems.h"
#include "path.h"

/*============================================================================

  close 

============================================================================*/
#ifndef LINUX
int close (int fd)
  {
  EFI_FILE_HANDLE h = (EFI_FILE_HANDLE)context_get_fd_data (fd);
  if (h)
    { 
    efi_files_close_file (h);
    context_clear_fd (fd);
    return 0;
    }
  else
    return -1; // errno should have been set
  }
#endif

/*============================================================================

  getcwd

============================================================================*/
char *getcwd (char *buf, size_t bufsize)
  {
  strcpy (buf, (char *)context_get_cwd ()); // TODO -- size
  return buf;
  }

/*============================================================================

  read 

============================================================================*/
#ifndef LINUX
int64_t read (int fd, void *buf, unsigned long count)
  {
  int ret = 0;
  EFI_FILE_HANDLE h = context_get_fd_data (fd);
  if (h)
    {
    long nread = 0;
    EFI_STATUS err = efi_files_read_file (h, buf, count, &nread);
    if (err == EFI_SUCCESS)
      {
      ret = nread;
      }
    else
      {
      ret = -1;
      errno = efi_util_status_to_errno (err);
      }
    }

  return ret;
  }
#endif
/*============================================================================

  unlink 

============================================================================*/
#ifndef LINUX
int unlink (const char *path)
  {
  int ret = 0;

  Path *p = path_new (path); 
  path_canonicalize (p);
  CHAR16 *efipath; 
  EFI_FILE_HANDLE root = filesystems_get_root_from_path 
     (path_cstr (p), &efipath);
  if (root)
    {
    EFI_STATUS err = efi_files_delete_file (root, efipath);
    if (err == EFI_SUCCESS)
      {
      ret = 0;
      }
    else
      {
      ret = -1;
      errno = efi_util_status_to_errno (err);
      }
    free (efipath);
    }
  else
    ret = -1;
  path_destroy (p);

  return ret;
  }

#endif

/*============================================================================

  write 

============================================================================*/
#ifndef LINUX
int64_t write (int fd, void *buf, unsigned long count)
  {
  int ret = 0;
  EFI_FILE_HANDLE h = context_get_fd_data (fd);
  if (h)
    {
    long nwritten = 0;
    EFI_STATUS err = efi_files_write_file (h, buf, count, &nwritten);
    if (err == EFI_SUCCESS)
      {
      ret = nwritten;
      }
    else
      {
      ret = -1;
      errno = efi_util_status_to_errno (err);
      }
    }

  return ret;
  }
#endif


