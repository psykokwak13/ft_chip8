#include "../includes/chip8.h"

bool    execute_nibble(nibble code, chip8_t *chip8) {
    printf( "opcode : %#X\n", code.opcode);
    switch (code.t) {
        case 0x0:
            if (code.nn == 0xE0) {
                memset(chip8->screen, 0, sizeof(chip8->screen));
                chip8->draw_flag = true;
            }
            else if (code.nn == 0xEE) {
                if (chip8->stack_counter == 0) {
                    fprintf(stderr, "stack underflow\n");
                    return false;
                }
                chip8->program_counter = chip8->stack[--chip8->stack_counter];
            }
            else {
                fprintf(stderr, "unknown 0xxx opcode: %#06X\n", code.opcode);
                return false;
            }
            break;
        case (0x1) :
            chip8->program_counter = code.nnn;
            break ;
        case (0x2) :
            if (chip8->stack_counter >= 16) {
                fprintf(stderr, "stack overflow\n");
                return false;
            }
            chip8->stack[chip8->stack_counter++] = chip8->program_counter;
            chip8->program_counter = code.nnn;
            break ;
        case (0x3) :
            if (chip8->V[code.x] == code.nn) { chip8->program_counter += 2; };
            break ;
        case (0x4) :
            if (chip8->V[code.x] != code.nn) { chip8->program_counter += 2; };
            break ;
        case (0x5) :
            if (chip8->V[code.x] == chip8->V[code.y]) { chip8->program_counter += 2; };
            break ;
        case (0x6) :
            chip8->V[code.x] = code.nn;
            break ;
        case (0x7) : ;
            chip8->V[code.x] += code.nn;
            break ;
        case (0x8) :
            switch (code.n) {
                case (0x0) :
                    chip8->V[code.x] = chip8->V[code.y];
                    break ;
                case (0x1) :
                    chip8->V[code.x] |= chip8->V[code.y];
                    break ;
                case (0x2) :
                    chip8->V[code.x] &= chip8->V[code.y];
                    break ;
                case (0x3) :
                    chip8->V[code.x] ^= chip8->V[code.y];
                    break ;
                case (0x4) : 
                    chip8->V[0xF] = chip8->V[code.x] + chip8->V[code.y] > 255 ? 1 : 0;
                    chip8->V[code.x] += chip8->V[code.y];
                    break ;
                case (0x5) :
                    chip8->V[0xF] = chip8->V[code.x] >= chip8->V[code.y] ? 1 : 0;
                    chip8->V[code.x] -= chip8->V[code.y];
                    break ;
                case (0x6) :
                    chip8->V[0xF] = chip8->V[code.x] & 0x1;
                    chip8->V[code.x] >>= 1;
                    break ;
                case (0x7) :
                    chip8->V[0xF] = chip8->V[code.y] >= chip8->V[code.x] ? 1 : 0;
                    chip8->V[code.x] = chip8->V[code.y] - chip8->V[code.x];
                    break ;
                case (0xE) :
                    chip8->V[0xF] = (chip8->V[code.x] & 0x80) >> 7;
                    chip8->V[code.x] <<= 1; 
                    break ;
            };
            break;
        case (0x9) :
            if (chip8->V[code.x] != chip8->V[code.y]) { chip8->program_counter += 2; };
            break ;
        case (0xA) :
            chip8->index_register = code.nnn;
            break ;
        case (0xB) :
            chip8->program_counter = code.nnn + chip8->V[0];
            break ;
        case (0xC) :
            chip8->V[code.x] = (uint8_t)rand() & code.nn;
            break ;
        case (0xD) :
            draw(chip8, code);
            break ;
        case (0xE) :
            if (code.nn == 0x9E) {
                if (chip8->pressed_keys[chip8->V[code.x]])
                    chip8->program_counter += 2;
            }
            else if (code.nn == 0xA1) {
                if (!chip8->pressed_keys[chip8->V[code.x]])
                    chip8->program_counter += 2;
            }
            break ;
        case (0xF) :
            switch (code.nn) {
                case (0x07) :
                    chip8->V[code.x] = chip8->delay;
                    break ;
                case (0x0A) :
                    chip8->key_event = true;
                    chip8->waiting_key_register = code.x;
                    break ;
                case (0x15) :
                     chip8->delay = chip8->V[code.x];
                    break ;
                case (0x18) :
                    chip8->sound = chip8->V[code.x];
                    break ;
                case (0x1E) :
                    chip8->index_register += chip8->V[code.x];
                    break ;
                case (0x29) :
                    chip8->index_register = 0x50 + chip8->V[code.x] * 5;
                    break ;
                case (0x33) : {
                    uint8_t nbr = chip8->V[code.x];
                    chip8->memory[chip8->index_register] = nbr / 100;
                    chip8->memory[chip8->index_register + 1] = (nbr / 10) % 10;
                    chip8->memory[chip8->index_register + 2] = nbr % 10;
                    break ;
                }
                case (0x55) :
                    for (uint8_t i = 0; i <= code.x; i++)
                        chip8->memory[chip8->index_register + i] = chip8->V[i];
                    break ;
                case (0x65) :
                    for (uint8_t i = 0; i <= code.x; i++)
                         chip8->V[i] = chip8->memory[chip8->index_register + i];
                    break ;
            }
            break;
        default :
            fprintf(stderr, "opcode not found ! : %#X", code.opcode);
            return (false);
    }

    return (true);
}
