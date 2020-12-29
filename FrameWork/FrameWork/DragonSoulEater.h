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
	Synthesize(D3DMATERIAL9, m_Mstl, Material);
	Synthesize(float, m_fPhysicsDefence, PhysicDefence);
	Synthesize(float, m_fElementalDefence, ElementalDefence);
	//float				m_fPhysicsDefence;		
	//float				m_fElementalDefence;	

	float				m_AttackCooldown;

	Synthesize(float, m_fRagegauge,RageGauge); //
	Synthesize(bool, m_IsRage, Rage);

	float				m_RageRate;
	float				m_RageDuration;
	float				m_RageDecreaseDefence;
	float				m_RageIncreaseAttack;

	bool				m_IsRigid; //
	//float				m_Rigid_Gauge; //
	float				m_Rigid_Rate;
	float				m_Rigid_DecreaseRateValue;
	float				m_Rigid_Duration;

	bool				m_IsStun; //
	//float				m_Stun_Gauge;//
	float				m_Stun_Rate;
	float				m_Stun_Decrease_Value;
	float				m_Stun_Duration;

	int					m_Skill_Weight_1;
	int					m_Skill_Weight_2;
	int					m_Skill_Weight_3;
	int					m_Skill_Weight_4;

	float				m_Speed;

	int					m_nPhase;
	int					m_Debuff;
	
	// ---- 오브젝트 상호작용속성 -----
	Synthesize(int, m_Wall_Stun_Damage, WallStunDamage);
	Synthesize(int, m_Wall_Rigid_Damage, WallRigidDamage);
	//int		m_Wall_Stun_Damage; // 벽 충돌시 받는 기절치
	//int		m_Wall_Rigid_Damage; // 벽 충돌시 받는 경직치



	//DWORD				m_dwSwampCreateCoolTime;
	//DWORD				m_dwSwampElapsedTime;


	Synthesize(float, m_fStungauge, STUN);
	Synthesize(float, m_fRigidgauge, Rigid);
	Synthesize(float, m_fMaxHeathPoint, MAXHP);
	Synthesize(float, m_fCurHeathpoint, CURHP);
	bool m_IsBreathe;
	bool m_IsFireball;

	int m_nTestStateIndex;

	// Test Dash Shader
	LPD3DXEFFECT m_pDashShader;
	LPDIRECT3DTEXTURE9 m_pDashTex;

public:
	cDragonSoulEater();
	~cDragonSoulEater();
	void Update() override;
	void Render(D3DXMATRIXA16* pmat) override;
	void Setup(char* szFolder, char* szFileName);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedUnit; }

	void GetWorldMatrix(D3DXMATRIXA16* matWorld);
	//cSoulEaterState* GetState() { return m_pCurState; }
	void SetupBoundingBox();
	virtual void CollisionProcess(cObject* pObject) override;
	virtual void AddCollisionInfo(int nTag, CollisionInfo Info, float fDMG = 0, bool bDamageType = true, float fStunDamage = 0, float fRigidDamage = 0);
	//std::vector<cOBB*>* GetBouningBox() { return &m_vecBoundingBoxList; }

	//new
	void Request();
	void LegacyRequest();
	//
	D3DXVECTOR3* GetTarget();
	D3DXMATRIXA16* GetRotation() { return &m_matRotation; }
	void SetRotation(D3DXMATRIXA16* mat) { m_matRotation = *mat; }
	int CurrentStateIndex();
	void HitSound() override;
	const int GetPhase() { return m_nPhase; }

	void PhaseShift();
	void DashShader();
};


