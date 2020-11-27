#pragma once
#include "cObject.h"
class cGroup;
class cMtlTex;

// Obj의 기본은 정적인 객체로 간주합니다.
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

	virtual void Setup(const char* folder, const char* file) = 0;
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

	virtual D3DXMATRIXA16 GetWorldMatrix() { return m_matWorld; }
	void SetWorldMatrix(D3DXMATRIX* mat) { m_matWorld = *mat; }
};

class cObjObject : public cObjDefault, public cObject
{
private:
	vector<cGroup*> m_vecGroup;
public:
	cObjObject();
	virtual ~cObjObject();

	virtual void Setup(string folder, string file);
	virtual void Setup(const char* folder, const char* file) override;
	virtual void Update();
	virtual void Render(D3DXMATRIXA16* pmat = NULL) override;
	virtual void Render() {};

	virtual vector<cGroup*> & GetGroup() { return m_vecGroup; }
	
};

class cObjMesh : public cObjDefault , public cObject
{
private:
	LPD3DXMESH m_Mesh;
	vector<cMtlTex*> m_vecMtlTex;
public:
	cObjMesh();
	virtual ~cObjMesh();

	virtual void Setup(string folder, string file);
	virtual void Setup(const char* folder, const char* file) override;
	virtual void Render(D3DXMATRIXA16* pmat = NULL) override;
	virtual void Render() {};
	virtual vector<cMtlTex*> & GetMtlTex() { return m_vecMtlTex; }
	virtual LPD3DXMESH GetMesh() { return m_Mesh; }

	
	virtual void Update()override {};
};

