/*============================================================================

  main.c

  Main REPL loop.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifdef LINUX
#else
#include <efi/efi.h>
#include <efi/efilib.h>
#endif
#include "defs.h" 
#include "compat_fcntl.h" 
#include "compat_stdio.h" 
#include "compat_string.h" 
#include "compat_unistd.h" 
#include "console.h" 
#include "filesystems.h" 
#include "list.h" 
#include "context.h" 
#include "cmds.h" 
// delete line below
#include "efifiles.h" 
#include "string8.h" 

int main (int argc, char **argv);

/*============================================================================

  efi_main() is the entry point for the UEFI program. It is called by the
  crt.o stub appropriate for this kind of program, which is part of
  gnu-efi

  FWIW efi_main() gets passed a handle to the disk image from which the
  program was loaded, and also a reference to the EFI system table. This
  reference sets up the standard "ST", "BS", etc., API structures that 
  will be used extensively.

============================================================================*/

#ifndef LINUX
EFI_STATUS EFIAPI efi_main (EFI_HANDLE image_handle, 
    EFI_SYSTEM_TABLE *system_table) 
  {
  InitializeLib (image_handle, system_table);

  main (0, NULL);

  // We never get here
  return EFI_SUCCESS;
  }
#endif

/*============================================================================

  main

============================================================================*/
int main (int argc, char **argv)
  {
  context_init();
  console_clear();

  filesystems_init();

  myprintf ("Kevin's dumb EFI shell\n");
  myprintf ("Enter 'help' for a list of commands\n");

  BOOL exit = FALSE;
  while (!exit)
    {
    myprintf ("%s # ", context_get_cwd());

    char line[256];
    // Read a line and echo it back
    if (console_readline (line, sizeof (line)) == 0)
      {
      List *args = string8_tokenize (line); 
      int argc = list_length (args);
      if (argc > 0)
        {
        char *cmd = string8_cstr ((String8 *)list_get (args, 0));
	if (strcmp (cmd, "exit") == 0)
	  { 
  #ifdef LINUX
          exit = TRUE; 
  #endif
          }
	else if (strcmp (cmd, "foo") == 0)
	  {
          // Test file write
          int f = open ("testfile.txt", O_WRONLY | O_CREAT);
          if (f >= 0)
            {
            write (f, "test\n", 5);
            close (f);
            }
          else
            myprintf ("BUGGER! %d %s\n", errno, strerror (errno));
	  }
	else
	  {
          CmdFn fn = cmd_find_in_table (cmd);
          if (fn)
            fn (args);
          else
            myprintf ("%s: command not found\n", cmd);
	  }
        }

      list_destroy (args);
      }
    else
      {
      // Interrupted
      myprintf ("\n");
      }
    }

  }


