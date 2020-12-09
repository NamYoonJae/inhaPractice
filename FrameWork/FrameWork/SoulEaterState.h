#pragma once

class cDragonSoulEater;



class cSoulEaterState
{
protected:
	cDragonSoulEater *m_pDragon;
	int m_nCurentIndex;
	D3DXVECTOR3 m_vTarget;
	D3DXVECTOR3 m_vDir;
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
		FirBall_Shot,
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

//
//0 Sleeping
//1 Idle
//2 FireBall_Shot
//3 Land
//4 FlyGlide
//5 FlyFireBallShoot
//6 Fly_Float
//7 Take_Off
//8 Run
//9 Tail_Attack
//10 Get Hit ¸Â´Â°Å
//11 Walk
//12 Defend
//13 Basic Attack