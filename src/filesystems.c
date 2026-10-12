/*============================================================================

  filesystems.c

  Keeps track of EFI storage volumes. See filesystems.h for more
  information. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h"
#include "compat_stdio.h"
#ifdef LINUX
#else
#include <efi/efi.h>
#include <efi/efilib.h>
#include "compat_errno.h"
#include "compat_limits.h"
#include "compat_string.h"
#include "context.h"
#include "filesystems.h"
#include "path.h"
#endif

#ifndef LINUX

// EfiVolumes -- list of EFI volumes know at boot time.

// So long as we only read this stuff at boot, we don't need to worry about
//  _any_ clean-up associated with this structure.

static EfiVolume efi_volumes[NVOL_MAX];
static int efi_volume_count = 0;
#endif

/*============================================================================

  filesystems_get_efi_volume

============================================================================*/
#ifndef LINUX
const EfiVolume *filesystems_get_efi_volume (int n)
  {
  if (n < 0 || n >= efi_volume_count)
    {
    errno = EINVAL;
    return NULL;
    }
  return &efi_volumes[n];
  }
#endif

/*============================================================================

  filesystems_get_num_efi_volumes

============================================================================*/
#ifndef LINUX
extern int filesystems_get_num_efi_volumes (void)
  {
  return efi_volume_count;
  }
#endif

/*============================================================================

  filesystems_get_root_from_path

============================================================================*/
#ifndef LINUX
EFI_FILE_HANDLE filesystems_get_root_from_path (const UTF8 *path, 
    CHAR16 **efi_path)
  {
  // TODO TODO TODO
  if (strlen (path) < 2) 
    {
    errno = ENOENT;
    return 0;
    }

  char mount_letter = path[1];
  if (mount_letter >= '0' && mount_letter <= '9')
    {
    int vol = mount_letter - '0';
    if (vol >= efi_volume_count)
      {
      errno = ENOENT;
      return 0;
      }
    else
      {
      if (path[2] == 0)
	*efi_path = path_to_efi ("/");
      else
	*efi_path = path_to_efi (path + 2);
      return efi_volumes[vol].root;
      }
    }
  else
    {
    errno = ENOENT;
    return 0;
    }
  }
#endif 

/*============================================================================

  filesystems_init

============================================================================*/
void filesystems_init (void)
  {
#ifndef LINUX

  UINTN handle_count = 0;
  EFI_HANDLE *handles = NULL;
  // Get handles for all the devices that support SimpleFileSystemProtocol
  int ret = uefi_call_wrapper (BS->LocateHandleBuffer, 5, ByProtocol, 
    &gEfiSimpleFileSystemProtocolGuid, 
    NULL, &handle_count, &handles);
  if (ret == EFI_SUCCESS)
    {
    for (int i = 0; i < handle_count; i++)
      {
      efi_volumes[efi_volume_count].handle = handles[i];
      EFI_DEVICE_PATH *dp = DevicePathFromHandle (handles[i]);
      if (dp)
	{
	CHAR16 *efi_device_path = DevicePathToStr (dp);
	if (efi_device_path) 
	  efi_volumes[efi_volume_count].device_path = path_from_efi (efi_device_path);
	else
	  efi_volumes[efi_volume_count].device_path[0] = 0;
	}

      EFI_GUID sfp_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *sfp;
      // This call shouldn't error, because we specifically asked for 
      //   handles that had an SFP
      uefi_call_wrapper (BS->HandleProtocol, 3,
	  handles[i], &sfp_guid, (void **) &sfp);

      // Likewise, there shouldn't be a volume with no root
      EFI_FILE_HANDLE root;
      uefi_call_wrapper (sfp->OpenVolume, 2, sfp, &root);
      efi_volumes[efi_volume_count].root = root;

      EFI_FILE_SYSTEM_INFO *f = LibFileSystemInfo (root);
      efi_volumes[efi_volume_count].label = path_from_efi (f->VolumeLabel);
      FreePool (f);

      efi_volume_count++;
      }
    }

#endif
  }
