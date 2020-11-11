#pragma once

class EffectMesh;

class cXFileObject
{
private:
	EffectMesh* m_pEffectMesh;
public:
	cXFileObject();
	virtual ~cXFileObject();

	virtual void Init();
	virtual void Update();
	virtual void Render();
};

