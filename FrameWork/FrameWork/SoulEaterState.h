#pragma once

class cDragonSoulEater;


enum{NONE_BATTLE,IDLE,RUN,BATTLE,BASIC_ATTACK};


// Head, TailEnd, UpperLeg_Right, UpperLeg_Left, UpperArm_Right, UpperArm_Left,

class cSoulEaterState
{
protected:
	cDragonSoulEater *m_pDragon;
public:
	cSoulEaterState();
	cSoulEaterState(cDragonSoulEater*);
	~cSoulEaterState();
	virtual void handle() = 0;
	void GetDragon(cDragonSoulEater* pDragon);
};

