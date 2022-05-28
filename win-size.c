#include <SDL.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    printf("Screen is %d x %d\n", mode.w, mode.h);
    printf("Refresh rate is %d Hz\n", mode.refresh_rate);
    printf("Pixel format is %s\n", SDL_GetPixelFormatName(mode.format));
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}
