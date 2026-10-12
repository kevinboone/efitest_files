/*============================================================================

  cmd.c

  Command table, and functions for searching it.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "compat_stdio.h" 
#include "compat_string.h" 
#include "defs.h" 
#include "cmds.h" 

struct _Cmd
  {
  const char *name;
  const char *usage;
  CmdFn fn;
  };

typedef struct _Cmd Cmd;

static Cmd cmdTable[] =
  {
  {"cat", "print files to the console", cmd_cat},
  {"cd", "change current directory", cmd_cd},
  {"clear", "clear console", cmd_clear},
  {"df", "show storage capacity and usage", cmd_df},
  {"help", "print command summary", cmd_help},
  {"ls", "list directory", cmd_ls},
  {"reboot", "reboot the computer", cmd_reboot},
  {"rm", "delete files", cmd_rm},
  {"mount", "list mounted volumes", cmd_mount},
  {NULL, NULL, NULL},
  };

/*============================================================================

  cmd_dump_cmds

============================================================================*/
void cmd_dump_cmds (void)
  {
  int i = 0;
  while (cmdTable[i].name)
    {
    myprintf ("\"%s\": %s\n", cmdTable[i].name, cmdTable[i].usage); 
    i++;
    }
  }

/*============================================================================

  cmd_find_in_table 

============================================================================*/
CmdFn cmd_find_in_table (const char *name)
  {
  int i = 0;
  while (cmdTable[i].name)
    {
    if (strcmp (cmdTable[i].name, name) == 0) return cmdTable[i].fn;
    i++;
    }
  return NULL;
  }

