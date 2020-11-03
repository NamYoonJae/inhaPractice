#pragma once
#include "fmod.hpp"
#include <map>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmodex_vc.lib")

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

using namespace FMOD;

class cSoundManager
{
private:
	System * m_fmodSystem;

	Channel* m_cbgmChannel;
	Channel* m_csfxChannel;

	Sound* m_sbgm;
	map<string, Sound*> m_mapsoundHash;

public:
	cSoundManager();
	~cSoundManager();

	void init();
	void AddSFX(string path, string musicName);
	void AddBGM(string path);

	void PlaySFX(string soundName);
	void PlayBGM();

	void Stop();

	void Destroy();
};
