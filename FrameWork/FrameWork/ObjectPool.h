#pragma once
#include "cObject.h"

#define  ObjectManager ObjectPool::GetInstance()

class cObjMesh;

class ObjectPool : public cObject
{
	Singletone(ObjectPool);
private:
	std::vector<cObject*> vecObjectList;
	std::vector<cObject*> vecUserInterface;
	std::vector<cObject*> DeleteObject;
	int m_nRefcnt;
public:
	void Update() override;
	void Render(D3DXMATRIXA16* pmat = 0) override;

	void AddChild(cObject* obj);
	void AddStaticChild(cObject* obj);
	void RemoveChild(cObject& obj);
	void Revert();
	//void Revert(int preSceneType, int curSceneType);
	const cObject* GetChild(int nIndex);

	
	void AddUIChild(cObject* obj);
	void RemoveUIChild(cObject& obj);
	const cObject* SearchChild(int nTag);
	const cObject* SearchChildUI(int nTag);
	const cObject* GetUI(int TagUI);

	void ObjectPool::CollisionDetection();
};
