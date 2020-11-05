#include "stdafx.h"
#include "basic.h"
#include "TimerManager.h"


cTimerManager::cTimerManager()
	:m_fFPS_Timer(0)
	,m_FPS(0)
{
	QueryPerformanceCounter(&m_liLastTime);
}


cTimerManager::~cTimerManager()
{
}

void cTimerManager::Update()
{
	LARGE_INTEGER CurTime, frequency, DeltaTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&CurTime);
	DeltaTime.QuadPart = (CurTime.QuadPart - m_liLastTime.QuadPart) * 1000000;
	DeltaTime.QuadPart /= frequency.QuadPart;

	m_fElapsedTime = DeltaTime.QuadPart * 0.000001f;

	m_fFPS_Timer += m_fElapsedTime;
	m_FPS++;
	
	if (m_fFPS_Timer > 1)
	{
		cout << "Frame : " << m_FPS << endl;
		m_fFPS_Timer = 0;
		m_FPS = 0;
	}

	m_liLastTime = CurTime;
}

float cTimerManager::GetElapsedTime()
{
	return m_fElapsedTime;
}
