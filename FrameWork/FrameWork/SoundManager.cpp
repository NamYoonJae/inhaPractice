#include "stdafx.h"
#include "basic.h"
#include "SoundManager.h"

cSoundManager::cSoundManager()
{
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

void cSoundManager::init()
{
	System_Create(&m_fmodSystem);
	m_fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);
	
	AddSFX("sounds/appear.wav", "BombPut");
	AddSFX("sounds/die.wav", "Die");
	AddSFX("sounds/draw.wav", "Draw");
	AddSFX("sounds/explode.wav", "Boom");
	AddSFX("sounds/get.wav", "ItemGet");
	AddSFX("sounds/lay.wav", "Lay");
	AddSFX("sounds/lose.wav", "Lose");
	AddSFX("sounds/start.wav", "Start");
	AddSFX("sounds/win.wav", "Win");
}

void cSoundManager::AddBGM(string path)
{
	//fmodSystem->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
	m_fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &m_sbgm);
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
		m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_mapsoundHash[soundName], false, &m_csfxChannel);
}

void cSoundManager::Stop()
{
	m_csfxChannel->stop();
	m_cbgmChannel->stop();
}