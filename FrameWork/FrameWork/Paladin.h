#pragma once
#include "cCharater.h"

class cSkinnedMesh;
class cPaladinState;

class cParts;
class cPaladinWeapon;
class cTrophies;
class cPaladinBody;
struct ST_BONE;

enum eDebuff_Player 
{
	enum_Idle,
	enum_Poison,
	enum_Stun,
	enum_Roar,
};

class cPaladin : public cCharater
{
private:
	cSkinnedMesh*	m_pSkinnedUnit;
	float			m_fvelocity;
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


	int m_MaxHp;
	//int m_MaxStamina;  // 기획서에 float형식이라 명시되어있어 임시적용
	float m_MaxStamina;
	//Synthesize(unsigned int, m_fInvincibleTime, InvincibleTime);
	Synthesize(bool, m_isInvincible, Invincible);

	int m_Hp;
	//int m_Stamina;  // 기획서에 float형식이라 명시되어있어 임시적용
	float m_Stamina;

	cTrophies* m_pTrophies;

	vector<int> m_vecDebuff;
	vector<cPopup*> m_vecDebuff_UI;
	vector<long> m_vecStartTime;
	D3DXMATRIXA16 TempRot;
public:
	cPaladin();
	~cPaladin();

	void Setup(char* szFolder, char* szFile);
	void ShaderSetup();
	void Update();
	void Update(EventType event) override;
	void Render(D3DXMATRIXA16 * pmat = NULL);
	void ShaderRender();

	void CollisionProcess(cObject* pObject) override;
	void StateFeedback();
	
	void SetPosition(D3DXVECTOR3 pos) { m_vPos = pos; };
	D3DXVECTOR3 GetPosition() { return m_vPos; };

	cSkinnedMesh* GetSkinnedMesh() { return m_pSkinnedUnit; };

	void CreateTrophies(EventType message);

	int GetHp() { return m_Hp; }
	int GetStamina() { return m_Stamina; }
	int GetMaxHp() { return m_MaxHp; }
	int GetMaxStamina() { return m_MaxStamina; }

	void SetDebuff(int debuff);
	int vecDebuffFind(int debuff);
	void ReloadSpriteDebuff();

	//
	int GetStateIndex();
	vector<cParts*> GetPartsList() { return m_vecParts; }

	// backviewCamera
	void SetCameraRot(D3DXVECTOR3 CameraRot) { m_vCameraRot = CameraRot; }
	void SetCameraDir(D3DXVECTOR3 CameraDir) { m_vCameraDir = CameraDir; }
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
