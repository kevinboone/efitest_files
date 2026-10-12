/*============================================================================

  efifiles.c

  File handling using EFI API.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>
#include "efifiles.h" 

/*============================================================================

  efi_files_close_file

============================================================================*/
void efi_files_close_file (EFI_FILE_HANDLE handle)
  {
  uefi_call_wrapper (handle->Close, 1, handle);
  }

/*============================================================================

  efi_files_delete_file

============================================================================*/
extern EFI_STATUS efi_files_delete_file (EFI_FILE_HANDLE root, 
         const CHAR16* path)
  {
  EFI_FILE_HANDLE handle;
  EFI_STATUS ret = efi_files_open_file (root, path, 
    EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ, &handle);
  if (ret == EFI_SUCCESS)
    {
    ret = uefi_call_wrapper (handle->Delete, 1, handle);
    }
  return ret;
  }


/*============================================================================

  efi_files_get_info

============================================================================*/
EFI_STATUS efi_files_get_info (EFI_FILE_HANDLE root, 
    const CHAR16* path, EFI_FILE_INFO **info)
  {
  EFI_FILE_HANDLE handle;
  EFI_STATUS ret = efi_files_open_file (root, path, 
    EFI_FILE_MODE_READ, &handle);
  if (ret == EFI_SUCCESS)
    {
    *info = LibFileInfo (handle);
    efi_files_close_file (handle);
    }
  return ret;
  }


/*============================================================================

  efi_files_open_file

============================================================================*/
EFI_STATUS efi_files_open_file (EFI_FILE_HANDLE root, const CHAR16* path,
         UINT64 mode, EFI_FILE_HANDLE *handle)
  {
  EFI_STATUS ret = uefi_call_wrapper (root->Open, 5, root, handle, path,
      mode, 0);

  return ret;
  }

/*============================================================================

  efi_files_read_file

============================================================================*/
EFI_STATUS efi_files_read_file (EFI_FILE_HANDLE handle, void *buf, 
         uint64_t count, int64_t *nread)
  {
  int64_t n = count;
  EFI_STATUS ret = uefi_call_wrapper (handle->Read, 3, handle, &n, buf);
  *nread = n;
  return ret;
  }


/*============================================================================

  efi_files_write_file

============================================================================*/
EFI_STATUS efi_files_write_file (EFI_FILE_HANDLE handle, void *buf, 
         uint64_t count, int64_t *nwritten)
  {
  int64_t n = count;
  EFI_STATUS ret = uefi_call_wrapper (handle->Write, 3, handle, &n, buf);
  *nwritten = n;
  return ret;
  }


#endif


