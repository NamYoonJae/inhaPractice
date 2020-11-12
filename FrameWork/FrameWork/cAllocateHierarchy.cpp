#include "StdAfx.h"
#include "cAllocateHierarchy.h"

#include "TextureManager.h"


cAllocateHierarchy::cAllocateHierarchy(void)
	: m_sDirectory("")
	, m_dwDefaultPaletteSize(0)
	, m_dwMaxPaletteSize(0)
	, m_vMin(0, 0, 0)
	, m_vMax(0, 0, 0)
{
}


cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame )
{
	ST_BONE* pBone = new ST_BONE;

	pBone->Name = NULL;
	if(Name)
	{
		int nLen = strlen(Name) + 1;
		pBone->Name = new char[nLen];
		strcpy(pBone->Name, Name);
	}

	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling	= NULL;
	pBone->pMeshContainer	= NULL;

	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer( THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	assert(pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH);

	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;

	pBoneMesh->Name = NULL;

	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		pBoneMesh->vecMaterial.push_back(pMaterials[i].MatD3D);
		std::string sFilename;
		
		if (pMaterials[i].pTextureFilename)
			sFilename = pMaterials[i].pTextureFilename;
		
		std::string sFullPath = m_sDirectory + sFilename;
		LPDIRECT3DTEXTURE9 pTex = g_pTextureManager->GetTexture(sFullPath);
		pBoneMesh->vecTexture.push_back(pTex);
	}

	pBoneMesh->pEffects = NULL;

	if(pAdjacency)
	{
		DWORD dwNumFaces = pMeshData->pMesh->GetNumFaces();
		pBoneMesh->pAdjacency = new DWORD[ 3 * dwNumFaces ];
		memcpy( pBoneMesh->pAdjacency, pAdjacency, 3 * sizeof( DWORD ) * dwNumFaces );
	}
	
	if (pSkinInfo)
		pSkinInfo->AddRef();
	
	pBoneMesh->pSkinInfo = pSkinInfo;


	if (pMeshData && pMeshData->pMesh)
	{
		/// >> : OBB
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
		} /// << : 
		
		pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF(),
			g_pD3DDevice,
			&pBoneMesh->pOrigMesh);
	}

	if(pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIXA16*[dwNumBones];
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIXA16[dwNumBones];
		for (DWORD i = 0; i < dwNumBones; ++i)
		{
			pBoneMesh->ppBoneMatrixPtrs[i] = NULL;
			pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		}
		pBoneMesh->dwNumPaletteEntries = min( m_dwDefaultPaletteSize, pSkinInfo->GetNumBones() );
		if(m_dwMaxPaletteSize < pBoneMesh->dwNumPaletteEntries)
		{
			m_dwMaxPaletteSize = pBoneMesh->dwNumPaletteEntries;
		}
		pBoneMesh->pSkinInfo->ConvertToIndexedBlendedMesh(
			pBoneMesh->pOrigMesh,
			D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
			pBoneMesh->dwNumPaletteEntries,
			pBoneMesh->pAdjacency,
			NULL,
			NULL,
			NULL,
			&pBoneMesh->dwMaxNumFaceInfls,
			&pBoneMesh->dwNumAttrGroups,
			&pBoneMesh->pBufBoneCombos,
			&pBoneMesh->pWorkingMesh );

		DWORD dwOldFVF = pBoneMesh->pWorkingMesh->GetFVF();
		DWORD dwNewFVF = 
			( dwOldFVF & D3DFVF_POSITION_MASK ) |
			D3DFVF_NORMAL |
			D3DFVF_TEX1 |
			D3DFVF_LASTBETA_UBYTE4;

		if( dwNewFVF != dwOldFVF )
		{
			LPD3DXMESH pMesh = NULL;

			pBoneMesh->pWorkingMesh->CloneMeshFVF(
				pBoneMesh->pWorkingMesh->GetOptions(),
				dwNewFVF,
				g_pD3DDevice,
				&pMesh );

			SafeRelease(pBoneMesh->pWorkingMesh);
			pBoneMesh->pWorkingMesh = pMesh;

			if( ! ( dwOldFVF & D3DFVF_NORMAL ) )
			{
				D3DXComputeNormals( pBoneMesh->pWorkingMesh, NULL );
			}
		}
		D3DVERTEXELEMENT9 pDecl[ MAX_FVF_DECL_SIZE ];
		D3DVERTEXELEMENT9 * pDeclCur;
		pBoneMesh->pWorkingMesh->GetDeclaration( pDecl );

		pDeclCur = pDecl;
		while( pDeclCur->Stream != 0xff )
		{
			if( ( pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES ) &&
				( pDeclCur->UsageIndex == 0 ) )
				pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
			pDeclCur++;
		}

		pBoneMesh->pWorkingMesh->UpdateSemantics( pDecl );
	}
	
	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame( THIS_ LPD3DXFRAME pFrameToFree )
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;
	SafeDeleteArray(pBone->Name);
	delete pFrameToFree;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	
	SafeRelease(pBoneMesh->pSkinInfo);
	SafeRelease(pBoneMesh->pWorkingMesh);
	SafeRelease(pBoneMesh->pOrigMesh);
	SafeRelease(pBoneMesh->pBufBoneCombos);

	SafeDeleteArray(pBoneMesh->Name);
	SafeDeleteArray(pBoneMesh->pAdjacency);
	SafeDeleteArray(pBoneMesh->ppBoneMatrixPtrs);
	SafeDeleteArray(pBoneMesh->pBoneOffsetMatrices);
	
	SafeDelete(pMeshContainerToFree);

	return S_OK;
}
