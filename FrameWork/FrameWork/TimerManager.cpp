#include "stdafx.h"
#include "basic.h"
#include "FontManager.h"
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
	static int Cnt = 0;
	Cnt++;
	
	if (m_fFPS_Timer > 1)
	{
		m_fFPS_Timer = 0;
		m_FPS = Cnt;
		Cnt = 0;
	}

	m_liLastTime = CurTime;
}

float cTimerManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

int cTimerManager::GetFPS()
{
	return m_FPS;
}

void cTimerManager::DrawFPS()
{
	string Text("Frame : ");
	Text += to_string(m_FPS);
	g_pFontManager->DrawFont(FONT_SYSTEM, Text, 0, 0, 100, 50, FONT_LEFTTOP, FONT_GREEN);
}


