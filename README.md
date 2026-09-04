# ft_chip8

A simple CHIP-8 emulator written in C using SDL3.

## Description
CHIP-8 is a simple interpreted programming language and virtual machine originally designed in the 1970s for developing small games. It features a simple architecture with 4 KB of memory, 16 registers, a 64×32 monochrome display, and a 16-key hexadecimal keyboard.

This project implements a CHIP-8 emulator in C using SDL3, allowing CHIP-8 ROMs to be loaded and executed.

23 (public domain) ROMs are included in the roms directory.

## Requirements
- C compiler (cc)
- make
- SDL3


## Compilation
- `make` or `make all` : Compile the program
- `make clean` : Remove all object files (.o)
- `make fclean` : Execute clean + remove the executable
- `make re` : Execute fclean + all (full recompilation)
- `make bonus` : Compile the checker program

## Usage
Run the emulator with a CHIP-8 ROM:
```bash
./ft_chip8 <rom>
```
Example:
```bash
./ft_chip8 pong.ch8
```

## Author

psykokwak13 — CHIP-8 emulator