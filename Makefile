IMG_KERNEL = kfs_1.iso
KERNEL = kfs_1

CC = gcc
LD = ld
ASM = nasm

CCFLAGS = -m32
LDFLAGS = -m elf_i386 -T
ASMFLAGS = -f elf

CC_SRC = kmain.c
LD_SRC = link.ld
ASM_SRC = kernel.s
GRUB_CFG = grub.cfg

CC_OBJ = $(CC_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.s=.o)

all: $(IMG_KERNEL) $(CC_SRC) $(LD_SRC) $(ASM_SRC) $(GRUB_CFG)

$(IMG_KERNEL): $(KERNEL)
	mkdir -p kernel/boot/grub
	cp -r $< kernel/boot
	cp -r $(GRUB_CFG) kernel/boot/grub
	grub-mkrescue -o $@ $<

$(KERNEL): $(CC_OBJ) $(ASM_OBJ)
	$(LD) $(LDFLAGS) $(LD_SRC) -o $@ $<

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

.s.o:
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -rf *.o
	rm -rf kernel

run: $(IMG_KERNEL)
	qemu-system-i386 -cdrom $(IMG_KERNEL)