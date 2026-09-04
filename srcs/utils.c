#include "../includes/chip8.h"

bool    setup_chip8(chip8_t *chip8, const char *path) {
    int     fd = open(path, O_RDONLY);
    ssize_t bytes_read;
    struct  stat file_info;

    memset(chip8, 0, sizeof(*chip8));

    if (fd == -1) {
        fprintf(stderr, "failed to open file : %s\n", path);
        return (false);
    }

    if (fstat(fd, &file_info) == -1) {
        close(fd);
        fprintf(stderr, "failed to stat rom : %s\n", path);
        return (false);
    }

    if (file_info.st_size > MEMORY_SIZE - ROM_START) {
        fprintf(stderr, "ROM too large: %ld bytes\n", file_info.st_size);
        close(fd);
        return false;
    }

    bytes_read = read(fd, chip8->memory + ROM_START, file_info.st_size);
    if (bytes_read != file_info.st_size) {
        fprintf(stderr, "failed to read complete ROM\n");
        close(fd);
        return false;
    }

    if (close(fd) == -1) {
        fprintf(stderr, "failed to close file : %s\n", path);
        return (false);
    }
    chip8->program_counter = ROM_START;
    memset(chip8->screen, 0, sizeof(chip8->screen));

    uint8_t font[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0; i < 80; i++) {
        chip8->memory[0x50 + i] = font[i];
    }
    return (true);
}

nibble decode(uint16_t opcode) {
    nibble data = {
        .opcode = opcode,
        .t = opcode >> 12,
        .x = opcode >> 8 & 0xF,
        .y = opcode >> 4 & 0xF,
        .n = opcode & 0xF,
        .nn = opcode & 0xFF,
        .nnn = opcode & 0xFFF,
    };
    return (data);
}
