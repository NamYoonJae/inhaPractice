#include "stdafx.h"
#include "TextureManager.h"
#include "DragonSoulEater.h"
#include "SoulEaterState.h"
#include "cOBB.h"
#include "AllocateHierarchy.h"
DragonSoulEater::DragonSoulEater()
	:m_pSkinnedUnit(NULL)
	,m_pCurState(NULL)
{
	m_pOBB = NULL;
}


DragonSoulEater::~DragonSoulEater()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
}

void DragonSoulEater::Update()
{
	// �÷��̾�� ���
	// ���¿� ���� ������Ʈ


	// �г�� ���� ���¸� ������ �ٲ���ϴ� ��� �ڽ��� ���¸� �ٲ��ش�.
	{
		//SetState()
	}
	
	m_pSkinnedUnit->Update();

	D3DXMATRIXA16 matOBB,matT,matRy;
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	// -15 ���ָ� ���� ����
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z - 15);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2, 0.2, 0.2);
	matOBB = matRy * matT;

	m_pOBB->Update(&matOBB);
	
	
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matOBB = matS * matRy * matT;

	for (int i = 0; i < m_vecBoundingBoxList.size(); ++i)
		m_vecBoundingBoxList.at(i)->Update(&matOBB);
	//if(m_pCurState)
	//{
	//	m_pCurState->Update();
	//}

}

void DragonSoulEater::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT,
	matR, matRx,matRy,matRz;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matRx,m_vRot.x);
	D3DXMatrixRotationY(&matRy,m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);
	matR = matRx * matRy * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	matWorld = matR * matT;
	m_pTexture = g_pTextureManager->GetTexture("data/XFile/Dragon/BlueHP.png");
	g_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	
	//ZeroMemory(&m_Mstl, sizeof(D3DXMATRIXA16));
//	g_pD3DDevice->SetMaterial(&m_Mstl);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedUnit->Render();
	g_pD3DDevice->SetMaterial(&m_Mstl);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pOBB->OBBBOX_Render(D3DXCOLOR(0,1.0f,0,1.0f));

	for (int i = 0; i < m_vecBoundingBoxList.size(); i++)
		m_vecBoundingBoxList.at(i)->OBBBOX_Render(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	
}

void DragonSoulEater::Setup(char* szFolder, char* szFileName)
{
	m_pSkinnedUnit = new cSkinnedMesh(szFolder, szFileName);
	m_pOBB = new cOBB;

	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, 0.2, 0.2, 0.2);

	m_pSkinnedUnit->Update();

	if (m_pSkinnedUnit->m_pCurrentBoneMatrices)
		mat *= *m_pSkinnedUnit->m_pCurrentBoneMatrices;

	m_pOBB->Setup(m_pSkinnedUnit, &mat);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vecSize;
	D3DXVECTOR3 vecJointOffset;

	LPD3DXFRAME pFrame = m_pSkinnedUnit->GetFrame();
	GetBoundingBoxSize(pFrame,
		pFrame->pMeshContainer,
		&vecSize,
		&vecJointOffset);

	BuildBoneData(0, pFrame, pFrame->pMeshContainer);


	SetupBoundingBox();
}

void DragonSoulEater::SetState()
{
	if(true)
	{
		// ���������� ���°� ��ȭ�ؾ��Ҷ� �г��� ������ ��ȭ
	}
	else if(true)
	{
		
	}
	else
	{
		// ������ ���Ѵ�.
	}
}

void DragonSoulEater::GetWorldMatrix(D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
}

