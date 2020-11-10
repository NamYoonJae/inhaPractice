#pragma once
#include "fmod.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmodex_vc.lib")

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

#define g_pSoundManager cSoundManager::GetInstance()

using namespace FMOD;

class cSoundManager
{
private:
	Singletone(cSoundManager);
	System * m_fmodSystem;
	Channel* m_cbgmChannel;

	Sound* m_sbgm;
	map<string, Sound*> m_mapsoundHash;
	float	m_fVolume;
public:
	void init();
	void AddSFX(string path, string soundName);
	void AddBGM(string path);

	void Add3DSFX(string path, string soundName);
	
	void PlaySFX(string soundName);
	void Play3DSFX(string soundName,FMOD_VECTOR ListenerPos,FMOD_VECTOR ChannelPos,FMOD_VECTOR ListenerVel = FMOD_VECTOR{0,0,0});
	void PlayBGM();

	void Stop();

	void Destroy();
	void Update();

	void SetVolume(float fVolume) { m_fVolume = fVolume; }
	float GetVolume() { return m_fVolume; }
};
