/*============================================================================

  cmd_cat.c

  Implementation of cat command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_fcntl.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "compat_unistd.h" 
#include "compat_errno.h" 
#include "cmds.h" 
#include "context.h" 
#include "path.h" 
#include "string8.h" 

/*============================================================================

  cmd_cat_path

============================================================================*/
static int cmd_cat_path (const char *path)
  {
  Path *p = path_new (path); 
  path_canonicalize (p);
  if (path_is_file (p))
    {
    int f = open (path_cstr (p), O_RDONLY);
    if (f >= 0)
      {
      char buff[513];
      int n = read (f, buff, sizeof (buff));
      while (n > 0)
	{
	buff[n] = 0;
	myprintf ("%s", buff);
	n = read (f, buff, sizeof (buff));
	}

      close (f);
      }
    else
      {
      myprintf ("%s: can't open for reading: %s\n", path, strerror (errno));
      }
    path_destroy (p);
    return 0;
    }
  else
    {
    myprintf ("%s: not a regular file\n", path); 
    return EISDIR;
    }
  }

/*============================================================================

  cmd_cat

============================================================================*/
int cmd_cat (const List *args)
  {
  int argc = list_length (args);
  for (int i = 1; i < argc; i++)
    {
    const char *path = string8_cstr (list_get (args, i));
    cmd_cat_path (path);
    }
  return 0;
  }



