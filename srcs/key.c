#include "../includes/chip8.h"

uint8_t    handle_key_down(SDL_KeyboardEvent key, chip8_t *chip8) {
    switch (key.key)
    {
        case SDLK_1: chip8->pressed_keys[0x1] = true; return 0x1;
        case SDLK_2: chip8->pressed_keys[0x2] = true; return 0x2;
        case SDLK_3: chip8->pressed_keys[0x3] = true; return 0x3;
        case SDLK_4: chip8->pressed_keys[0xC] = true; return 0xC;
        case SDLK_Q: chip8->pressed_keys[0x4] = true; return 0x4;
        case SDLK_W: chip8->pressed_keys[0x5] = true; return 0x5;
        case SDLK_E: chip8->pressed_keys[0x6] = true; return 0x6;
        case SDLK_R: chip8->pressed_keys[0xD] = true; return 0xD;
        case SDLK_A: chip8->pressed_keys[0x7] = true; return 0x7;
        case SDLK_S: chip8->pressed_keys[0x8] = true; return 0x8;
        case SDLK_D: chip8->pressed_keys[0x9] = true; return 0x9;
        case SDLK_F: chip8->pressed_keys[0xE] = true; return 0xE;
        case SDLK_Z: chip8->pressed_keys[0xA] = true; return 0xA;
        case SDLK_X: chip8->pressed_keys[0x0] = true; return 0x0;
        case SDLK_C: chip8->pressed_keys[0xB] = true; return 0xB;
        case SDLK_V: chip8->pressed_keys[0xF] = true; return 0xF;
    }
    return (NO_KEY);
}

void    handle_key_up(SDL_KeyboardEvent key, chip8_t *chip8) {
    switch (key.key)
    {
        case SDLK_1: chip8->pressed_keys[0x1] = false; break;
        case SDLK_2: chip8->pressed_keys[0x2] = false; break;
        case SDLK_3: chip8->pressed_keys[0x3] = false; break;
        case SDLK_4: chip8->pressed_keys[0xC] = false; break;
        case SDLK_Q: chip8->pressed_keys[0x4] = false; break;
        case SDLK_W: chip8->pressed_keys[0x5] = false; break;
        case SDLK_E: chip8->pressed_keys[0x6] = false; break;
        case SDLK_R: chip8->pressed_keys[0xD] = false; break;
        case SDLK_A: chip8->pressed_keys[0x7] = false; break;
        case SDLK_S: chip8->pressed_keys[0x8] = false; break;
        case SDLK_D: chip8->pressed_keys[0x9] = false; break;
        case SDLK_F: chip8->pressed_keys[0xE] = false; break;
        case SDLK_Z: chip8->pressed_keys[0xA] = false; break;
        case SDLK_X: chip8->pressed_keys[0x0] = false; break;
        case SDLK_C: chip8->pressed_keys[0xB] = false; break;
        case SDLK_V: chip8->pressed_keys[0xF] = false; break;
    }
}