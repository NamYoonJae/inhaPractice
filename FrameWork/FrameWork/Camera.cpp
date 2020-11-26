#include "stdafx.h"
#include "TimerManager.h"
#include "Camera.h"
#include "EventManager.h"



cCamera::cCamera()
	: m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_pvTarget(NULL)
	, m_fCameraDistance(5.0f)
	, m_isLccButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_ptPrevMouse(0, 0)
	, m_vOriginEye(0, 50, -5)
{
}


cCamera::~cCamera()
{
}

void cCamera::Setup(D3DXVECTOR3 * pvTarget)
{
	m_pvTarget = pvTarget;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(m_vOriginEye.x, m_vOriginEye.y, m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
	
	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye += *m_pvTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::Update(EventType event)
{
	if(event == EventType::EVENT_LBUTTONDOWN)
	{
		m_isLccButtonDown = true;
		m_ptPrevMouse = EventManager->GetMouseCurrent();
	}
	if(event == EventType::EVENT_LBUTTONUP)
	{
		m_isLccButtonDown = false;
	}
	
	if(m_isLccButtonDown && event == EventType::EVENT_MOVE)
	{
		D3DXVECTOR2 vCurMouse = EventManager->GetMouseCurrent();
		
		float fDeltaX = vCurMouse.x - m_ptPrevMouse.x;
		float fDeltaY = vCurMouse.y - m_ptPrevMouse.y;
		
		m_vCamRotAngle.y += fDeltaX * 10.0f * g_pTimeManager->GetElapsedTime();
		m_vCamRotAngle.x += fDeltaY * 10.0f * g_pTimeManager->GetElapsedTime();

		if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
			m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
		
		if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
			m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

		m_ptPrevMouse = vCurMouse;
	}
	
	if(event == EventType::EVENT_WHEELUP)
	{
		m_fCameraDistance -= 1.0f;

		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
	}
	else if (event == EventType::EVENT_WHEELDOWN)
	{
		m_fCameraDistance += 1.0f;
	}
	
}