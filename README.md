# ok-c kernel

A basic x86 kernel written in C with a multiboot2 header.
Create a bootable iso with GRUB2 as bootloader.

Offical repository here : https://gitlab.com/oxynux/ok-c-kernel/ (the GitHub one is a mirror).

## Requirements

Recent GNU/Linux distribution should work with:
```
cmake >= 3.10
qemu
qemu-system-i386
gcc
build-essential
nasm
xorriso
grub-common
```

## Compile

```
cmake .
make
```

## Launch

```
make run
```
or
```
qemu-system-i386  -enable-kvm -cdrom oxynux.iso -serial file:serial.log
```

If you can't ou don't want to use KVM with QEMU:

```
qemu-system-i386 -cdrom oxynux.iso -serial file:serial.log
```
