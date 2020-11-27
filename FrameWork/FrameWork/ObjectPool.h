#pragma once
#include "cObject.h"

#define  ObjectManager ObjectPool::GetInstance()

class cObjMesh;

class ObjectPool : public cObject
{
	Singletone(ObjectPool);
private:
	// temp
	cObjMesh* m_pObjMesh;
	//
	std::vector<cObject*> vecObjectList;
	std::vector<cObject*> vecUserInterface;
	int m_nRefcnt;
public:

	void Update() override;
	void Render(D3DXMATRIXA16* pmat = 0) override;

	void AddChild(cObject* obj);
	void AddStaticChild(cObject* obj);
	void RemoveChild(cObject& obj);
	void Revert();
	const cObject* GetChlid(int nIndex);

	
	void AddUIChild(cObject* obj);
	void RemoveUIChild(cObject& obj);

	const cObject* SearchChild(int nTag);

	void CollisionProcess();
};

struct HitDelay
{
	DWORD dwHitTime;
	DWORD dwDelayTime;
	Tag	  CrashObjectTag;
};

