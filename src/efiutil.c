/*============================================================================

  efiutil.c

  EFI stuff that doesn't fit anywhere else.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#ifndef LINUX

#include <efi/efi.h>
#include <efi/efilib.h>
#include "compat_time.h" 
#include "compat_errno.h" 

#define TM_YEAR_BASE 1900

static int get_yday (int mon, int day, int year);
static long shr (long a, int b);
static long ydhms_diff (long year1, long yday1, int hour1, int min1, int sec1,
	    int year0, int yday0, int hour0, int min0, int sec0);
static int yisleap (int year);

/*============================================================================

  efi_util_status_to_errno

============================================================================*/
int efi_util_status_to_errno (EFI_STATUS status)
  {
  if (status == EFI_SUCCESS) return 0;
  if (status == EFI_INVALID_PARAMETER) return EINVAL;
  if (status == EFI_LOAD_ERROR) return EINVAL;
  if (status == EFI_LOAD_ERROR) return ENOEXEC;
  if (status == EFI_UNSUPPORTED) return EINVAL;
  if (status == EFI_BAD_BUFFER_SIZE) return EINVAL;
  if (status == EFI_DEVICE_ERROR) return ENODEV;
  if (status == EFI_WRITE_PROTECTED) return EROFS;
  if (status == EFI_OUT_OF_RESOURCES) return ENOMEM;
  if (status == EFI_VOLUME_FULL) return ENOSPC;
  if (status == EFI_NO_MEDIA) return ENOMEDIUM;
  if (status == EFI_MEDIA_CHANGED) return EMEDIUMTYPE;
  if (status == EFI_NOT_FOUND) return ENOENT;
  if (status == EFI_ACCESS_DENIED) return EPERM;
  if (status == EFI_NO_RESPONSE) return ETIMEDOUT;
  if (status == EFI_ICMP_ERROR) return EPROTO;
  if (status == EFI_TFTP_ERROR) return EPROTO;
  if (status == EFI_PROTOCOL_ERROR) return EPROTO;
  if (status == EFI_SECURITY_VIOLATION) return EPERM;
  return -1; 
  }

/*============================================================================

  efi_util_time_to_epoch

============================================================================*/
time_t efi_util_time_to_epoch (const EFI_TIME *efitime)
  {
  // TODO correct for TZ and DST
  int yday = get_yday (efitime->Month, efitime->Day, efitime->Year);

  long e = ydhms_diff (efitime->Year, yday, efitime->Hour, efitime->Minute, 
          efitime->Second, 1970, 1, 0, 0, 0);

  return e; 
  }


/*============================================================================

  get_yday 

============================================================================*/
int get_yday (int mon, int day, int year)
  {
  static const int days[2][13] = 
     {
     {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
     {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
     };

  int leap = yisleap (year);
  return days[leap][mon] + day;
  }

/*============================================================================

  shr 

============================================================================*/
static long shr (long a, int b)
  {
  long one = 1;
  return (-one >> 1 == -1
	  ? a >> b
	  : (a + (a < 0)) / (one << b) - (a < 0));
  }


/*============================================================================

  ydhms_diff 

============================================================================*/
static long ydhms_diff (long year1, long yday1, int hour1, int min1, int sec1,
	    int year0, int yday0, int hour0, int min0, int sec0)
  {
  int a4 = shr (year1, 2) + shr (TM_YEAR_BASE, 2) - ! (year1 & 3);
  int b4 = shr (year0, 2) + shr (TM_YEAR_BASE, 2) - ! (year0 & 3);
  int a100 = (a4 + (a4 < 0)) / 25 - (a4 < 0);
  int b100 = (b4 + (b4 < 0)) / 25 - (b4 < 0);
  int a400 = shr (a100, 2);
  int b400 = shr (b100, 2);
  int intervening_leap_days = (a4 - b4) - (a100 - b100) + (a400 - b400);
  long years = year1 - year0;
  long days = 365 * years + yday1 - yday0 + intervening_leap_days;
  long hours = 24 * days + hour1 - hour0;
  long minutes = 60 * hours + min1 - min0;
  long seconds = 60 * minutes + sec1 - sec0;
  return seconds;
  }

/*============================================================================

  yisleep 

============================================================================*/
static int yisleap (int year)
  {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

#endif



