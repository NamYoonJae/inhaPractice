#include "stdafx.h"
#include "basic.h"
#include "SoundManager.h"

cSoundManager::cSoundManager()
	:m_fVolume(1.0f)
{
	init();
}

cSoundManager::~cSoundManager()
{
	Stop();
	m_fmodSystem->close();
}

// cant use
void cSoundManager::Destroy()
{
	delete m_fmodSystem;
}

void cSoundManager::Update()
{
	if (m_fmodSystem)
		m_fmodSystem->update();

	/* IMPORTANT! CALL THIS ONCE PER FRAME! */
}

void cSoundManager::init()
{
	System_Create(&m_fmodSystem);
	m_fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);

	m_vecSounds.resize(eSoundList::SoundListSize);
	
	{
		string szFullPath;
		string szPathHead = "data/Sound/SFX/Paladin/NW_Move ";
		string szPathTail = ".mp3";
		
		for(int i = Paladin_Move1; i <= Paladin_Move8; i++)
		{
			szFullPath = szPathHead + to_string(i) + szPathTail;
			AddSFX(szFullPath, i);
		}
	}
}

void cSoundManager::AddBGM(string path)
{
	m_fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &m_sbgm);
}

void cSoundManager::Add3DSFX(string path, unsigned soundindex)
{
	m_fmodSystem->createSound(path.c_str(), FMOD_3D, 
		NULL, &m_vecSounds[soundindex]);
}

void cSoundManager::AddSFX(string path, unsigned soundindex)
{
	m_fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &m_vecSounds[soundindex]);
}

void cSoundManager::PlayBGM()
{
	m_fmodSystem->playSound(FMOD_CHANNEL_REUSE, m_sbgm, false, &m_cbgmChannel);
}

void cSoundManager::PlaySFX(unsigned soundindex)
{
	if (m_vecSounds[soundindex] != NULL)
	{
		Channel* m_csfxChannel = 0;	
		m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_vecSounds[soundindex], false, &m_csfxChannel);
	}
}

void cSoundManager::Play3DSFX(unsigned soundindex, FMOD_VECTOR ListenerPos, FMOD_VECTOR ChannelPos,
	FMOD_VECTOR ListenerVel)
{
	if(m_vecSounds[soundindex] != NULL)
	{
		Channel * m_csfxChannel = 0; 
		m_fmodSystem->playSound(FMOD_CHANNEL_FREE,
			m_vecSounds[soundindex],
			false,
			&m_csfxChannel);
		m_csfxChannel->setVolume(m_fVolume);

		m_fmodSystem->set3DListenerAttributes(0, &ListenerPos, &ListenerVel, 0, 0);

		m_csfxChannel->set3DMinMaxDistance(50.0f, 10000.0f);

		m_csfxChannel->set3DAttributes(&ChannelPos, 0);
	}
}

void cSoundManager::Stop()
{
	m_cbgmChannel->stop();
}
