#include "stdafx.h"
#include "TimerManager.h"
#include "ObjectPool.h"
#include "EventManager.h"

#include "cOBB.h"
#include "cTerrain.h"
#include "Arthur.h"
#include "DragonSoulEater.h"
#include "ObjObject.h"
#include "Map"

ObjectPool::ObjectPool()
{
}


ObjectPool::~ObjectPool()
{
}

void ObjectPool::Update()
{
	static iMap* terrain;
	if (terrain == NULL)
		terrain = (iMap*)SearchChild(Tag::Tag_Map);

	for(int i = 0; i< vecObjectList.size(); ++i)
	{
		if (terrain != NULL && 
			(vecObjectList[i]->GetTag() >= Tag::Tag_Player ))
		{
			D3DXVECTOR3 pos = vecObjectList[i]->GetPos();
			float h = terrain->getHeight(pos);
			pos.y = h;
			vecObjectList[i]->SetPos(pos);
		}
		vecObjectList.at(i)->Update();
	}


	for (int i = 0; i < vecObjectList.size(); ++i)
	{

	}

	std::vector<cObject*>::iterator it;
	it = vecObjectList.begin();

	for (; it != vecObjectList.end();)
	{
		if ((*it)->m_isDelete)
			it = vecObjectList.erase(it);
		else
			++it;
	}

}

void ObjectPool::Render(D3DXMATRIXA16* pmat)
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	if(pmat)
	{
		matWorld *= *pmat;
	}

	for(int i = 0 ; i < vecObjectList.size(); i++)
	{
		vecObjectList.at(i)->Render(NULL);
	}

	g_pTimeManager->DrawFPS();

	for(int i = 0; i < vecUserInterface.size(); i++)
	{
		vecUserInterface.at(i)->Render(NULL);
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void ObjectPool::AddChild(cObject* obj)
{
	vecObjectList.push_back(obj);
	++m_nRefcnt;
}

void ObjectPool::AddStaticChild(cObject* obj)
{
	if(m_nRefcnt > 0)
	{
		int SwapIndex = vecObjectList.size() - m_nRefcnt;
		
		vecObjectList.resize(vecObjectList.size() + 1);

		vecObjectList[vecObjectList.size() - 1] = vecObjectList[SwapIndex];
		vecObjectList[SwapIndex] = NULL;
		vecObjectList[SwapIndex] = obj;
	}
	else
	{
		vecObjectList.push_back(obj);
	}

}

void ObjectPool::Revert()
{
	int nRevertSize = vecObjectList.size() - m_nRefcnt;

	std::vector<cObject*> vecNewList;
	vecNewList.resize(nRevertSize);

	for(int i =0; i < nRevertSize; ++i)
	{
		vecNewList.at(i) = vecObjectList.at(i);
	}

	vecObjectList.swap(vecNewList);
	m_nRefcnt = 0;

	//Detech를 해줘야한다
	// 현재 수정해야하는곳
	/*
	 for(int i = 0; i < vecUserInterface.size(); i++)
	{
		cPopup* popup = (cPopup*)vecUserInterface[i];
		popup->Destroy();
	}
	 

	std::vector<cObject*> vecNewUIList;
	vecUserInterface.swap(vecNewUIList);
	*/
	//

	return;
}

/*
void ObjectPool::Revert(int curSceneType, int SceneType)
{
	int nRevertSize = vecObjectList.size() - m_nRefcnt;

	std::vector<cObject*> vecNewList;
	vecNewList.resize(nRevertSize);

	for (int i = 0; i < nRevertSize; ++i)
	{
		vecNewList.at(i) = vecObjectList.at(i);
	}

	vecObjectList.swap(vecNewList);
	m_nRefcnt = 0;



	
	cPopup* popup =(cPopup*) ObjectManager->SearchChildUI(curSceneType);
	if (popup != NULL) 
	{
		popup->PowerOnOff();
	}

	object = ObjectManager->SearchChildUI(SceneType);
	popup = (cPopup*)object;
	popup->PowerOnOff();
	
}
*/

const cObject* ObjectPool::GetChild(int nIndex)
{
	if (nIndex < vecObjectList.size())
		return vecObjectList[nIndex];
	else
		return NULL;
}

void ObjectPool::AddUIChild(cObject* obj)
{
	vecUserInterface.push_back(obj);
}

void ObjectPool::RemoveUIChild(cObject& obj)
{
	vecUserInterface.erase(remove(vecUserInterface.begin(),
		vecUserInterface.end(), &obj));
}

const cObject * ObjectPool::GetUI(int Tag)
{
	for(int i = 0;  i < vecUserInterface.size(); ++i)
	{
		if (vecUserInterface.at(i)->GetTag() == Tag)
			return vecUserInterface.at(i);
	}
	
	return NULL;
}

const cObject* ObjectPool::SearchChild(int nTag)
{
	int i = 0;
	if (vecObjectList.empty()) return NULL;

	while (vecObjectList.at(i)->GetTag() != nTag)
	{
		++i;

		if (vecObjectList.size() <= i)
		{
			return NULL;
		}
	}

	return vecObjectList.at(i);
}

const cObject * ObjectPool::SearchChildUI(int nTag)
{
	int i = 0;
	if (vecUserInterface.empty()) return NULL;

	while (vecUserInterface.at(i)->GetTag() != nTag)
	{
		++i;

		if (vecUserInterface.size() <= i)
		{
			return NULL;
		}
	}

	return vecUserInterface.at(i);
}

void ObjectPool::CollisionDetection()
{

	for (int i = 0; i < vecObjectList.size(); ++i)
	{
		if (vecObjectList.at(i)->GetOBB() == NULL)
			continue;

		for (int j = i + 1; j < vecObjectList.size(); ++j)
		{
			if (vecObjectList.at(j)->GetOBB() == NULL)
				continue;
			
			if (cOBB::IsCollision(vecObjectList.at(i)->GetOBB(),
				vecObjectList.at(j)->GetOBB()))
			{
				// 수치 계산
				vecObjectList.at(i)->CollisionProcess(vecObjectList.at(j),
					vecObjectList.at(j)->GetTag(), 1500.0f);

				vecObjectList.at(j)->CollisionProcess(vecObjectList.at(i),
					vecObjectList.at(j)->GetTag(), 1500.0f);

			}

		}

	}

}

void ObjectPool::RemoveChild(cObject& obj)
{
	int nOrginalSize = vecObjectList.size();

	vecObjectList.erase(remove(vecObjectList.begin(),
		vecObjectList.end(), &obj));

	m_nRefcnt -= (nOrginalSize - vecObjectList.size());

}
