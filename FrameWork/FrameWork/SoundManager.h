#pragma once
#include "fmod.hpp"
#include <map>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

using namespace FMOD;

class SoundManager
{
private:
	System * fmodSystem;

	Channel* bgmChannel;
	Channel* sfxChannel;

	Sound* bgm;
	map<string, Sound*> soundHash;

public:
	SoundManager();
	~SoundManager();

	void init();
	void AddSFX(string path, string musicName);
	void AddBGM(string path);

	void PlaySFX(string soundName);
	void PlayBGM();

	void Stop();

	void Destroy();
};
