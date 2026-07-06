COMPILER_FLAGS="-ffreestanding -Wall -Wextra"
LINKER_FLAGS="-nostdlib"

cd source/
x86_64-elf-as boot.asm -o boot.o
x86_64-elf-gcc -c kernel/kernel.c -o kernel/kernel.o $COMPILER_FLAGS
x86_64-elf-ld $LINKER_FLAGS -T linker.ld boot.o kernel/kernel.o -o kernel.elf