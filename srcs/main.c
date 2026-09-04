#include "../includes/chip8.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "./ft_chip8 <chip8 rom>\n");
        return (1);
    }

    chip8_t chip8;
    gfx_t   gfx;

    if (!setup_chip8(&chip8, argv[1])) return(1);
    if (!setup_gfx(&gfx)) return (1);

    if (!machine_start(&chip8, &gfx)) {
        clean_gfx(&gfx);
        fprintf(stderr, "error\n");
        return (1);
    }

    clean_gfx(&gfx);

    return (0);
}