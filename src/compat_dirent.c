/*============================================================================

  compat_dirent.h

  Implementations of opendir(), readdir(), and closedir() for the 
  EFI environment. The implementations essentially wrap EFI 
  functionality in efifiles.c.

  See compat_dirent.h for more information.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>
#include "defs.h"
#include "compat_errno.h"
#include "compat_dirent.h"
#include "compat_malloc.h"
#include "compat_string.h"
#include "compat_stdio.h"
#include "context.h"
#include "efiutil.h"
#include "efifiles.h"
#include "filesystems.h"
#include "path.h"

/*============================================================================

  closedir

============================================================================*/
int closedir (DIR *dirp)
  {
  if (dirp->dir_handle) 
    efi_files_close_file (dirp->dir_handle);
  return 0;
  }

/*============================================================================

  opendir

============================================================================*/
DIR *opendir (const char *path)
  {
  DIR *ret = NULL;

  Path *p = path_new (path);
  if (path_canonicalize (p) == 0) 
    {
    CHAR16 *epath;

    EFI_FILE_HANDLE handle;
    EFI_FILE_HANDLE root = filesystems_get_root_from_path (path_cstr(p), &epath);
    if (root)
      {
      EFI_STATUS err = efi_files_open_file (root, epath, 
	EFI_FILE_MODE_READ, &handle);

      if (err == EFI_SUCCESS)
	{
	EFI_FILE_INFO *info = LibFileInfo (handle);
	if (info->Attribute & EFI_FILE_DIRECTORY)
	  {
	  ret = malloc (sizeof (DIR));
	  ret->dir_handle = handle; 
	  }
	else 
	  {
	  efi_files_close_file (handle);
	  errno = ENOTDIR;
	  }
	free (info);
	}
      else
	errno = efi_util_status_to_errno (err);

      free (epath);
      }
    else
      ret = NULL;
    }
  path_destroy (p);
  return ret;
  }

/*============================================================================

  opendir

============================================================================*/
struct dirent *readdir (DIR *dirp)
  {
  struct dirent *ret = NULL;
  UINT64 read_size = 1000; // TODO
  char buff[read_size];

  EFI_FILE_HANDLE handle = dirp->dir_handle;
  EFI_STATUS err = uefi_call_wrapper (handle->Read, 3, handle, &read_size, buff);
  if (err == EFI_SUCCESS && read_size > 0)
    {
    EFI_FILE_INFO *entry = (EFI_FILE_INFO *)&buff;
    UTF8 *nicepath = path_from_efi (entry->FileName);    
    strcpy (dirp->entry.d_name, nicepath);
    free (nicepath);
    ret = &dirp->entry;
    }

  return ret;
  }

#endif 

