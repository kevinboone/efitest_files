/*============================================================================

  filesystems.h

  Keeps track of EFI storage volumes. A list of EfiVolume structures gets
  populated a boot time, and then used in all subsequent file operations. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>

typedef struct _EfiVolume
  {
  // The EFI handle of the storage storage device
  EFI_HANDLE handle;
  // The EFI device path, which is a very long, unhelpful string
  UTF8 *device_path;
  // A pointed to the SFP structure that provides the file management
  //   functions for this volume. It may, or may not, be the same for
  //   all VFAT volumes -- this is implementation-dependent
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *sfp;
  // A handle to the root directory of the volume, which we'll need
  //   when we open or query a file in the volume
  EFI_FILE_HANDLE root;
  // Volume label. May be an empty string if there is none.
  UTF8 *label;
  } EfiVolume;
#endif

/** Initalize the volume table at boot time. */
extern void filesystems_init (void);

#ifndef LINUX
/** Returns the number of EFI volumes found at boot time. */
extern int filesystems_get_num_efi_volumes (void);

/** Returns an EfiVolume structure corresponding to the 
    supplied number (starts at zero). This function can
    fail; if it does, it returns NULL. */
extern const EfiVolume *filesystems_get_efi_volume (int n);

/* Returns the EFI handle of the volume that contains the specified path.
   path MUST be a canonical, absolute path. The function returns, in EFI
   format, a newly-allocated string containing the path that should be
   passed to EFI, that is, minus that part of the path that identifies
   the volume. The caller should free this string. 

   This function can fail, in which case it returns zero, and errno is
   set. In such a case, the caller should not free the returned path,
   which will be invalid.
*/
extern EFI_FILE_HANDLE filesystems_get_root_from_path (const UTF8 *path,
  CHAR16 **epath);
#endif
