//
// Created by burrito on 07/04/2026.
// TODO

#include "audio_stream.h"

#include "audio_manager.h"

AudioStream::AudioStream(ResourceLocation source) {
    this->wav = std::move(source);

}

