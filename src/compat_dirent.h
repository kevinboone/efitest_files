/*============================================================================

  compat_dirent.h

  Implementations of opendir(), readdir(), and closedir() for the 
  EFI environment. The implementations essentially wrap EFI 
  functionality in efifiles.c.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#pragma once

#ifdef LINUX
#include <dirent.h>
#else

#include <efi/efi.h>
#include <efi/efilib.h>

/** Our struct dirent is much simpler than the Linux one, as most of the
   information in the Linux version is irrelevant in an EFI system. */
struct dirent 
  {
  char d_name[256]; // Filename
  }; 

/** Struct DIR is returned by opendir(). It contains the EFI file handle,
    and also a static struct dirent. readdir() populates this dirent
    structure, and returns a pointer to it to the caller. */
typedef struct _DIR
  {
  EFI_FILE_HANDLE dir_handle;
  struct dirent entry;
  } DIR;

// Prototypes as in Linux
extern int closedir (DIR *dirp);
extern DIR *opendir (const char *path);
extern struct dirent *readdir (DIR *dirp);

#endif


