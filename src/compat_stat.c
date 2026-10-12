/*============================================================================

  compat_stat.c

  Implementation of the stat() function, which is just a wrapper around 
  a bunch of EFI API calls.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>
#include "defs.h"
#include "compat_stat.h"
#include "compat_time.h"
#include "compat_malloc.h"
#include "compat_stdio.h"
#include "context.h"
#include "efiutil.h"
#include "efifiles.h"
#include "filesystems.h"
#include "path.h"

int stat (const char *pathname, struct stat *statbuff)
  {
  int ret = 0;

  Path *p = path_new (pathname); 
  path_canonicalize (p);

  CHAR16 *efi_path;

  EFI_FILE_INFO *info;

  EFI_FILE_HANDLE root = filesystems_get_root_from_path 
      (path_cstr (p), &efi_path);
  if (root)
    {
    EFI_STATUS eret = efi_files_get_info (root, efi_path, &info);
    if (eret == EFI_SUCCESS)
       {
       if (info->Attribute & EFI_FILE_DIRECTORY)
	  statbuff->st_mode = S_IFDIR;
       else
	  statbuff->st_mode = S_IFREG;
       statbuff->st_size = info->FileSize;

       if (info->Attribute & EFI_FILE_READ_ONLY)
	 statbuff->st_mode |= (S_IRUSR | S_IXUSR);
       else
	 statbuff->st_mode |= (S_IRUSR | S_IXUSR | S_IWUSR);

       statbuff->st_mtime = efi_util_time_to_epoch (&info->ModificationTime);

       FreePool (info);
       }
    else
       {
       errno = efi_util_status_to_errno (eret);
       ret = -1;
       }

    free (efi_path);
    }
  else
    ret = -1;
  path_destroy (p);

  return ret;
  }

#endif
