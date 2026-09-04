#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h> // uint8_t /uint16_t
#include <stdbool.h> // bool data type
#include <fcntl.h> // open() / close()
#include <sys/stat.h>

#include <SDL3/SDL.h>

#define MEMORY_SIZE 4*1024 // memory size of chip8
#define ROM_START 0x200
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCALE 10
#define NO_KEY 0xFF

typedef struct gfx {
    SDL_Window *window;
    SDL_Renderer *renderer;
} gfx_t;

typedef struct nibble {
    uint16_t opcode;
    uint8_t t;
    uint8_t x;
    uint8_t y;
    uint8_t n;
    uint8_t nn;
    uint16_t nnn;
} nibble;

typedef struct chip8 {
    uint8_t     memory[MEMORY_SIZE]; // chip8 only have ram, 0x000 to 0xFFF

    bool        draw_flag;
    bool        key_event;
    uint8_t     waiting_key_register;

    bool        screen[64 * 32];
    bool        pressed_keys[16];
    uint16_t    stack[16]; 

    uint8_t     stack_counter;
    uint16_t    program_counter;
    uint16_t    index_register;
    uint8_t     V[16];

    uint8_t     sound; // used for sound effects
    uint8_t     delay; // used for timing event in game
} chip8_t;

bool    setup_gfx(gfx_t *gfx);
void    clean_gfx(gfx_t *gfx);
bool    setup_chip8(chip8_t *chip8, const char *path);
nibble  decode(uint16_t opcode);
bool    machine_start(chip8_t *chip8, gfx_t *gfx);
void    draw(chip8_t *chip8, nibble code);
void    draw_screen(gfx_t *gfx, bool screen[64 * 32]);
uint8_t    handle_key_down(SDL_KeyboardEvent key, chip8_t *chip8);
void    handle_key_up(SDL_KeyboardEvent key, chip8_t *chip8);
void    update_timers(chip8_t *chip8);
bool    execute_nibble(nibble code, chip8_t *chip8);


#endif