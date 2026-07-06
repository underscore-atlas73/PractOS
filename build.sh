COMPILER_FLAGS="-ffreestanding -Wall -Wextra"
LINKER_FLAGS="-nostdlib"

cd source/

#set -x
x86_64-elf-gcc -c -x assembler $(find . -path "./include" -prune -o -iname "*.asm" -print) -Iinclude/
x86_64-elf-gcc $COMPILER_FLAGS -c $(find . -path "./include" -prune -o -iname "*.c" -print) -Iinclude/
x86_64-elf-ld $LINKER_FLAGS -T linker.ld $(find . -name "*.o") -o kernel.elf