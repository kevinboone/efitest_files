/*============================================================================

  cmd_mount.c

  Implementation of mount command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "cmds.h" 
#include "filesystems.h" 

/*============================================================================

  cmd_mount

============================================================================*/
int cmd_mount (const List *args)
  {
  #ifdef LINUX
  myprintf ("The command is only available on an EFI platform\n");
  #else

  int nvols = filesystems_get_num_efi_volumes();
  for (int i = 0; i < nvols; i++)
    {
    const EfiVolume *vol = filesystems_get_efi_volume (i);
    myprintf ("/%d \"%s\" %s\n", i,
      vol->label,
      vol->device_path);
    }

  #endif
  return 0;
  }



