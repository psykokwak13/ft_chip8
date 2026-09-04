#include "../includes/chip8.h"

void draw_screen(gfx_t *gfx, bool screen[64 * 32])
{
    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gfx->renderer);

    SDL_SetRenderDrawColor(gfx->renderer, 0, 128, 0, 255);
    for (int y = 0; y < 32; y++)
        for (int x = 0; x < 64; x++)
            if (screen[y * 64 + x])
            {
                SDL_FRect rect = { x * SCALE, y * SCALE, SCALE, SCALE };
                SDL_RenderFillRect(gfx->renderer, &rect);
            }
    SDL_RenderPresent(gfx->renderer);
}

void draw(chip8_t *chip8, nibble code)
{
    chip8->V[0xF] = 0;
    for (int row = 0; row < code.n; row++)
    {
        uint8_t sprite_byte = chip8->memory[chip8->index_register + row];
        for (int col = 0; col < 8; col++)
        {
            uint8_t sprite_pixel = (sprite_byte >> (7 - col)) & 0x1;
            if (sprite_pixel)
            {
                int x = (chip8->V[code.x] + col) % 64;
                int y = (chip8->V[code.y] + row) % 32;
                int index = y * 64 + x;
                if (chip8->screen[index])
                    chip8->V[0xF] = 1;
                chip8->screen[index] ^= 1;
            }
        }
    }
    chip8->draw_flag = true;
}

bool    setup_gfx(gfx_t *gfx) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "error with SDL_Init\n");
        return (false);
    }

    gfx->window = SDL_CreateWindow("ft_chip8", SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, 0); 
    if (!gfx->window) {
        fprintf(stderr, "Window error : %s\n", SDL_GetError());
        return (false);
    }

    gfx->renderer = SDL_CreateRenderer(gfx->window, NULL);
    if (!gfx->renderer) {
        fprintf(stderr, "Renderer error : %s\n", SDL_GetError());
        return (false);
    }

    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gfx->renderer);
    SDL_RenderPresent(gfx->renderer);

    return (true);
}

void    clean_gfx(gfx_t *gfx) {
    SDL_DestroyRenderer(gfx->renderer);
    SDL_DestroyWindow(gfx->window);
    SDL_Quit();
}
