#include "stdafx.h"
#include "BackViewCamera.h"
#include "cCharater.h"
#include "EventManager.h"
#include "jsonManager.h"
#include "Map.h"
#include "ObjectPool.h"
#pragma once


cBackViewCamera::cBackViewCamera()
	: m_vEye(0, 0, 0)
	, m_vOffset(0, 30, 150)
	, m_vLookAt(0, 0, 0)
	, m_vUp(D3DXVECTOR3(0, 1, 0))
	, m_ptPrevMouse(0, 0)
	, m_vCamRotAngle(0, 0, 0)
	, m_fVibrationValue(2.0f)
	, m_fScrollY(0.0f)
	, m_IsVibration(false)
	, m_IsUpdate(true)
	, m_IsRBDOWN(false)
{
}

cBackViewCamera::~cBackViewCamera()
{

}



void cBackViewCamera::Setup(cCharater* pPlayer)
{
	if (pPlayer)
		m_pPlayer = pPlayer;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 2000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);



}


void cBackViewCamera::Update()
{
	if (!m_IsUpdate) return;

	D3DXMATRIXA16 matW,matR, matRX, matRy;
	D3DXMatrixRotationY(&matRy, m_vCamRotAngle.y);
	matW = matR = matRy;

	m_vEye = m_vOffset;

	if (m_pPlayer)
	{
		DirectionCalculation();
		m_pPlayer->SetCameraDir(m_vDir);
		m_pPlayer->SetCameraRot(m_vCamRotAngle);
		D3DXVECTOR3 pos = m_pPlayer->GetPosition();
		pos.y += 10.0f;
		m_vLookAt = pos;
		m_vEye += pos;


		D3DXMATRIXA16 matT;
		
		D3DXMatrixTranslation(&matT, m_vLookAt.x, m_vLookAt.y, m_vLookAt.z);
		matW = matR * matT;
		
	}

	D3DXVec3TransformCoord(&m_vEye, &m_vOffset, &matW);
	m_vLookAt.y += m_vOffset.y;
	if (m_IsVibration)
	{
		m_vLookAt.y += m_fVibrationValue;
		m_fVibrationValue = -m_fVibrationValue;
	}
	else
	{
		m_vLookAt.y += m_fScrollY;
	}

	iMap* pMap = (iMap*)ObjectManager->SearchChild(Tag::Tag_Map);
	if(pMap)
	{
		D3DXVECTOR3 vPrevEye = m_vEye;
		float y = pMap->getHeight(m_vEye);
		if(y <= 0.0f || y >= 21.0f)
		{
			D3DXVECTOR3 vDir = m_vLookAt - m_vEye;
			D3DXVec3Normalize(&vDir, &vDir);
			while(true)
			{
				m_vEye += vDir * 3.0f;
				
				y = pMap->getHeight(m_vEye);
				
				if( y < 21.0f && y > 0.0f)
				{
					break;
				}
				if (sqrt(pow(m_vEye.x - (m_vLookAt).x, 2) + pow(m_vEye.z - (m_vLookAt).z, 2)) <= 3.0f)
				{
					m_vEye = vPrevEye;
					break;
				}
			}
		}
	}

	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

 void cBackViewCamera::GetTarget(cCharater* pPlayer)
 {
	 m_pPlayer = pPlayer;	
 }


 void cBackViewCamera::DirectionCalculation()
{

	D3DXVECTOR3 vPlayerPos, vEye;
	D3DXVECTOR3 vDir;
	D3DXMATRIXA16 matSy;
	D3DXMatrixRotationY(&matSy, m_vCamRotAngle.y);


	vPlayerPos = m_pPlayer->GetPosition();
	
	vEye = vPlayerPos + m_vOffset;
	D3DXVec3TransformCoord(&vEye, &vEye, &matSy);
	
	vDir = vPlayerPos - vEye;
	vDir.y = 0;
	D3DXVec3Normalize(&vDir, &vDir);

	m_vDir = vDir;
	
}

 void cBackViewCamera::Update(EventType Event)
 {
	 if (!m_IsUpdate) return;

	 if (Event == EventType::EVENT_RBUTTONDOWN)
	 {
		 m_ptPrevMouse = EventManager->GetMouseCurrent();
		 m_IsRBDOWN = true;
	 }

	 if(Event == EventType::EVENT_MOVE && m_IsRBDOWN)
	 {
		 D3DXVECTOR2 ptCurMouse = EventManager->GetMouseCurrent();

		 float fDeltaX = (float)(ptCurMouse.x - m_ptPrevMouse.x);
		 float fDeltaY = (float)(ptCurMouse.y - m_ptPrevMouse.y);
		 
		 m_fScrollY -= fDeltaY * 0.1f;
		 
		 JSON_Object* p_mouseSensitivity = g_p_jsonManager->get_json_object_Setting();
		 m_vCamRotAngle.y += fDeltaX * D3DX_PI * 0.0001
			 * json_Function::object_get_double(p_mouseSensitivity, "Mouse sensitivity/total")
			 * json_Function::object_get_double(p_mouseSensitivity, "Mouse sensitivity/normal") * 0.01;

		 m_ptPrevMouse = ptCurMouse;
	 }

	 if (Event == EventType::EVENT_RDRAG)
	 {
		 m_IsRBDOWN = false;

	 }

	 return;
 }
