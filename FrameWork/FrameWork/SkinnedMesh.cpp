#include "stdafx.h"
#include "AllocateHierarchy.h"
#include "TimerManager.h"
#include "SkinnedMeshManager.h"

#include "SkinnedMesh.h"


cSkinnedMesh::cSkinnedMesh()
	:m_pRoot(NULL)
	,m_pAnimController(NULL)
, m_isAnimBlend(false)
, m_fPassedBlendTime(0.0f)
, m_fBlendTime(0.3f)
, m_dAnimStartTime(0)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	//D3DXFrameDestroy(m_pRoot, &ah);
	SafeRelease(m_pAnimController);
}

void cSkinnedMesh::Setup(char * szFolder, char * szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + string("/") + string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	D3DXLoadMeshHierarchyFromXA(sFullPath.c_str(), D3DXMESH_MANAGED, g_pD3DDevice, &ah, NULL ,&m_pRoot, &m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Update()
{	
	if(m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if(m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
			//m_pAnimController->SetTrackWeight(1, 0.0f);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	m_pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
	
	if(GetTickCount() - m_dAnimStartTime > GetTickCount() + pCurAnimSet->GetPeriod())
	{
		//SetAnimationIndexBlend(4);
	}

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	Update((ST_BONE*)m_pRoot, &m_matWorldTM);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	if (pParent) 
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild) 
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling) 
	{
		Update(pFrame->pFrameSibling, pParent);
	}

}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			// 본 기준 행렬정렬 제거(임시)
			//g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i) 
			{
				if(!pBoneMesh->vecTexture.empty())
				{
					g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
					g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				}
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
				g_pD3DDevice->SetTexture(0, NULL);
			}
		}
	}
	if (pFrame->pFrameFirstChild)
		Render(pFrame->pFrameFirstChild);
	if (pFrame->pFrameSibling)
		Render(pFrame->pFrameSibling);

}

void cSkinnedMesh::Render(D3DXMATRIXA16 * pmat)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	Render(LPD3DXFRAME(NULL));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo) 
		{
			DWORD dwNumBones = pBoneMesh->pSkinInfo->GetNumBones();
			
			for (DWORD i = 0; i < dwNumBones; i++) 
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pBoneMesh->pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombinedTransformationMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i) 
			{
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);

		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();

	}


	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);

}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	//m_pAnimController->GetPriorityBlend();
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);

	m_dAnimStartTime = GetTickCount();
	
	SafeRelease(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isAnimBlend = true;
	m_fPassedBlendTime = 0.0f;

	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);

	// 진행되고 있던 애니메이션의 정보를 받아와 1번 트랙으로 옮김
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	// 새로운 애니메이션의 정보를 0번 트랙에 받아옴
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f);

	// 가중치 설정
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	m_dAnimStartTime = GetTickCount();

	SafeRelease(pPrevAnimSet);
	SafeRelease(pNextAnimSet);
}

LPD3DXANIMATIONCONTROLLER cSkinnedMesh::GetAnimationController()
{
	return m_pAnimController;
}

cSkinnedMesh::cSkinnedMesh(char* szFolder, char* szFileName)
	:m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_isAnimBlend(false)
	, m_fPassedBlendTime(0.0f)
	, m_fBlendTime(0.3f)
	, m_dAnimStartTime(0)
	, m_vMin(0, 0, 0)
	, m_vMax(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorldTM);
	cSkinnedMesh* pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFileName);

	m_pRoot = pSkinnedMesh->m_pRoot;
	
	m_vMin = pSkinnedMesh->m_vMin;
	m_vMax = pSkinnedMesh->m_vMax;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
}

void cSkinnedMesh::Load(char* szFolder, char* szFileName)
{
	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFileName);

	D3DXLoadMeshHierarchyFromXA(sFullPath.c_str(), D3DXMESH_MANAGED, g_pD3DDevice, &ah, 
		NULL, &m_pRoot, &m_pAnimController);

	m_vMin = ah.GetMin();
	m_vMax = ah.GetMax();

	//cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh;
	//if(m_pRoot)
	//{
	//	pSkinnedMesh->SetupBoneMatrixPtrs(m_pRoot);
	//}

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRoot, &ah);
}

void cSkinnedMesh::UpdateAndRender()
{
	if (m_pAnimController)
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);

	if(m_pRoot)
	{
		Update((ST_BONE*)m_pRoot, &m_matWorldTM);
		Render(m_pRoot);
	}
}

void cSkinnedMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	if(pCurrent == NULL)
	{
		pCurrent = (ST_BONE*)m_pRoot;
	}

	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;

	if(pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);

	if (pCurrent->pFrameFirstChild)
		Update((ST_BONE*)pCurrent->pFrameFirstChild,
			&(pCurrent->CombinedTransformationMatrix));
}

void cSkinnedMesh::SetRandomTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}

void cSkinnedMesh::SetTransform(D3DXMATRIXA16* pmat)
{
	m_matWorldTM = *pmat;
}
