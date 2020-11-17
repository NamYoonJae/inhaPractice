#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;

public:
	Singletone(cSkinnedMeshManager);

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFileName);
	
	void Destroy();
};

