#pragma once
#include "cObject.h"
#include "SkinnedMesh.h"
#include "SoundManager.h"

//
class cSoulEaterState;
class cOBB;

enum eDebuff_Dragon 
{
	enum_Stun_Dragon,
	enum_Trip_Dragon,
};


class cDragonSoulEater :
	public cObject
{
private:
	cSkinnedMesh*		m_pSkinnedUnit;
	D3DMATERIAL9		m_Mstl;

	
	cSoulEaterState*	m_pCurState;
	
	DWORD				m_dwDelayState;

	D3DXMATRIXA16		m_matWorld;
	LPDIRECT3DTEXTURE9	m_pTexture;

	vector<BoundingBox> m_vecBoundingBoxList;
	
	D3DXVECTOR3*			m_pvTarget;
	int						m_nPrevStateIndex;
	D3DXMATRIXA16			m_matRotation;

	float				m_fPhysicDamage;
	float				m_fElementalDamage;

	float				m_fPhysicsDefence;		
	float				m_fElementalDefence;	

	// >> 2020. 12. 23.
	float				m_AttackCooldown;

	bool				m_IsRage; //
	float				m_fRagegauge; //

	float				m_RageRate;
	float				m_RageDuration;
	float				m_RageDecreaseDefence;
	float				m_RageIncreaseAttack;

	bool				m_IsRigid; //
	float				m_Rigid_Gauge; //
	float				m_Rigid_Rate;
	float				m_Rigid_DecreaseRateValue;
	float				m_Rigid_Duration;

	bool				m_IsStun; //
	float				m_Stun_Gauge;//
	float				m_Stun_Rate;
	float				m_Stun_Decrease_Value;
	float				m_Stun_Duration;

	int					m_Skill_Weight_1;
	int					m_Skill_Weight_2;
	int					m_Skill_Weight_3;
	int					m_Skill_Weight_4;

	float				m_Speed;

	// 기본공격 // 패턴 1
	float				m_BasicAttack_Physic_Rate;
	float				m_BasicAttack_Elemental_Rate;
	// 브레스 // 패턴 4
	float				m_Breath_Duration;
	float				m_Breath_Physic_Rate;
	float				m_Breath_Elemental_Rate;
	// 파이어볼 // 즉사기 패턴
	float				m_FireBall_Physic_Rate;
	float				m_FireBall_Elemental_Rate;
	float				m_FireBall_Range;
	// 장판 // 패턴 3
	float				m_Flood_Physic_Rate;
	float				m_Flood_Elemental_Rate;
	string				m_Flood_Condition; // 상태이상 부여 종류
	float				m_Flood_Condition_Rate; // 상태이상 부여치
	// 돌진 // 패턴 2
	float				m_Rush_Physic_Rate;
	float				m_Rush_Elemental_Rate;
	// 포효 // 포효 패턴
	float				m_Scream_Range;
	// 수면 // 체력회복 패턴
	float				m_Sleep_Duration;
	// 꼬리치기 // 패턴 1
	float				m_TailAttack_Physic_Rate;
	float				m_TailAttack_Elemental_Rate;

	// ---- 오브젝트 상호작용속성 -----
	int					m_Wall_Stun_Damage; // 벽 충돌시 받는 기절치
	int					m_Wall_Rigid_Damage; // 벽 충돌시 받는 경직치
	// << 2020. 12. 23.

	int					m_nPhase;
	int					m_Debuff;
	

	//DWORD				m_dwSwampCreateCoolTime;
	//DWORD				m_dwSwampElapsedTime;


	Synthesize(float, m_fStungauge, STUN);
	Synthesize(float, m_fMaxHeathPoint, MAXHP);
	Synthesize(float, m_fCurHeathpoint, CURHP);
	bool m_IsBreathe;
	bool m_IsFireball;

	int m_nTestStateIndex;
public:
	cDragonSoulEater();
	~cDragonSoulEater();
	void Update() override;
	void Render(D3DXMATRIXA16* pmat) override;
	void Setup(char* szFolder, char* szFileName);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedUnit; }

	void GetWorldMatrix(D3DXMATRIXA16* matWorld);

	void SetupBoundingBox();
	virtual void CollisionProcess(cObject* pObject) override;
	//std::vector<cOBB*>* GetBouningBox() { return &m_vecBoundingBoxList; }

	//new
	void Request();
	D3DXVECTOR3* GetTarget();
	D3DXMATRIXA16* GetRotation() { return &m_matRotation; }
	void SetRotation(D3DXMATRIXA16* mat) { m_matRotation = *mat; }
	int CurrentStateIndex();
	void HitSound() override;
	const int GetPhase() { return m_nPhase; }
};


