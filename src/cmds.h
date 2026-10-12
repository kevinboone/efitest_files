/*============================================================================

  cmd.h

  Prototypes for the cmd_xx functions and the command table 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#include "list.h"

// CmdFn is the prototype for all the command-handling functions.
typedef int (*CmdFn) (const List *args);

extern int cmd_cat (const List *args);
extern int cmd_cd (const List *args);
extern int cmd_clear (const List *args);
extern int cmd_df (const List *args);
extern int cmd_help (const List *args);
extern int cmd_ls (const List *args);
extern int cmd_reboot (const List *args);
extern int cmd_rm (const List *args);
extern int cmd_mount (const List *args);

/** Given a command name, find the command's function pointer in the command 
    table. If the name is not found, returns NULL. */
extern CmdFn cmd_find_in_table (const char *name);

/** Print brief descriptions of each command to the console. */
extern void cmd_dump_cmds (void);

