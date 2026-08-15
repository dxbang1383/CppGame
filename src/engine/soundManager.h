#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL3/SDL.h>
#include <string>
#include <map>
#include <vector>

class soundManager {
private:
    static SDL_AudioDeviceID device;
    static std::map<std::string, std::string> pathTable;

    static SDL_AudioStream* musicStream;
    static Uint8* musicBuffer;
    static Uint32 musicLength;
    static bool musicLoop;

    static std::vector<SDL_AudioStream*> effectStreams;

    static SDL_AudioStream* createStream(const std::string& key, Uint8** outBuf, Uint32* outLen);

public:
    static bool init();
    static void playMusic(const std::string& key);
    static void stopMusic();
    static void playEffect(const std::string& key);
    static void update();
    static void clearAll();
};

#endif
