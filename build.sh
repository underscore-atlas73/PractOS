cd source/
as boot.asm -o boot.o
ld -T linker.ld boot.o -o kernel.elf