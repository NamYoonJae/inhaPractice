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

	float PhysicRate; // << 

#pragma region SKILL Attribute
	// 파이어볼 // 즉사기 패턴
	float				m_FireBall_Physic_Rate;
	float				m_FireBall_Elemental_Rate;
	float				m_FireBall_Range;
	// 돌진 // 패턴 2
	float				m_Rush_Physic_Rate;
	float				m_Rush_Elemental_Rate;
	// 포효 // 포효 패턴
	float				m_Scream_Range;
	//// 브레스 // 패턴 4
	//float				m_Breath_Duration;
	//float				m_Breath_Physic_Rate;
	//float				m_Breath_Elemental_Rate;
	//// 장판 // 패턴 3 // Flood
	////float			m_Flood_Physic_Rate;
	////float			m_Flood_Elemental_Rate;
	//string			m_Flood_Condition; // 상태이상 부여 종류
	//float				m_Flood_Condition_Rate; // 상태이상 부여치
#pragma region SKILL Attribute

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
