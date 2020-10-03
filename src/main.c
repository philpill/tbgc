#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_TICK_PER_FRAME = 1000 / 30;

void close()
{
    render_destroy();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;
    SDL_Event e;

    double start_t, end_t, total_t;

    int posx = 0;
    int posy = 0;

    render_init();

    // start timer
    start_t = SDL_GetTicks();

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    posy--;
                    break;

                case SDLK_DOWN:
                    posy++;
                    break;

                case SDLK_LEFT:
                    posx--;
                    break;

                case SDLK_RIGHT:
                    posx++;
                    break;

                case SDLK_ESCAPE:
                    close();
                    return 0;
                }
            }
        }

        render_handle(posx, posy);

        end_t = SDL_GetTicks();

        total_t = end_t - start_t;

        // printf("%d - %d = %d\n", end_t, start_t, total_t);

        if (total_t < SCREEN_TICK_PER_FRAME)
        {
            // printf("delay: %d\n", SCREEN_TICK_PER_FRAME - total_t);

            SDL_Delay(SCREEN_TICK_PER_FRAME - total_t);

            start_t = SDL_GetTicks();
        }
    }

    close();

    return 0;
}
