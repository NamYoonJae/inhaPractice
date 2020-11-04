#include "stdafx.h"
#include "basic.h"
#include "TimerManager.h"


cTimerManager::cTimerManager()
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimerManager::~cTimerManager()
{
}

void cTimerManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float cTimerManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float cTimerManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}
