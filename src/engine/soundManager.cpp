#include "soundManager.h"

SDL_AudioDeviceID soundManager::device = 0;

std::map<std::string, std::string> soundManager::pathTable = {
    { "bgm",  "assets/kenney_pixel-platformer/Sounds/Playing.wav" },
    { "click","assets/kenney_pixel-platformer/Sounds/Click.wav" },
    { "win",  "assets/kenney_pixel-platformer/Sounds/Youwin.wav" },
    { "lose", "assets/kenney_pixel-platformer/Sounds/Youlose.wav" },
    { "earncoin","assets/kenney_pixel-platformer/Sounds/Earncoin.wav" },
    { "enemy",   "assets/kenney_pixel-platformer/Sounds/Enemy.wav" },
    { "item",    "assets/kenney_pixel-platformer/Sounds/Item.wav" },
    { "itembox", "assets/kenney_pixel-platformer/Sounds/Itembox.wav" },
    { "jump",    "assets/kenney_pixel-platformer/Sounds/Jump.wav" },
    { "ladder",  "assets/kenney_pixel-platformer/Sounds/Ladder.wav" },
    { "punji",   "assets/kenney_pixel-platformer/Sounds/Punji.wav" },
    { "switch",  "assets/kenney_pixel-platformer/Sounds/Switch.wav" },
};

SDL_AudioStream* soundManager::musicStream = nullptr;
Uint8* soundManager::musicBuffer = nullptr;
Uint32 soundManager::musicLength = 0;
bool soundManager::musicLoop = false;
bool soundManager::muted = false;
std::vector<SDL_AudioStream*> soundManager::effectStreams;

bool soundManager::isMuted() { return muted; }
void soundManager::toggleMute() { muted = !muted; }

bool soundManager::init() {
    device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (device == 0) {
        SDL_Log("soundManager: khong mo duoc thiet bi am thanh: %s", SDL_GetError());
        return false;
    }
    SDL_ResumeAudioDevice(device);
    return true;
}

SDL_AudioStream* soundManager::createStream(const std::string& key, Uint8** outBuf, Uint32* outLen) {
    *outBuf = nullptr;
    *outLen = 0;

    if (device == 0) return nullptr;

    auto it = pathTable.find(key);
    if (it == pathTable.end()) {
        SDL_Log("soundManager: khong co am thanh ten: %s", key.c_str());
        return nullptr;
    }

    SDL_AudioSpec spec;
    Uint8* buf = nullptr;
    Uint32 len = 0;
    if (!SDL_LoadWAV(it->second.c_str(), &spec, &buf, &len)) {
        SDL_Log("soundManager: load that bai %s: %s", it->second.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_AudioStream* stream = SDL_CreateAudioStream(&spec, &spec);
    if (!stream) {
        SDL_Log("soundManager: tao stream that bai: %s", SDL_GetError());
        SDL_free(buf);
        return nullptr;
    }

    if (!SDL_BindAudioStream(device, stream)) {
        SDL_Log("soundManager: bind stream that bai: %s", SDL_GetError());
        SDL_DestroyAudioStream(stream);
        SDL_free(buf);
        return nullptr;
    }

    *outBuf = buf;
    *outLen = len;
    return stream;
}

void soundManager::playMusic(const std::string& key) {
    stopMusic();

    Uint8* buf = nullptr;
    Uint32 len = 0;
    SDL_AudioStream* stream = createStream(key, &buf, &len);
    if (!stream) return;

    SDL_PutAudioStreamData(stream, buf, (int)len);

    musicStream = stream;
    musicBuffer = buf;
    musicLength = len;
    musicLoop = true;
}

void soundManager::stopMusic() {
    if (musicStream) {
        SDL_DestroyAudioStream(musicStream);
        musicStream = nullptr;
    }
    if (musicBuffer) {
        SDL_free(musicBuffer);
        musicBuffer = nullptr;
    }
    musicLength = 0;
    musicLoop = false;
}

void soundManager::playEffect(const std::string& key) {
    Uint8* buf = nullptr;
    Uint32 len = 0;
    SDL_AudioStream* stream = createStream(key, &buf, &len);
    if (!stream) return;

    SDL_PutAudioStreamData(stream, buf, (int)len);
    SDL_free(buf);

    effectStreams.push_back(stream);
}

void soundManager::update() {
    if (musicStream && musicLoop && musicBuffer) {
        if (SDL_GetAudioStreamAvailable(musicStream) <= 0) {
            SDL_PutAudioStreamData(musicStream, musicBuffer, (int)musicLength);
        }
    }

    for (size_t i = 0; i < effectStreams.size(); ) {
        SDL_AudioStream* s = effectStreams[i];
        if (SDL_GetAudioStreamAvailable(s) <= 0) {
            SDL_DestroyAudioStream(s);
            effectStreams.erase(effectStreams.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void soundManager::clearAll() {
    stopMusic();

    for (SDL_AudioStream* s : effectStreams) {
        SDL_DestroyAudioStream(s);
    }
    effectStreams.clear();

    if (device != 0) {
        SDL_CloseAudioDevice(device);
        device = 0;
    }
}
