#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;
	std::map<std::string, LPD3DXANIMATIONCONTROLLER> m_mapAnimCtrl;
public:
	Singletone(cSkinnedMeshManager);

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFileName);
	LPD3DXANIMATIONCONTROLLER GetAnimController(char* szFolder, char* szFileName);
	
	void Destroy();
};

