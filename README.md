# Oxynux kernel

## Requirements

Recent GNU/Linux distribution should work with:
```
cmake >= 3.10
qemu
qemu-system-i386
qemu-kvm (if you use KVM)
gcc (gcc-multilib-i686-linux-gnu)
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

Alternative: use CLion

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