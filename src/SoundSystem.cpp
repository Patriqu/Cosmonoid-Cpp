#include "SoundSystem.h"

#include "UpdateGame.h"

SoundSystem::SoundSystem()
{
    music_tracks["menu_music"] = Mix_LoadMUS("sound/menu_music.mp3");
    sound_samples["ball_collision"] = Mix_LoadWAV("sound/92622__nigelcoop__canbounce-2.wav");

    volumes = {{"off", 0}, {"low", 8}, {"medium", 15}, {"high", 30}, {"very high", 45}};
}

void SoundSystem::setVolumeSound(const std::string sound_vol)
{
    Mix_Volume(-1, volumes[sound_vol]);
}

void SoundSystem::setVolumeMusic(const std::string music_vol)
{
    Mix_VolumeMusic(volumes[music_vol]);
}

void SoundSystem::playMusic(const std::string track)
{
    Mix_PlayMusic(music_tracks[track], -1);
}

void SoundSystem::playSoundSample(const std::string sample)
{
    if (Mix_PlayChannel(1, sound_samples[sample], 0) == -1)
    {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }
}

void SoundSystem::stopMenuMusic()
{
    Mix_HaltMusic();
}
