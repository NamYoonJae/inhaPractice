#pragma once

class cDragonSoulEater;



class cSoulEaterState
{
protected:
	cDragonSoulEater *m_pDragon;
	int m_nCurentIndex;
	D3DXVECTOR3 m_vTarget;
	D3DXVECTOR3 m_vDir;

	DWORD m_dwElapsedTime;
public:
	cSoulEaterState();
	cSoulEaterState(cDragonSoulEater*);
	~cSoulEaterState();
	virtual void handle() = 0;
	void SetDragon(cDragonSoulEater* pDragon);
	int GetIndex() { return m_nCurentIndex; }
	D3DXVECTOR3 GetTargetPos() { return m_vTarget; }
	void SetTargetPos(D3DXVECTOR3 Target) { m_vTarget = Target; }
	void TargetCapture();

	enum AnimationSet {
		Sleeping,
		Idle,
		FireBall_Shot,
		Land,
		FlyGlide,
		FlyFireBallShoot,
		Fly_Float,
		Take_Off,
		Run,
		Tail_Attack,
		Get_Hit,
		Walk,
		Defence,
		Basic_Attack
	};

};

//	Idle		0
//	basicattack 1
//	tailattack	2
//	rush		3	
//	scream		4
//	FireBall	5
//	Sleep		6
//	Breath		7
//	Flood		8
//	Stun		9
