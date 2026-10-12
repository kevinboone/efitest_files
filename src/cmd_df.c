/*============================================================================

  cmd_df.c

  Implementation of df command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "cmds.h" 
#include "filesystems.h" 
#include "textutil.h" 

/*============================================================================

  cmd_df

============================================================================*/
int cmd_df (const List *args)
  {
  #ifdef LINUX
  myprintf ("The command is only available on an EFI platform\n");
  #else

  myprintf ("Mount  Size      Avail  Used   Use%\n");
  int nvols = filesystems_get_num_efi_volumes();
  for (int i = 0; i < nvols; i++)
    {
    const EfiVolume *vol = filesystems_get_efi_volume (i);
    EFI_FILE_SYSTEM_INFO *info = LibFileSystemInfo (vol->root);
    uint64_t volume_size = info->VolumeSize;
    uint64_t free_space = info->FreeSpace;
    uint64_t used_space = volume_size - free_space; 
    char size_buff[10];
    textutil_humanize_size (volume_size, size_buff, sizeof (size_buff));
    char used_buff[10];
    textutil_humanize_size (used_space, used_buff, sizeof (used_buff));
    char free_buff[10];
    textutil_humanize_size (free_space, free_buff, sizeof (free_buff));
    int use_percent = 0; 
    if (volume_size > 0)
      use_percent = 100 * used_space / volume_size;
    myprintf ("/%d     %s %s %s %d%%\n", i, size_buff, used_buff, 
      free_buff, use_percent); 
    FreePool (info);
    }

  #endif
  return 0;
  }




