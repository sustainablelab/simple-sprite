#include <SDL.h>
#include <stdio.h>

void die(const char *s)
{
    perror(s);
    SDL_Quit();
    exit(1);
}

typedef uint8_t u8;
typedef uint32_t u32;
#define SCREEN_W 800
#define SCREEN_H 400
#define PITCH (SCREEN_W * sizeof(u32))

u32 rawpix[SCREEN_W*SCREEN_H*sizeof(u32)];

int main(int argc, char *argv[])
{
    /* =====[ SETUP ]===== */
    for (int i=0; i<argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) die(SDL_GetError());

                                           //  x    y    w         h        flags
    SDL_Window *win = SDL_CreateWindow("BOB", 100, 200, SCREEN_W, SCREEN_H, SDL_WINDOW_BORDERLESS);
    if (win == NULL) die(SDL_GetError());

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL) die(SDL_GetError());

    SDL_Texture *tex = SDL_CreateTexture(ren,
            SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H);
    if (tex == NULL) die(SDL_GetError());

    /* =====[ GAME ]===== */

    { // Fill the window with a beautiful complex sunset gradient
        for (u32 m=0; m < SCREEN_H; m++) {
            for (u32 n=0; n < SCREEN_W; n++) {
                u32 r, g, b;
                { // ---< Calculate the color >---
                    //
                    // Base color
                    // u32 r = 0x00 << 24;
                    // u32 g = 0xCC << 16;
                    // u32 b = 0xFF << 8;
                    //
                    // Gradient color
                    // Scale vertical red gradient to match screen height
                    u32 vstart = 2*SCREEN_H; // start red beyond half-brightness
                    r = ((m+vstart)*255/(SCREEN_H+vstart)) << 24;
                    // Scale horizontal green and blue gradients to match screen width
                    u32 hstart = 3*SCREEN_W; // start green and blue well beyond half-brightness
                    g = ((n+hstart)*0xCC/(SCREEN_W+hstart)) << 16;
                    b = ((n+hstart)*0xFF/(SCREEN_W+hstart)) << 8;
                }
                // ---< Color the pixel >---
                rawpix[m*SCREEN_W + n] = (r | g | b); // RGBA, alpha is ignored
            }
        }
    }

    // TODO: Doc says this is slow, for textures that do not change often.
    if (SDL_UpdateTexture(tex, NULL, rawpix, PITCH) < 0) die(SDL_GetError());

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(1000);

    /* =====[ CLEANUP ]===== */
    printf("Ran OK");
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
