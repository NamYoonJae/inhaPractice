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
	
	AddSFX("data/Sound/SFX/explode.wav", "Boom");
}

void cSoundManager::AddBGM(string path)
{
	m_fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &m_sbgm);
}

void cSoundManager::Add3DSFX(string path, string soundName)
{
	m_fmodSystem->createSound(path.c_str(), FMOD_3D, 
		NULL, &m_mapsoundHash[soundName]);
}

void cSoundManager::AddSFX(string path, string soundName)
{
	m_fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &m_mapsoundHash[soundName]);
}

void cSoundManager::PlayBGM()
{
	m_fmodSystem->playSound(FMOD_CHANNEL_REUSE, m_sbgm, false, &m_cbgmChannel);
}

void cSoundManager::PlaySFX(string soundName)
{
	if (m_mapsoundHash[soundName] != NULL)
	{
		Channel* m_csfxChannel = 0;	
		m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_mapsoundHash[soundName], false, &m_csfxChannel);
	}
}

void cSoundManager::Play3DSFX(string soundName, FMOD_VECTOR ListenerPos, FMOD_VECTOR ChannelPos,
	FMOD_VECTOR ListenerVel)
{
	if(m_mapsoundHash[soundName] != NULL)
	{
		Channel * m_csfxChannel = 0; 
		m_fmodSystem->playSound(FMOD_CHANNEL_FREE,
			m_mapsoundHash[soundName],
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
