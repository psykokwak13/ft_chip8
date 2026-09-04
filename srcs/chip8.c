#include "../includes/chip8.h"

void update_timers(chip8_t *chip8)
{
    if (chip8->delay > 0)
        chip8->delay--;
    if (chip8->sound > 0)
        chip8->sound--;
}

bool    machine_start(chip8_t *chip8, gfx_t *gfx) {
    nibble      code;
    bool        running = true;
    SDL_Event   event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                uint8_t key = handle_key_down(event.key, chip8);
                if (chip8->key_event && key != NO_KEY) {
                    chip8->key_event = false;
                    chip8->V[chip8->waiting_key_register] = key;
                }
                if (event.key.key == SDLK_ESCAPE)
                    running = false;
            }
            if (event.type == SDL_EVENT_KEY_UP) {
                handle_key_up(event.key, chip8);
            }
        }

        for (int i = 0; i < 10; i++) {
            if (chip8->key_event)
                break;
            code = decode(
                (chip8->memory[chip8->program_counter] << 8)
                | chip8->memory[chip8->program_counter + 1]
            );
            chip8->program_counter += 2;
            if (!execute_nibble(code, chip8))
                return false;
        }

        if (chip8->draw_flag)
        {
            draw_screen(gfx, chip8->screen);
            chip8->draw_flag = false;
        }

        update_timers(chip8);
        SDL_Delay(16);
    }

    return (true);
}