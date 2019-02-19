KERNEL = kfs_1
KERNEL_IMG = kfs_1.iso
KERNEL_DIR = kernel
LIBK_DIR = libk
LIBK = $(LIBK_DIR)/libk.a


CC = gcc
LD = ld
ASM = nasm

WFLAGS = # -Wall -Wextra -Werror
INCLUDES = -I . -I $(LIBK_DIR)
CCFLAGS = -O0 -ffreestanding -m32 -nostdlib -fno-stack-protector $(WFLAGS) $(INCLUDES)
LDFLAGS = -m elf_i386 -T
ASMFLAGS = -f elf32

CC_SRC =	kmain.c \
		    keyboard.c

LD_SRC = link.ld
ASM_SRC = kernel.s
GRUB_CFG = grub.cfg

CC_OBJ = $(CC_SRC:.c=.o)

ASM_OBJ = $(ASM_SRC:.s=.o)

all: $(KERNEL_IMG)

$(KERNEL_IMG): $(KERNEL)
	mkdir -p $(KERNEL_DIR)/boot/grub
	cp -r $< $(KERNEL_DIR)/boot
	cp -r $(GRUB_CFG) $(KERNEL_DIR)/boot/grub
	grub-mkrescue -o $@ $(KERNEL_DIR)

$(KERNEL): $(ASM_OBJ) $(CC_OBJ)
	$(MAKE) -C $(LIBK_DIR)/
	$(LD) $(LDFLAGS) $(LD_SRC) -o $@ $^ $(LIBK)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

.s.o:
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -rf $(CC_OBJ)
	rm -rf $(ASM_OBJ)
	$(MAKE) -C $(LIBK_DIR)/ clean

fclean: clean
	rm -rf $(KERNEL_DIR)
	rm -rf $(KERNEL_IMG)
	rm -rf $(KERNEL)
	$(MAKE) -C $(LIBK_DIR)/ fclean

run: $(KERNEL_IMG)
	qemu-system-i386 -cdrom $(KERNEL_IMG)

re: fclean all
