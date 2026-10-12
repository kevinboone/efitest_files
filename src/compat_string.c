/*============================================================================

  string.c

  General string handling functions.

  Copyright (c)2026 Kevin Boone, GPLv3.0

============================================================================*/

#include "compat_errno.h" 
#include "compat_string.h" 
#include "compat_malloc.h" 

/*============================================================================

  strcmp

============================================================================*/
int strcmp (const char *p1, const char *p2)
  {
  register const unsigned char *s1 = (const unsigned char *) p1;
  register const unsigned char *s2 = (const unsigned char *) p2;
  unsigned register char c1, c2;

  do
    {
    c1 = (unsigned char) *s1++;
    c2 = (unsigned char) *s2++;
    if (c1 == '\0')
      return c1 - c2;
    } while (c1 == c2);

  return c1 - c2;
  }

/*============================================================================

  strcpy

============================================================================*/
char *strcpy (char *dst, const char *src)
  {
  int l = strlen (src);
  for (register int i = 0; i < l; i++)
    {
    *dst = *src;
    src++; dst++;
    }
  *dst = 0;
  return dst;
  }

/*============================================================================

  strdup 

============================================================================*/
char *strdup (const char *s)
  {
  int l = strlen (s);
  char *ret = malloc (l + 1);
  strcpy (ret, s); 
  ret[l] = 0;
  return ret;
  }

/*============================================================================

  strlen

============================================================================*/
long unsigned int strlen (const char *s)
  {
  register int l = 0;
  while (*s)
    {
    l++;
    s++;
    }
  return l;
  }

/*============================================================================

  strerror

============================================================================*/
char *strerror (int errnum)
  {
  switch (errnum)
    {
    case 0: return "OK";
    case ENOTDIR: return "not a directory";
    case ENOEXEC: return "executable missing or in wrong format";
    case EINVAL: return "invalid parameter";
    case ENOENT: return "not found";
    case ENODEV: return "device error";
    case EROFS: return "read only";
    case ENOMEM: return "out of memory or resources";
    case ENOSPC: return "out of space";
    case ENOMEDIUM: return "no medium in drive";
    case EMEDIUMTYPE: return "incorrect medium type, or medium changed";
    case ETIMEDOUT: return "no response within timeout";
    case EPROTO: return "protocol error";
    case EPERM: return "permission denied";
    case EBADF: return "bad file descriptor";
    }  
  return "unknown error";
  }



