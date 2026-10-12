/*============================================================================

  cmd_rm.c

  Implementation of rm command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_fcntl.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "compat_unistd.h" 
#include "cmds.h" 
#include "context.h" 
#include "path.h" 
#include "string8.h" 

/*============================================================================

  cmd_rm_path

============================================================================*/
static int cmd_rm_path (const char *path)
  {
  Path *p = path_new (path); 
  path_canonicalize (p);

  UTF8 *cp = path_cstr (p); 
  if (unlink (cp) != 0)
    myprintf ("%s: can't delete: %s\n", cp, strerror (errno));

  path_destroy (p);
  return 0;
  }

/*============================================================================

  cmd_rm

============================================================================*/
int cmd_rm (const List *args)
  {
  int argc = list_length (args);
  for (int i = 1; i < argc; i++)
    {
    const char *path = string8_cstr (list_get (args, i));
    cmd_rm_path (path);
    }
  return 0;
  }




