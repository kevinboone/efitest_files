/*============================================================================

  cmd_ls.c

  Implementation of ls command 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "defs.h" 
#include "compat_dirent.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "compat_stat.h" 
#include "compat_time.h" 
#include "cmds.h" 
#include "context.h" 
#include "string8.h" 
#include "path.h" 

static char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/*============================================================================

  cmd_ls_path

============================================================================*/
int cmd_ls_path (const char *path)
  {
  int ret = 0;

  DIR *p = opendir (path);
  if (p)
    {
    struct dirent *dirp = readdir (p);
    while (dirp)
      {
      Path *newpath = path_new (path); 
      path_append (newpath, dirp->d_name);
      path_canonicalize (newpath);
      struct stat sb;
      if (path_stat (newpath, &sb) == 0)
        {
        if ((sb.st_mode & S_IFMT) == S_IFDIR)
          myprintf ("d");
        else
          myprintf ("-");

        if (sb.st_mode & S_IRUSR)
          myprintf ("r");
        else
          myprintf ("-");

        if (sb.st_mode & S_IWUSR)
          myprintf ("w");
        else
          myprintf ("-");

        if (sb.st_mode & S_IXUSR)
          myprintf ("x");
        else
          myprintf ("-");

        myprintf (" %8d ", sb.st_size);

        struct tm *tm = gmtime (&sb.st_mtime);
        myprintf (" %s %02d %04d %02d:%02d ", months[tm->tm_mon], tm->tm_mday, 
          tm->tm_year + 1900, tm->tm_hour, tm->tm_min);
        }

      myprintf ("%s\n", dirp->d_name);
      path_destroy (newpath);
      dirp = readdir (p);
      }
    closedir (p);
    }
  else
    {
    myprintf ("%s: %s%s", path, strerror (errno), "\n");
    ret = -1;
    }

  return ret;
  }

/*============================================================================

  cmd_ls

============================================================================*/
int cmd_ls (const List *args)
  {
  int argc = list_length (args);
  if (argc == 1)
    {
    cmd_ls_path (context_get_cwd());
    }
  else if (argc == 2)
    {
    const char *path = string8_cstr (list_get (args, 1));
    cmd_ls_path (path);
    }
  else
    {
    for (int i = 1; i < argc; i++)
      {
      const char *path = string8_cstr (list_get (args, i));
      myprintf ("%s:%s", path, "\n");
      cmd_ls_path (path);
      }
    }
  return 0;
  }



