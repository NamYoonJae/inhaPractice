#include "stdafx.h"
#include "TimerManager.h"
#include "ObjectPool.h"
#include "EventManager.h"

ObjectPool::ObjectPool()
{
}


ObjectPool::~ObjectPool()
{
}

void ObjectPool::Update()
{
	for(int i = 0; i< vecObjectList.size(); i++)
	{
		vecObjectList.at(i)->Update();
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
		vecObjectList.at(i)->Render(&matWorld);
	}

	g_pTimeManager->DrawFPS();

	for(int i = 0; i < vecUserInterface.size(); i++)
	{
		vecUserInterface.at(i)->Render(&matWorld);
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
	for(int i = 0; i < vecUserInterface.size(); i++)
	{
		cPopUp* popup = (cPopUp*)vecUserInterface[i];
		popup->Destroy();
	}
	
	std::vector<cObject*> vecNewUIList;
	vecUserInterface.swap(vecNewUIList);
	
	return;
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

const cObject* ObjectPool::SearchChild(int nTag)
{
	int i = 0;
	while(vecObjectList.at(i)->GetTag() != nTag)
	{
		++i;

		if(vecObjectList.size() <= i)
		{
			return NULL;
		}
	}

	return vecObjectList.at(i);

}

void ObjectPool::RemoveChild(cObject& obj)
{
	int nOrginalSize = vecObjectList.size();

	vecObjectList.erase(remove(vecObjectList.begin(),
		vecObjectList.end(), &obj));

	m_nRefcnt -= (nOrginalSize - vecObjectList.size());

}
