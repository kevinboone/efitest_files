/*============================================================================

  efifiles.h 

  File handling using EFI API.

  None of these functions set errno -- success or failure is indicated
  by the values returned. 

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>

/** Close a file that efi_files_open_file() opened. */
extern void efi_files_close_file (EFI_FILE_HANDLE handle);

/** Delete a file from a specified filesystem image. The path is relative
    to the root of that filesystem. */
extern EFI_STATUS efi_files_delete_file (EFI_FILE_HANDLE root, 
         const CHAR16* path);

/** Give a filesystem image, get a FileInfo object for some path,
    which is relative to the root of that filesystem. The caller
    must free the FileInfo structure if this function returns 
    a success code. */
extern EFI_STATUS efi_files_get_info (EFI_FILE_HANDLE root, 
         const CHAR16* path, EFI_FILE_INFO **info);

/** Given the handle of the volume root, open a file in that filesystem. 
    The `path` argument is relative to that root. */
extern EFI_STATUS efi_files_open_file (EFI_FILE_HANDLE root, const CHAR16* path,
        UINT64 mode, EFI_FILE_HANDLE *handle);

/** Read a file that has been opened using efi_files_open_file. 
    At EOF, *nread will be less than count, and may be zero. */
extern EFI_STATUS efi_files_read_file (EFI_FILE_HANDLE handle, void *buf, 
         uint64_t count, int64_t *nread);

/** Write a file that has been opened using efi_files_open_file. */
extern EFI_STATUS efi_files_write_file (EFI_FILE_HANDLE handle, void *buf, 
         uint64_t count, int64_t *nwritten);

#endif

