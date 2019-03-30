cmake_minimum_required(VERSION 3.10)

set(BINARY oxynux)
project(${BINARY})

set(KERNEL_DIR oxynux_kernel)
set(SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/post_build.sh)
set(GRUB_CFG ${CMAKE_CURRENT_SOURCE_DIR}/src/grub.cfg)
set(KERNEL_IMG  oxynux.iso)
set(LD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/linker.ld)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
enable_language(ASM_NASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -O2 -ffreestanding")

set(CMAKE_NASM_LINK_EXECUTABLE "ld -m elf_i386 -T ${LD_PATH} -o <TARGET> <OBJECTS>")

set(SOURCES_FILES
        include/freestanding.h
        include/kernel.h
        include/liboxyk.h
        include/kernel/keyboard.h
        include/kernel/vga.h
        include/kernel/kshell.h
        include/kernel/system.h
        include/kernel/com.h
        include/kernel/gdt.h
        include/kernel/memdump.h 
        src/liboxyk/strncmp.c
        src/liboxyk/memcpy.c
        src/liboxyk/isdigit.c
        src/liboxyk/isascii.c
        src/liboxyk/strlen.c
        src/liboxyk/isprint.c
        src/liboxyk/isalpha.c
        src/liboxyk/memmove.c
        src/liboxyk/islower.c
        src/liboxyk/memset.c
        src/liboxyk/isupper.c
        src/liboxyk/inb.c
        src/liboxyk/isspace.c
        src/liboxyk/isalnum.c
        src/liboxyk/outb.c
        src/vga/kputchar.c
        src/vga/kputstr.c
        src/vga/clear_screen.c
        src/vga/kputnbr.c
        src/vga/vga.c
        src/keyboard/keyboard.c
        src/kmain.c
        src/boot.asm
        src/system/reboot.c
        src/kshell/cmd_parse.c
        src/com/com1.c
        src/vga/cursor.c
        src/gdt/gdt.c
        src/gdt/gdt_flush.asm
        src/vga/scrolling.c
        src/kshell/prompt.c
        src/vga/kdraw.c
        src/memdump/memdump.c
        src/liboxyk/strcpy.c
        src/liboxyk/getsp.c)

include_directories(include)

add_executable(${BINARY} ${SOURCES_FILES})

set_target_properties(${BINARY} PROPERTIES LINKER_LANGUAGE NASM)

add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND sh ${SCRIPT_PATH} ${KERNEL_DIR} ${GRUB_CFG} ${PROJECT_BINARY_DIR}/${BINARY} ${KERNEL_IMG} ${LD_PATH})

set(RUN_COMMAND -enable-kvm -cdrom ${KERNEL_IMG} -serial file:serial.log)

add_custom_target(run COMMAND qemu-system-i386 ${RUN_COMMAND})