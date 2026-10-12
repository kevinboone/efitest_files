/*============================================================================

  cmd_reboot.c

  Implementation of reboot command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#ifdef LINUX
#else
#include <efi/efi.h>
#include <efi/efilib.h>
#endif
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "cmds.h" 
#include "console.h" 
#include "context.h" 
#include "string8.h" 

/*============================================================================

  cmd_reboot

============================================================================*/
int cmd_reboot (const List *args)
  {
  #ifdef LINUX
  myprintf ("The command is only available on an EFI platform\n");
  #else
  RT->ResetSystem (EfiResetCold, 0, 0, NULL);
  #endif
  return 0;
  }




