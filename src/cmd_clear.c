/*============================================================================

  cmd_clear.c

  Implementation of clear command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "cmds.h" 
#include "console.h" 
#include "context.h" 
#include "string8.h" 

/*============================================================================

  cmd_clear

============================================================================*/
int cmd_clear (const List *args)
  {
  console_clear();
  return 0;
  }



