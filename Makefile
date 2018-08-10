KERNEL = kfs_1
KERNEL_IMG = kfs_1.iso
KERNEL_DIR = kernel

CC = gcc
LD = ld
ASM = nasm

CCFLAGS = -O0 -m32
LDFLAGS = -m elf_i386 -T
ASMFLAGS = -f elf32

CC_SRC =	kmain.c \
		keyboard.c

LD_SRC = link.ld
ASM_SRC = kernel.s
GRUB_CFG = grub.cfg

CC_OBJ = $(CC_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.s=.o)

all: $(KERNEL_IMG) $(CC_SRC) $(LD_SRC) $(ASM_SRC) $(GRUB_CFG) $(KERNEL_DIR)

$(KERNEL_IMG): $(KERNEL)
	mkdir -p $(KERNEL_DIR)/boot/grub
	cp -r $< $(KERNEL_DIR)/boot
	cp -r $(GRUB_CFG) $(KERNEL_DIR)/boot/grub
	grub-mkrescue -o $@ $(KERNEL_DIR)

$(KERNEL): $(ASM_OBJ) $(CC_OBJ)
	$(LD) $(LDFLAGS) $(LD_SRC) -o $@ $^

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

.s.o:
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -rf $(CC_OBJ)
	rm -rf $(ASM_OBJ)

fclean: clean
	rm -rf $(KERNEL_DIR)
	rm -rf $(KERNEL_IMG)
	rm -rf $(KERNEL)

run: $(KERNEL_IMG)
	qemu-system-i386 -cdrom $(KERNEL_IMG)

re: clean all
