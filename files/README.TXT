What is this?
-------------

This EFI program demonstrates simple file handling. It offers a (very)
rudimentary shell, which supports the following commands

cat {files}
Prints text files to the console

cd
Prints the current working directory

cd {dir}
Change directory. `dir` can be absolute (starting with `/`) or
relative to the current working directory

clear
Clear the console

df
Show used and free space on each volume known to EFI

ls {dirs}
List files in the specified directories. If no directory, lists the current
directory

mount
Shows storage volumes known to EFI, and their mount points 

reboot
Reboots the system

rm {files}
Deletes files

Notes
-----

- The directory separator is a forward slash (/)
- EFI probably only recognizes as storage volumes partitions of hard disks
  in VFAT format. One of these will be the device you booted from, which
  might be a removable device such as a flash drive. 
- All paths start with "/N", where N is a single digit that represents the
  storage device number. "/" alone is _not_ a directory here. 
- Device numbers are arbitrary. That's no guarantee the `/0' is the
  root of the device you booted from
- You can change volumes using `cd /N`, but but you can use the full path 
  of any file or directory if you prefer.
- File and directory names are case-insensitive


