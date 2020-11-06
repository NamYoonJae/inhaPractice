#pragma once


class cGroup;

// Obj의 기본은 정적인 객체로 간주합니다.
class cObjObject
{
protected:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vRotateAngle;

	D3DXMATRIXA16 m_matTrans;
	D3DXMATRIXA16 m_matScale;
	D3DXMATRIXA16 m_matRot;
	D3DXMATRIXA16 m_matWorld;

	vector<cGroup*> m_vecGroup;
public:
	cObjObject();
	virtual ~cObjObject();

	virtual void Setup(char* folder, char* file);
	virtual void Update();
	virtual void Render();

	virtual void SetPosition(D3DXVECTOR3 pos)	{ m_vPos = pos;				Update(); }
	virtual void SetScale(D3DXVECTOR3 scale)	{ m_vScale = scale;			Update(); }
	virtual void SetRotation(D3DXVECTOR3 angle) { m_vRotateAngle = angle;	Update(); }
	virtual void SetRotationX(float angle)		{ m_vRotateAngle.x = angle; Update(); }
	virtual void SetRotationY(float angle)		{ m_vRotateAngle.y = angle; Update(); }
	virtual void SetRotationZ(float angle)		{ m_vRotateAngle.z = angle; Update(); }

	virtual D3DXVECTOR3 GetPosition() { return m_vPos; }
	virtual D3DXVECTOR3 GetScale() { return m_vScale; }
	virtual D3DXVECTOR3 GetRotation() { return m_vRotateAngle; }

	virtual vector<cGroup*> & GetGroup() { return m_vecGroup; }
};

