#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "src/resource_location.h"
#include <GL/glew.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include <GL/glu.h>



static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_AudioStream *stream = NULL;
static Uint8 *wav_data = NULL;
static Uint32 wav_data_len = 0;

int loadSDL() {
    // basic sdl setup
    SDL_AudioSpec spec;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("Game Window (WIP TEST BUILD)", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!window) {
        printf("Window failed to be created: %s\n", SDL_GetError());
    }

    // in future a dedicated audio manager will be made, this is for a test
    if (!SDL_LoadWAV("./assets/base/sound/music/menu.wav", &spec, &wav_data, &wav_data_len)) {
        SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_ResumeAudioStreamDevice(stream);



    bool running = true;

    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
        }

        if (SDL_GetAudioStreamQueued(stream) < (int)wav_data_len) {
            /* feed more data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
            SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
        }

        SDL_SetRenderDrawColor(renderer,255, 255,255,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_free(wav_data);
    return SDL_APP_SUCCESS;
}

int main() {
    ResourceLocation rl1 = ResourceLocation("base", "test");
    ResourceLocation rl2 = ResourceLocation::empty();
    rl2.parse("base:music/menu");

    std::cout << rl1.toString() << " " << rl2.toString() << std::endl;

   return loadSDL();
}


