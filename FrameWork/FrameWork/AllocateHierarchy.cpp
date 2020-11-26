#include "stdafx.h"
#include "basic.h"
#include "TextureManager.h"

#include "AllocateHierarchy.h"


ST_BONE::ST_BONE()
{
	memset(this, 0, sizeof(ST_BONE));
}

cAllocateHierarchy::cAllocateHierarchy()
	:m_vMax(0, 0, 0)
	,m_vMin(0, 0, 0)
{
}


cAllocateHierarchy::~cAllocateHierarchy()
{
}


STDMETHODIMP cAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame) 
{
	ST_BONE* pBone = new ST_BONE;
	ZeroMemory(pBone, sizeof(ST_BONE));
	if (Name)
	{
		pBone->Name = new char[lstrlenA(Name) + 1];
		UINT length = lstrlenA(Name) + 1;
		strcpy_s(pBone->Name, length * sizeof(CHAR), Name);
		cout << pBone->Name << endl;
	}

	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);

	*ppNewFrame = pBone;
	return S_OK;
};

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer(THIS_
	LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	for (DWORD i = 0; i < NumMaterials; ++i) 
	{
		pBoneMesh->vecMtl.push_back(pMaterials[i].MatD3D);
		string sFullPath = m_sFolder;
		if(pMaterials[i].pTextureFilename)
		{
			sFullPath = sFullPath + string("/") + string(pMaterials[i].pTextureFilename);

			pBoneMesh->vecTexture.push_back(g_pTextureManager->GetTexture(sFullPath));
		}
	}

	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;

	pMeshData->pMesh->AddRef();
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;

	// >> : Bounding Box
	if(pMeshData && pMeshData->pMesh)
	{
		D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		LPVOID pV = NULL;
		pMeshData->pMesh->LockVertexBuffer(0, &pV);

		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			pMeshData->pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pMeshData->pMesh->GetFVF()),
			&vMin,
			&vMax);

		D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
		
		pMeshData->pMesh->UnlockVertexBuffer();
	}



	
	pMeshData->pMesh->CloneMeshFVF(
		pMeshData->pMesh->GetOptions(), 
		pMeshData->pMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pOrigMesh
	);

	DWORD dwNumBones = pSkinInfo->GetNumBones();
	pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
	pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
	pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];

	for (DWORD i = 0; i < dwNumBones; ++i) 
	{
		pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;

};

STDMETHODIMP cAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree) 
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;
	SafeDeleteArray(pBone->Name);
	SafeDelete(pFrameToFree);
	return S_OK;


};

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) 
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	SafeRelease(pBoneMesh->pSkinInfo);
	SafeRelease(pBoneMesh->MeshData.pMesh);
	SafeRelease(pBoneMesh->pOrigMesh);

	SafeDeleteArray(pBoneMesh->pCurrentBoneMatrices);
	SafeDeleteArray(pBoneMesh->ppBoneMatrixPtrs);
	SafeDeleteArray(pBoneMesh->pBoneOffsetMatrices);

	SafeDelete(pBoneMesh);
	return S_OK;


};