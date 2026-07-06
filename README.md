# PractOS

A practice operating system (for now).


## Roadmap

- [x] Cross-Compiler Setup
- [x] x86_32 to x86_64 Bootstrapper
- [ ] Legacy VGA text-mode Display Driver
- [ ] Legacy PS/2 Keyboard Driver
- [ ] Dynamic Memory Allocation (Heap)
- TODO

## Planned Features
 
- Processes
- Syscalls (custom calling convention)
- Basic ACPI Parsing
- PCI Parsing
- AHCI Driver
- FAT32 driver
- Transition from Legacy VGA Text-Mode to linear framebuffer
- Optional Ring 3/Userspace Processes (By default, all threads will be in kernelspace)

- Custom ABI
- Custom Executable/Linkable Format
- USB/3.2 Driver (xHCI)
- PCIe Parsing

- POSIX emulation
- Linux subsystem
- GPU Driver porting
