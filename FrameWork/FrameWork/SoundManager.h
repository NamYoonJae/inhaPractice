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

enum eSoundList
{
	Paladin_Move1 = 0,
	Paladin_Move2,
	Paladin_Move3,
	Paladin_Move4,
	Paladin_Move5,
	Paladin_Move6,
	Paladin_Move7,
	Paladin_Move8,





	
	SoundListSize
};

class cSoundManager
{
private:
	Singletone(cSoundManager);
	System * m_fmodSystem;
	Channel* m_cbgmChannel;

	Sound* m_sbgm;
	vector<Sound*> m_vecSounds;
	float	m_fVolume;
public:
	void init();
	void AddSFX(string path, unsigned soundindex);
	void AddBGM(string path);

	void Add3DSFX(string path, unsigned soundindex);
	
	void PlaySFX(unsigned soundindex);
	void Play3DSFX(unsigned soundindex, FMOD_VECTOR ListenerPos,FMOD_VECTOR ChannelPos, FMOD_VECTOR ListenerVel = FMOD_VECTOR{0,0,0});
	void PlayBGM();

	void Stop();

	void Destroy();
	void Update();

	void SetVolume(float fVolume) { m_fVolume = fVolume; }
	float GetVolume() { return m_fVolume; }
};
