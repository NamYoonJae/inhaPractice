#pragma once

class cGroup;
class cMtlTex;

// Obj�� �⺻�� ������ ��ü�� �����մϴ�.
class cObjDefault
{
protected:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vRotateAngle;

	D3DXMATRIXA16 m_matTrans;
	D3DXMATRIXA16 m_matScale;
	D3DXMATRIXA16 m_matRot;
	D3DXMATRIXA16 m_matWorld;
public:
	cObjDefault();
	virtual ~cObjDefault();

	virtual void Setup(char* folder, char* file) = 0;
	virtual void Update();
	virtual void Render() = 0;

	virtual void SetPosition(D3DXVECTOR3 pos) { m_vPos = pos;				Update(); }
	virtual void SetScale(D3DXVECTOR3 scale) { m_vScale = scale;			Update(); }
	virtual void SetRotation(D3DXVECTOR3 angle) { m_vRotateAngle = angle;	Update(); }
	virtual void SetRotationX(float angle) { m_vRotateAngle.x = angle; Update(); }
	virtual void SetRotationY(float angle) { m_vRotateAngle.y = angle; Update(); }
	virtual void SetRotationZ(float angle) { m_vRotateAngle.z = angle; Update(); }

	virtual D3DXVECTOR3 GetPosition() { return m_vPos; }
	virtual D3DXVECTOR3 GetScale() { return m_vScale; }
	virtual D3DXVECTOR3 GetRotation() { return m_vRotateAngle; }
};

class cObjObject : public cObjDefault
{
private:
	vector<cGroup*> m_vecGroup;
public:
	cObjObject();
	virtual ~cObjObject();

	virtual void Setup(char* folder, char* file);
	virtual void Update();
	virtual void Render();

	virtual vector<cGroup*> & GetGroup() { return m_vecGroup; }
};

class cObjMesh : public cObjDefault
{
private:
	LPD3DXMESH m_Mesh;
	vector<cMtlTex*> m_vecMtlTex;
public:
	cObjMesh();
	virtual ~cObjMesh();

	virtual void Setup(char* folder, char* file) override;
	virtual void Render() override;
	
	virtual vector<cMtlTex*> & GetMtlTex() { return m_vecMtlTex; }
};
