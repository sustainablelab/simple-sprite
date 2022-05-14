#include <SDL.h>
#include <stdio.h>

void die(const char *s)
{
    perror(s);
    SDL_Quit();
    exit(1);
}

int main(int argc, char *argv[])
{
    /* =====[ SETUP ]===== */
    for (int i=0; i<argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) die(SDL_GetError());

                                           //  x    y    w    h   flags
    SDL_Window *win = SDL_CreateWindow("BOB", 100, 200, 200, 100, 0);
    if (win == NULL) die(SDL_GetError());

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL) die(SDL_GetError());

    /* =====[ GAME ]===== */
    SDL_Delay(1000);

    /* =====[ CLEANUP ]===== */
    printf("Ran OK");
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
