#pragma once

#include <map>
#include <string>

#include "SDL_mixer.h"

class SoundSystem
{
public:
    SoundSystem();
    ~SoundSystem() = default;

    void setVolumeSound(std::string);
    void setVolumeMusic(std::string);

    void playMusic(std::string track);
    void playSoundSample(std::string sample);
    
    void stopMenuMusic();

private:
    std::map<std::string, Mix_Music*> music_tracks;
    std::map<std::string, Mix_Chunk*> sound_samples;

    std::map<std::string, int> volumes;
};
