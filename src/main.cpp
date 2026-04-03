#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "resource_location.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int main() {
    ResourceLocation rl1 = ResourceLocation("game", "test");
    ResourceLocation rl2 = ResourceLocation::empty();
    rl2.parse("game2:test");

    std::cout << rl1.toString() << " " << rl2.toString() << std::endl;

    // basic sdl setup

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("SDL Window", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!window) {
        printf("Window failed to be created: %s\n", SDL_GetError());
    }

    bool running = true;

    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer,255, 255,255,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return SDL_APP_SUCCESS;
}
