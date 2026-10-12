/*============================================================================

  cmd_cd.c

  Implementation of cd command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "cmds.h" 
#include "context.h" 
#include "string8.h" 

/*============================================================================

  cmd_cd

============================================================================*/
int cmd_cd (const List *args)
  {
  int argc = list_length (args);
  if (argc > 1)
    {
    String8 *arg = list_get (args, 1);
    char *newdir = string8_cstr (arg);
    if (context_cd (newdir) != 0)
      {
      myprintf ("%s: %s\n", newdir, strerror (errno));
      return errno; 
      }
    }
  else
    {
    myprintf ("%s\n", context_get_cwd());
    }
  return 0;
  }


