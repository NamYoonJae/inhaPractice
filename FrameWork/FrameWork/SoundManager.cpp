#include "stdafx.h"
#include "basic.h"
#include "SoundManager.h"

cSoundManager::cSoundManager()
	:m_fSFXVolume(1.0f)
	,m_fBGMVolume(1.0f)
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
	m_fmodSystem->init(64, FMOD_INIT_NORMAL, NULL);

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

	{
		// Dragon SFX
		string strPath = "data/Sound/SFX/Dragon/";
		for (int i = Dragon_Move0; i <= Dragon_Move9; ++i)
		{
			string strFullPath = strPath + string("Move/NW_Dragon_Move ") +
				to_string(i + 1 - Dragon_Move0) + string(".mp3");
			AddSFX(strFullPath  ,i);
		}

		AddSFX(strPath + string("NW_Dragon_Basic Attack.mp3"),(int)Dragon_BasicAttack);
		AddSFX(strPath + string("NW_Dragon_Tail Attack.mp3"), (int)Dragon_TailAttack);
		AddSFX(strPath + string("NW_Dragon_Shout.mp3"), (int)Dragon_Scream);
		AddSFX(strPath + string("NW_Dragon_Stun.mp3"), (int)Dragon_Stun);
		AddSFX(strPath + string("GetHit/NW_Dragon_Hit 1.mp3"), (int)Dragon_GetHit1);
		AddSFX(strPath + string("GetHit/NW_Dragon_Hit 2.mp3"), (int)Dragon_GetHit2);
		AddSFX(strPath + string("GetHit/NW_Dragon_Hit 3.mp3"), (int)Dragon_GetHit3);
		AddSFX(strPath + string("NW_Dragon_HP.mp3"), (int)Dragon_Sleep);
		AddSFX(strPath + string("Fly/NW_Dragon_Fly 1.mp3"), (int)Dragon_Fly1);
		AddSFX(strPath + string("Fly/NW_Dragon_Fly 2.mp3"), (int)Dragon_Fly2);
		AddSFX(strPath + string("Fly/NW_Dragon_Fly 3.mp3"), (int)Dragon_Fly3);
		AddSFX(strPath + string("Fly/NW_Dragon_Fly Breath_Voice.mp3"), (int)Dragon_FlyFireBall);
		AddSFX(strPath + string("NW_Dragon_Breath.mp3"), (int)Dragon_Breath);
		AddSFX(strPath + string("Die/NW_Dragon_Die_Effect.mp3"), (int)Dragon_Die1); 
		AddSFX(strPath + string("Die/NW_Dragon_Die_Voice.mp3"), (int)Dragon_Die2);
		AddSFX(strPath + string("NW_Dragon_Collision.mp3"), (int)Dragon_Collision);
		//
	}

	{
		//Golem
		string strPath = "data/Sound/SFX/Golem/";
		AddSFX(strPath + string("NW_Golem_Attack 1 Voice.mp3"), (int)Golem_AttackVoice1);
		AddSFX(strPath + string("NW_Golem_Attack 2 Voice.mp3"), (int)Golem_AttackVoice2);
		AddSFX(strPath + string("NW_Golem_Attack 1 Effect.mp3"), (int)Golem_Attack);
		AddSFX(strPath + string("NW_Golem_Die.mp3"), (int)Golem_Die);
	
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
	//m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_sbgm, false, &m_cbgmChannel);
	m_cbgmChannel->setVolume(m_fBGMVolume);
}

void cSoundManager::PlaySFX(unsigned soundindex)
{
	//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "d", soundindex);
	if (m_vecSounds[soundindex] != NULL)
	{
		Channel* m_csfxChannel = 0;	
		FMOD_RESULT r;
		r = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_vecSounds[soundindex], false, &m_csfxChannel);
		m_csfxChannel->setVolume(m_fSFXVolume);
		
		if (r == FMOD_OK)
		{
			//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s","OK");
		}
		else
		{
			//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "FAILED");
		}
	}

	// fix
	m_fmodSystem->update();
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
		m_csfxChannel->setVolume(m_fSFXVolume);

		m_fmodSystem->set3DListenerAttributes(0, &ListenerPos, &ListenerVel, 0, 0);

		m_csfxChannel->set3DMinMaxDistance(50.0f, 10000.0f);

		m_csfxChannel->set3DAttributes(&ChannelPos, 0);
	}
}

void cSoundManager::Stop()
{
	m_cbgmChannel->stop();
}
