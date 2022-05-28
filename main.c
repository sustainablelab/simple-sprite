#include <SDL.h>
#include <stdio.h>

void die(const char *s)
{
    perror(s);
    SDL_Quit();
    exit(1);
}

typedef uint8_t u8;
typedef u8 bool;
#define true 1
#define false 0
typedef uint32_t u32;
#define SCREEN_W 800
#define SCREEN_H 400
#define PITCH (SCREEN_W * sizeof(u32))

u32 rawpix[SCREEN_W*SCREEN_H*sizeof(u32)];

// #Data
int Data_hstart = 3; // Initial game data value.
void Data_Update(void)
{ // Update game data after a file reload.
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
                    u32 hstart = Data_hstart*SCREEN_W; // start green and blue well beyond half-brightness
                    g = ((n+hstart)*0xCC/(SCREEN_W+hstart)) << 16;
                    b = ((n+hstart)*0xFF/(SCREEN_W+hstart)) << 8;
                }
                // ---< Color the pixel >---
                rawpix[m*SCREEN_W + n] = (r | g | b); // RGBA, alpha is ignored
            }
        }
    }
}
const char * File_name = "data.txt";
void File_Reload(void)
{ // Reload data.txt
    /* *************DOC***************
     * Look at first character in data.txt.
     * Interpret as an integer.
     * Store this value in Data_hstart.
     * *******************************/
    FILE *f;
    f = fopen(File_name, "r");
    if (f == NULL) { printf("Cannot find \"%s\"\n", File_name); fflush(stdout); return; }
    fscanf(f, "%d", &Data_hstart);
    printf("Reload game data: new Data_hstart is %d.\n", Data_hstart); fflush(stdout);
    fclose(f);
}

int main(int argc, char *argv[])
{
    /* =====[ SETUP ]===== */
    int i=0;
    for (i=0; i<argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
    }
    int Window_x = (i>1) ? atoi(argv[1]) : 0;
    int Window_y = (i>2) ? atoi(argv[2]) : 0;
    int Window_w = (i>3) ? atoi(argv[3]) : SCREEN_W;
    int Window_h = (i>4) ? atoi(argv[4]) : SCREEN_H;

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) die(SDL_GetError());

    SDL_WindowFlags win_flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP;
                                           //  x    y
    /* SDL_Window *win = SDL_CreateWindow("BOB", Window_x, Window_y, SCREEN_W, SCREEN_H, win_flags); */
    SDL_Window *win = SDL_CreateWindow("BOB", Window_x, Window_y, Window_w, Window_h, win_flags);
    if (win == NULL) die(SDL_GetError());

    SDL_RendererFlags ren_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, ren_flags);
    if (ren == NULL) die(SDL_GetError());

    SDL_Texture *tex = SDL_CreateTexture(ren,
            /* SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H); */
            SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Window_w, Window_h);
    if (tex == NULL) die(SDL_GetError());

    /* =====[ GAME ]===== */

    // Initial data load.
    Data_Update();

    // TODO: Doc says this is slow, for textures that do not change often.
    if (SDL_UpdateTexture(tex, NULL, rawpix, PITCH) < 0) die(SDL_GetError());

    bool quit = false;
    while (!quit)
    {
        // Look for quit
        SDL_Event ui;
        while (SDL_PollEvent(&ui))
        {
            { // ---< Keyboard Input >---
                if (ui.type == SDL_KEYDOWN)
                {
                    SDL_Keycode sdlk_key = ui.key.keysym.sym;
                    switch(sdlk_key)
                    {
                        case SDLK_q: quit=true; break;
                        case SDLK_SPACE:
                             File_Reload();
                             Data_Update();
                             if (SDL_UpdateTexture(tex, NULL, rawpix, PITCH) < 0) die(SDL_GetError());
                             break;
                        default: break;
                    }
                }
            }
        }

        // Draw textures to back buffer
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        // Swap back buffer with front buffer
        SDL_RenderPresent(ren);
    }

    /* =====[ CLEANUP ]===== */
    printf("Ran OK");
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
