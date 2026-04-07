//
// Created by burrito on 07/04/2026.
// TODO

#ifndef JAMEJAM_AUDIO_STREAM_H
#define JAMEJAM_AUDIO_STREAM_H
#include <SDL3/SDL_audio.h>

#include "resource_location.h"

#define PLAYSTATE_PLAYING 1
#define PLAYSTATE_PAUSED 0
#define PLAYSTATE_ERR -1


typedef struct WAVAudioDataStore {
    Uint8 wav_data;
    Uint8 durationBytes;
};

class AudioStream {

public:

    // samples amplitude.
    // ...
    // get it? like amplitude
    float samplitude();

    // pauses the stream, returns true on success
    bool pause();

    // plays the stream, returns true on success
    bool play();

    // returns 1 for playing, 0 for paused, and -1 for error
    int getPlayState();

    AudioStream(ResourceLocation wavLocation);

private:
    WAVAudioDataStore source = {};
    ResourceLocation wav = ResourceLocation::empty();
    float durationSeconds = 0;
    Uint8 durationBytes{};
    int playState = PLAYSTATE_PAUSED;
    Uint8 wav_data{};
    SDL_AudioStream *stream = NULL;
};


#endif //JAMEJAM_AUDIO_STREAM_H
