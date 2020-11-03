#include "stdafx.h"
#include "basic.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	Stop();
	fmodSystem->close();
}

// cant use
void SoundManager::Destroy()
{
	delete fmodSystem;
}

void SoundManager::init()
{
	System_Create(&fmodSystem);
	fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);
	
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

void SoundManager::AddBGM(string path)
{
	//fmodSystem->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
	fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
}

void SoundManager::AddSFX(string path, string soundName)
{
	fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &soundHash[soundName]);
}

void SoundManager::PlayBGM()
{
	fmodSystem->playSound(FMOD_CHANNEL_REUSE, bgm, false, &bgmChannel);
}

void SoundManager::PlaySFX(string soundName)
{
	if (soundHash[soundName] != NULL)
		fmodSystem->playSound(FMOD_CHANNEL_FREE, soundHash[soundName], false, &sfxChannel);
}

void SoundManager::Stop()
{
	sfxChannel->stop();
	bgmChannel->stop();
}