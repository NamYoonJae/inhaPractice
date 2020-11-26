#include "stdafx.h"
#include "cObject.h"
#include "cOBB.h"

cObject::cObject()
	: m_pOBB(NULL)
	, IsRender(true)
	, m_vRot(0, 0, 0)
	, m_vPos(0, 0, 0)
	, m_vDir(0, 0, -1)
{
}


cObject::~cObject()
{
	SafeDelete(m_pOBB);
}

cOBB * cObject::GetOBB()
{
	return m_pOBB;
}

void cObject::PosInMap(RECT rcVisibleArea)
{
	POINT pt = { m_vPos.x,m_vPos.z };
	IsRender = PtInRect(&rcVisibleArea, pt);

	//if ((rcVisibleArea.left <= m_vPos.x && m_vPos.x <= rcVisibleArea.right)
	//	&& (rcVisibleArea.top <= m_vPos.z && m_vPos.z <= rcVisibleArea.bottom))
	//{
	//	IsRender = true;
	//}
	//else
	//	IsRender = false;
};