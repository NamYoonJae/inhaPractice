#pragma once

#define g_pTimeManager cTimerManager::GetInstance()

class cTimerManager
{
private:
	Singletone(cTimerManager);

	float m_fElapsedTime;

	LARGE_INTEGER m_liLastTime;
	float m_fFPS_Timer;
	int m_FPS;
public:
	void Update();
	float GetElapsedTime();

};

