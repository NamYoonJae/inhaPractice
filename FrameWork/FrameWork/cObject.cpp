#include "stdafx.h"
#include "cObject.h"
#include "cOBB.h"

cObject::cObject()
	: m_pOBB(NULL)
	, m_vRot(0, 0, 0)
	, m_vPos(0, 0, 0)
	, m_vDir(0, 0, -1)
	, m_nTag(999)
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

