#pragma once
#include "PaladinState.h"
#include "cCharater.h"

class cSkinnedMesh;
class cPaladinState;

class cParts;
class cPaladinWeapon;
class cTrophies;
class cPaladinBody;
class cShadow;

struct ST_BONE;

enum eDebuff_Player 
{
	enum_Idle,
	enum_Poison,
	enum_Stun,
	enum_Roar,
	enum_slow
};

class cPaladin : public cCharater
{
private:
	cSkinnedMesh*	m_pSkinnedUnit;
	float			m_fvelocity;
	float			m_fOriginSpeed;
	float			m_fSpeed;

	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

	bool			m_isMoving;

	cPaladinState*	m_pCurState;
	DWORD			m_dwDelayState;
	
	cOBB*			m_pWeaponOBB;
	D3DXMATRIXA16	m_matWeapon;
	cPaladinWeapon* m_pWeapon;

	vector<cParts*> m_vecParts;

	float m_MaxHp;
	float m_MaxStamina;
	Synthesize(bool, m_isInvincible, Invincible);

	float m_Hp;
	float m_Stamina;
	float m_StaminaRestoreValue;
	//DWORD m_dwStaminaRestoreElapsedTime;
	bool m_IsStaminaState;
	float m_PoisonGauge;

	bool m_IsChangeScene;
	bool m_isStuned;

	int				m_Attack_Melee_Damage;
	float			m_Melee_rate_1;
	float			m_Melee_rate_2;
	float			m_Melee_rate_3;

	int				m_Attack_Elemental_Damage;
	float			m_Attack_StunRate;	// 공격시 기절부여치
	float			m_Attack_RigidRate;	// 공격시 경직부여치

	float			m_Critical_probability;
	int				m_Critical_Additional_Damage;

	int				m_Melee_Defense;
	int				m_Elemental_Defense;

	// char는 character 상태에 대한 속성
	float			m_char_Poison_Rate;
	int				m_Char_Poison_Damage;
	float			m_Char_Poison_Duration;
	
	float			m_Char_StunRate;
	int				m_Char_Stun_Reduce;
	int				m_Char_Stun_Duration;
	float			m_Char_Scream_Duration;

	float			m_Char_Invincibility_Duration;
	int				m_Char_Flinch;  // 캐릭터 움찔 발생 손상치

	bool			m_Char_isSlow;
	float			m_Char_Slow_rate;
	DWORD			m_Char_Slow_Elapsedtime;
	DWORD			m_Char_Slow_DurationTime;

	int				m_Aggro;  // 어그로

	// object interaction 
	float			m_Orb_effect_Duration;

	

	cTrophies* m_pTrophies;

	vector<int> m_vecDebuff;
	vector<cPopup*> m_vecDebuff_UI;
	vector<long> m_vecDebuffStartTime;	//디버프 시작 시간
	D3DXMATRIXA16 TempRot;
	DWORD m_dwDeverffPreTime; //디버프 적용 시간 딜레이(ex 3초마다 / 5초마다)
	DWORD m_dwDeverffStartTime;	//디버프 적용 시간 딜레이

	DWORD m_dwStaminaPreTime;
	DWORD m_dwStaminaStartTime;

	DWORD m_DethTime;
	bool m_Deth;

public:
	cPaladin();
	~cPaladin();

	void Setup(char* szFolder, char* szFile);
	void ShadowShaderSetup();
	void ShaderSetup();
	void Update();
	void Update(EventType event) override;
	void Render(D3DXMATRIXA16 * pmat = NULL);
	void ShaderRender();
	void CreateShadow();

	void CollisionProcess(cObject* pObject) override;
	void StateFeedback();
	
	void SetPosition(D3DXVECTOR3 pos) { m_vPos = pos; };
	D3DXVECTOR3 GetPosition() { return m_vPos; };

	cSkinnedMesh* GetSkinnedMesh() { return m_pSkinnedUnit; };

	void CreateTrophies(EventType message);

	float GetHp() { return m_Hp; }
	float GetStamina() { return m_Stamina; }
	void SetStamina(float stamina) { m_Stamina = stamina; };
	float GetMaxHp() { return m_MaxHp; }
	float GetMaxStamina() { return m_MaxStamina; }
	float GetOriginSpeed() { return m_fOriginSpeed; }

	void SetSpeed(int speed) { m_fSpeed = speed; }
	void SetDebuff(int debuff);
	int vecDebuffFind(int debuff);
	void ReloadSpriteDebuff();

	//
	int GetStateIndex() { return m_pCurState->GetStateIndex(); }
	vector<cParts*> GetPartsList() { return m_vecParts; }

	// backviewCamera
	void SetCameraRot(D3DXVECTOR3 CameraRot) { m_vCameraRot = CameraRot; }
	void SetCameraDir(D3DXVECTOR3 CameraDir) { m_vCameraDir = CameraDir; }

	int SearchDebuff(int debuff);
	void SetStaminaState(bool state) { m_IsStaminaState = state; };

	//
	void AddCollisionInfo(int nTag, CollisionInfo Info, float fDMG = 0, bool bDamageType = true, float fStunDamage = 0.0f, float fRigidDamage = 0.0f, float slow = 0.0f) override;
	
	void PlayAttackSound();
	void PlayDeathSound();

	void SetStun(bool isStuned) { m_isStuned = isStuned; }
	void OnStun(bool isHardStun);
	void OnDeath();

	cTrophies* GetTrophies() { return m_pTrophies; };
	void IncreasePoisonGauge() { m_PoisonGauge += 20; };
};

class cParts
{
protected:
	cOBB*			m_pOBB;
	ST_BONE*		m_pBone;
	Synthesize(D3DCOLOR, m_color, Color);
	
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vRot;
	D3DXVECTOR3		m_vScale;

	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

public:
	cParts();
	virtual ~cParts();

	virtual void Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat);
	virtual void Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* pmat);
	virtual void Update(D3DXMATRIXA16* pmat);
	virtual void Render();
	
	cOBB* GetOBB() { return m_pOBB; }
};


class cPaladinWeapon : public cParts
{
public:
	cPaladinWeapon(){};
	~cPaladinWeapon() = default;

	void Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat) override;
	void Update(D3DXMATRIXA16* pmat) override;
};

class cPaladinBody : public cParts
{
public:
	cPaladinBody(){};
	~cPaladinBody() = default;

	void Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* pmat) override;
	void Update(D3DXMATRIXA16* pmat) override;
};
