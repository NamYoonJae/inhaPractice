#include "stdafx.h"
#include "basic.h"
#include "ResourceManager.h"
#include "XFileObject.h"

cXFileObject::cXFileObject()
	:m_pEffectMesh(nullptr)
{
}

cXFileObject::~cXFileObject()
{
}

void cXFileObject::Init()
{
	m_pEffectMesh = g_pResourceManager->GetEffectMesh("data/XFile/Bandage/", "Bandage.X");
}

void cXFileObject::Update()
{
}

void cXFileObject::Render()
{
	D3DXMATRIXA16 matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	
	
	for (size_t i = 0u; i < m_pEffectMesh->EffectParams.size(); ++i)
	{
		const auto& ep = m_pEffectMesh->EffectParams[i];
		ep.pEffect->ApplyParameterBlock(ep.hParam);

		ep.pEffect->SetMatrix("World", &matWorld);
		ep.pEffect->SetMatrix("View", &matView);
		ep.pEffect->SetMatrix("Projection", &matProj);

		UINT numPasses;
		ep.pEffect->Begin(&numPasses, 0);
		for (UINT p = 0u; p < numPasses; ++p)
		{
			ep.pEffect->BeginPass(p);
			m_pEffectMesh->pMesh->DrawSubset(i);
			ep.pEffect->EndPass();
		}
		ep.pEffect->End();
	}
}
