/*============================================================================

  efiutil.h

  EFI stuff that doesn't fit anywhere else.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>
#include "compat_time.h"

/** Convert an EFI_STATUS value into a Linux-like errno, for compatibility
    with Linux code. */
extern int efi_util_status_to_errno (EFI_STATUS status);

/** Convert an EFI_TIME structure (which has a similar function to
    POSIX "struct tm" into a time_t. */
extern time_t efi_util_time_to_epoch (const EFI_TIME *efitime);

#endif
