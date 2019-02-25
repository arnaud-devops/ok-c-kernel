#!/bin/sh

# $1 : KERNEL_DIR
# $2 : GRUB_CFG
# $3 : BINARY_PATH
# $4 : ISO_NAME

mkdir -p $1/boot/grub
cp -r $3 $1/boot
cp -r $2 $1/boot/grub
grub-mkrescue -o $4 $1