void DragonSoulEater::SetupBoundingBox()
{
	if (m_vBoneArray.empty())
		return;

	std::vector<ST_PC_VERTEX> Body, Tail,
		UpperLeg_R, UpperLeg_L,
		LowerLeg_R, LowerLeg_L,
		Wing_R, Wing_L;


	ST_BONE* pBone;

	D3DXMATRIXA16 mat;

	for (int i = 0; i < m_vBoneArray.size(); ++i)
	{
		string szName = m_vBoneArray.at(i)->szName;

		pBone = (ST_BONE*)D3DXFrameFind(m_pSkinnedUnit->GetFrame(), szName.c_str());
		mat = pBone->CombinedTransformationMatrix;
		ST_PC_VERTEX Vertex;
		Vertex.c = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		if (STRCMP(&szName[0], "Spine") ||
			STRCMP(&szName[0], "Chest") ||
			//STRCMP(&szName[0], "ValleyFat") ||
			STRCMP(&szName[0], "Neck") ||
			STRCMP(&szName[0], "Head") ||
			STRCMP(&szName[0], "NeckFat_Left") ||
			STRCMP(&szName[0], "UpperMouth") ||
			STRCMP(&szName[0], "Jaw") ||
			STRCMP(&szName[0], "Eye_Left") ||
			STRCMP(&szName[0], "Eye_Right") ||
			STRCMP(&szName[0], "JawTip"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{

				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Body.push_back(Vertex);
			}

		}
		else if (STRCMP(&szName[0], "Tail01") ||
			STRCMP(&szName[0], "Tail02") ||
			STRCMP(&szName[0], "Tail03") ||
			STRCMP(&szName[0], "TailEnd"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Tail.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0], "UpperLeg_Right") ||
			STRCMP(&szName[0], "UpperArm_Right"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				UpperLeg_R.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0], "UpperLeg_Left") ||
			STRCMP(&szName[0], "UpperArm_Left"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				UpperLeg_L.push_back(Vertex);
			}
		}
		else if (szName[0] == 'W' && szName[szName.size() - 4] == 'L')
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Wing_L.push_back(Vertex);
			}
		}
		else if (szName[0] == 'W' && szName[szName.size() - 5] == 'R')
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Wing_R.push_back(Vertex);
			}
		}
		else if (szName[0] == 'L' && szName[szName.size() - 4] == 'L' ||
			(STRCMP(&szName[0], "Feet_Left")) ||
			(STRCMP(&szName[0], "Toe_Left")) ||
			(STRCMP(&szName[0], "ReverseLeg_Left")))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				LowerLeg_L.push_back(Vertex);
			}
		}
		else if (szName[0] == 'L'  && szName[szName.size() - 5] == 'R' ||
			(STRCMP(&szName[0], "Feet_Right")) ||
			(STRCMP(&szName[0], "Toe_Right")) ||
			(STRCMP(&szName[0], "ReverseLeg_Right")))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				LowerLeg_R.push_back(Vertex);
			}
		}
	}

	std::vector<cOBB*> vecOBBList;
	D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
	D3DXMATRIXA16 matS, matT, matW;
	//body
	{

		cOBB* BodyOBB = new cOBB;

		for (int i = 0; i < Body.size(); ++i)
		{
			vMin.x = min(vMin.x, Body.at(i).p.x);
			vMin.y = min(vMin.y, Body.at(i).p.y);
			vMin.z = min(vMin.z, Body.at(i).p.z);

			vMax.x = max(vMax.x, Body.at(i).p.x);
			vMax.y = max(vMax.y, Body.at(i).p.y);
			vMax.z = max(vMax.z, Body.at(i).p.z);
		}

		BodyOBB->Setup(vMin, vMax);
		vecOBBList.push_back(BodyOBB);
	}
	//Tail
	{
		cOBB* TailOBB = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Tail.size(); ++i)
		{
			vMin.x = min(vMin.x, Tail.at(i).p.x);
			vMin.y = min(vMin.y, Tail.at(i).p.y);
			vMin.z = min(vMin.z, Tail.at(i).p.z);

			vMax.x = max(vMax.x, Tail.at(i).p.x);
			vMax.y = max(vMax.y, Tail.at(i).p.y);
			vMax.z = max(vMax.z, Tail.at(i).p.z);
		}


		TailOBB->Setup(vMin, vMax);

		vecOBBList.push_back(TailOBB);
	}

	//UpperLeg_Right
	{
		cOBB* UpperLegR = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < UpperLeg_R.size(); ++i)
		{
			vMin.x = min(vMin.x, UpperLeg_R.at(i).p.x);
			vMin.y = min(vMin.y, UpperLeg_R.at(i).p.y);
			vMin.z = min(vMin.z, UpperLeg_R.at(i).p.z);

			vMax.x = max(vMax.x, UpperLeg_R.at(i).p.x);
			vMax.y = max(vMax.y, UpperLeg_R.at(i).p.y);
			vMax.z = max(vMax.z, UpperLeg_R.at(i).p.z);
		}

		D3DXMatrixScaling(&matS, 1, 1, 0.7);
		D3DXMatrixTranslation(&matT, 0, 0, -(vMax.z - vMin.z) * 0.5);

		matW = matS * matT;
		UpperLegR->Setup(vMin, vMax, &matW);
		vecOBBList.push_back(UpperLegR);


		//lower
		D3DXMatrixTranslation(&matT, 0, 0, (vMax.z - vMin.z) * 0.5);
		cOBB* LowerLegR = new cOBB;
		matW = matS * matT;
		LowerLegR->Setup(vMin, vMax, &matW);
		vecOBBList.push_back(LowerLegR);
	}
	//UpperLeg_Left
	{
		cOBB* UpperLegL = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < UpperLeg_L.size(); ++i)
		{
			vMin.x = min(vMin.x, UpperLeg_L.at(i).p.x);
			vMin.y = min(vMin.y, UpperLeg_L.at(i).p.y);
			vMin.z = min(vMin.z, UpperLeg_L.at(i).p.z);

			vMax.x = max(vMax.x, UpperLeg_L.at(i).p.x);
			vMax.y = max(vMax.y, UpperLeg_L.at(i).p.y);
			vMax.z = max(vMax.z, UpperLeg_L.at(i).p.z);
		}
		D3DXMatrixScaling(&matS, 1, 1, 0.7);
		D3DXMatrixTranslation(&matT, 0, 0, -(vMax.z - vMin.z) * 0.5);

		matW = matS * matT;

		UpperLegL->Setup(vMin, vMax, &matW);

		vecOBBList.push_back(UpperLegL);

		// lower
		D3DXMatrixTranslation(&matT, 0, 0, (vMax.z - vMin.z) * 0.5);
		cOBB* LowerLegL = new cOBB;
		matW = matS * matT;
		LowerLegL->Setup(vMin, vMax, &matW);
		vecOBBList.push_back(LowerLegL);

	}



	////LowerLeg_Right
	//{
	//	cOBB* LowerLegR = new cOBB;
	//	vMax = vMin = D3DXVECTOR3(0, 0, 0);

	//	for (int i = 0; i < LowerLeg_R.size(); ++i)
	//	{
	//		vMin.x = min(vMin.x, LowerLeg_R.at(i).p.x);
	//		vMin.y = min(vMin.y, LowerLeg_R.at(i).p.y);
	//		vMin.z = min(vMin.z, LowerLeg_R.at(i).p.z);

	//		vMax.x = max(vMax.x, LowerLeg_R.at(i).p.x);
	//		vMax.y = max(vMax.y, LowerLeg_R.at(i).p.y);
	//		vMax.z = max(vMax.z, LowerLeg_R.at(i).p.z);
	//	}

	//	LowerLegR->Setup(vMin, vMax);
	//	
	//	vecOBBList.push_back(LowerLegR);
	//}
	////LowerLeg_Left
	//{
	//	cOBB* LowerLegL = new cOBB;
	//	vMax = vMin = D3DXVECTOR3(0, 0, 0);

	//	for (int i = 0; i < LowerLeg_L.size(); ++i)
	//	{
	//		vMin.x = min(vMin.x, LowerLeg_L.at(i).p.x);
	//		vMin.y = min(vMin.y, LowerLeg_L.at(i).p.y);
	//		vMin.z = min(vMin.z, LowerLeg_L.at(i).p.z);

	//		vMax.x = max(vMax.x, LowerLeg_L.at(i).p.x);
	//		vMax.y = max(vMax.y, LowerLeg_L.at(i).p.y);
	//		vMax.z = max(vMax.z, LowerLeg_L.at(i).p.z);
	//	}

	//	LowerLegL->Setup(vMin, vMax);
	//	
	//	vecOBBList.push_back(LowerLegL);
	//}
	//Wing_Right
	{
		cOBB* WingR = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Wing_R.size(); ++i)
		{
			vMin.x = min(vMin.x, Wing_R.at(i).p.x);
			vMin.y = min(vMin.y, Wing_R.at(i).p.y);
			vMin.z = min(vMin.z, Wing_R.at(i).p.z);

			vMax.x = max(vMax.x, Wing_R.at(i).p.x);
			vMax.y = max(vMax.y, Wing_R.at(i).p.y);
			vMax.z = max(vMax.z, Wing_R.at(i).p.z);
		}

		D3DXMATRIXA16 matS, matT, matW;
		D3DXMatrixScaling(&matS, 1, 0.3, 1);
		D3DXMatrixTranslation(&matT, 0, (vMax.y - vMin.y) * 0.7, 0);

		matW = matS * matT;

		WingR->Setup(vMin, vMax, &matW);

		vecOBBList.push_back(WingR);
	}
	//Wing_Left
	{
		cOBB* WingL = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Wing_L.size(); ++i)
		{
			vMin.x = min(vMin.x, Wing_L.at(i).p.x);
			vMin.y = min(vMin.y, Wing_L.at(i).p.y);
			vMin.z = min(vMin.z, Wing_L.at(i).p.z);

			vMax.x = max(vMax.x, Wing_L.at(i).p.x);
			vMax.y = max(vMax.y, Wing_L.at(i).p.y);
			vMax.z = max(vMax.z, Wing_L.at(i).p.z);
		}
		D3DXMATRIXA16 matS, matT, matW;
		D3DXMatrixScaling(&matS, 1, 0.3, 1);
		D3DXMatrixTranslation(&matT, 0, (vMax.y - vMin.y) * 0.7, 0);

		matW = matS * matT;

		WingL->Setup(vMin, vMax, &matW);

		vecOBBList.push_back(WingL);
	}

	m_vecBoundingBoxList = vecOBBList;
}
