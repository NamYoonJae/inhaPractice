#include "StdAfx.h"
#include "SkinnedMesh.h"
#include "SkinnedMeshManager.h"

cSkinnedMeshManager::cSkinnedMeshManager(void)
{
}


cSkinnedMeshManager::~cSkinnedMeshManager(void)
{
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SafeDelete(it.second);
	}
}

cSkinnedMesh* cSkinnedMeshManager::GetSkinnedMesh( char* szFolder, char* szFileName)
{
	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFileName);

	if(m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFileName);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
		m_mapAnimCtrl[sFullPath] = pSkinnedMesh->GetAnimationController();
	}
	return m_mapSkinnedMesh[sFullPath];
}

LPD3DXANIMATIONCONTROLLER cSkinnedMeshManager::GetAnimController(char* szFolder, char* szFileName)
{
	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFileName);

	if(m_mapAnimCtrl.find(sFullPath) == m_mapAnimCtrl.end())
	{
		GetSkinnedMesh(szFolder, szFileName);
	}
	return m_mapAnimCtrl[sFullPath];
}
