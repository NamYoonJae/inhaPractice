#pragma once

#define g_pTimeManager cTimerManager::GetInstance()

class cTimerManager
{
private:
	Singletone(cTimerManager);

	DWORD m_dwLastUpdateTime;
	float m_fElapsedTime;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();

};

