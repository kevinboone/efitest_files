# efitest_files

v0.1a, October 2026

## What is this? 

`efitest_files` demonstrates how to build and deploy a bare-metal (no operating
system) program on a PC-type computer that supports 64-bit EFI (or UEFI)
booting. Almost any PC-like computer with an Intel or AMD CPU from the last
fifteen years should work. 

In particular, this program demonstrates file and volume handling
using EFI's "Simple File Protocol".

The program itself is a simple comamnd-line shell, which offers commands such
as `ls`, `cd`, `cat`. Although rudimetary, the program demonstrates how to open
a storage volume, open a file, read a file, and close it.  It also demonstrates
EFI features for getting information about files, and also about storage
volumes (including free space).

`efitest_files` is designed to be built on a 64-bit Linux system, with `gnu-efi`
development tools in place (`apt install gnu-efi`). You'll also need
`mtools` for manipulating the DOS-like floppy disk image that will 
host the EFI program. 

To build the bootable CD/USB image, you'll need `xorriso`. `genisoimage` 
and `mkisofs` might work on some systems, but their EFI support seems to be
limited on some Linux distributions.

## Building the boot image

If you have all the prerequisites, `make` should do all the work.  The result
will be a bootable disk image `test.iso`. 

## Building a Linux test harness

`make -f Makefile.linux` should build a program `test`, that contains those
bits of the functionality that can be exercised using Linux. This version
uses Linux file handling, rather than EFI file handling, but it's still
useful for tasks like looking for memory leaks -- something that is painfully
difficult in an EFI enviroment.

## Testing with VirtualBox

Create a VirtualBox machine of type `Other/Unknown (64-bit)`. In the Settings
dialog, under System, check `Enable EFI`, but do not enable Secure Boot. 

Create a virtual DVD drive, using `test.iso` as the image. Boot the virtual
machine. 

## Making a bootable USB stick

Plug in a USB stick, and copy the `test.iso` to the raw disk device -- not to a
partition.  For example:

```
dd if=test.iso of=/dev/sdb
```

Naturally, any other data on the device will be overwritten, so don't
use `sdb` unless you're sure it's appropriate.

## Testing on a real computer

Plug in the USB drive, and configure your computer to boot from it. There's 
probably a keystroke that allows you to select the boot device on the fly
(on my Lenovo laptops it's the F12 key).

You'll need to ensure that Secure Boot is disabled. You might (or might not)
need to re-enable it to boot a real operating system.

## More information

See [my website](https:/kevinboone.me/efitest5.html).


