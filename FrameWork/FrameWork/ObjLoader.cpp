#include "stdafx.h"
#include "basic.h"
#include "ObjLoader.h"


cMtlTex::cMtlTex()
	:m_Texture(nullptr)
{
	ZeroMemory(&m_pMlt, sizeof(D3DMATERIAL9));
}

cMtlTex::~cMtlTex()
{
	SafeDelete(m_Texture);
}

cGroup::cGroup()
	:m_pMtlTex(nullptr)
{
}

cGroup::~cGroup()
{
	SafeDelete(m_pMtlTex);
}

void cGroup::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	}

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
									m_vecVertex.size() / 3,
									&m_vecVertex[0],
									sizeof(ST_PNT_VERTEX));

	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTexture(0, NULL);
	}
}


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::LoadOBJ(OUT vector<cGroup*> & vecGroup, char* folder, char* file)
{
	string Path = folder + string("/") + file;
	FILE* SrcFile;

	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		vecGroup.clear();
		return;
	}

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> UVs;

	vector<ST_PNT_VERTEX> vertices;
	string MtlName;

	while (!feof(SrcFile))
	{
		char buff[1024] = { 0 };
		fgets(buff, sizeof(buff), SrcFile);

		if (buff[0] == '#') continue;

		if (buff[0] == 'm')
		{
			// %*는 해당 구문을 버린(생략)다.
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			LoadMtlLib(folder, buff);
		}
		else if (buff[0] == 'g')
		{
			if (!vertices.empty())
			{
				cGroup* group = new cGroup;
				group->SetVertices(vertices);
				group->SetMaterialTexture(m_mapMtlTex[MtlName]);
				vecGroup.push_back(group);
				vertices.clear();
			}
		}
		else if (buff[0] == 'v')
		{
			float x(0), y(0), z(0);
			switch (buff[1])
			{
			case ' ':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				positions.push_back(D3DXVECTOR3(x, y, z));
				break;
			case 't':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				UVs.push_back(D3DXVECTOR2(x, y));
				break;
			case 'n':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				normals.push_back(D3DXVECTOR3(x, y, z));
				break;
			}
		}
		else if (buff[0] == 'u')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = buff;
		}
		else if (buff[0] == 'f')
		{
			unsigned int Index[3][3];
			sscanf_s(buff, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&Index[0][0], &Index[0][1], &Index[0][2],
				&Index[1][0], &Index[1][1], &Index[1][2],
				&Index[2][0], &Index[2][1], &Index[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = positions[Index[i][0] - 1];
				v.t = UVs[Index[i][1] - 1];
				v.n = normals[Index[i][2] - 1];
				vertices.push_back(v);
			}
		}
	}

	fclose(SrcFile);

	//for (auto it : m_mapMtlTex)
	//{
	//	SafeRelease(it.second->m_Texture);
	//	//SafeDelete(it.second);
	//}
	//m_mapMtlTex.clear();
}

void cObjLoader::LoadMtlLib(char* folder, char* file)
{
	string Path = folder + string("/") + file;

	FILE* SrcFile;

	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		return;
	}

	string MtlName;

	while (!feof(SrcFile))
	{
		char buff[1024];
		fgets(buff, sizeof(buff), SrcFile);

		if (buff[0] == '#') continue;

		if (buff[0] == 'n')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = buff;

			if (m_mapMtlTex.find(MtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[MtlName] = new cMtlTex;
			}
		}
		else if (buff[0] == 'K')
		{
			float r(0), g(0), b(0);
			sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);

			switch (buff[1])
			{
			case 'a':
				m_mapMtlTex[MtlName]->GetMaterial().Ambient = D3DXCOLOR(r, g, b, 1.0f);
				break;
			case 'd':
				m_mapMtlTex[MtlName]->GetMaterial().Diffuse = D3DXCOLOR(r, g, b, 1.0f);
				break;
			case 's':
				m_mapMtlTex[MtlName]->GetMaterial().Specular = D3DXCOLOR(r, g, b, 1.0f);
				break;
			}
		}
		else if (buff[0] == 'd')
		{
			float power = 0.0f;
			sscanf_s(buff, "%*s %f", &power);

			m_mapMtlTex[MtlName]->GetMaterial().Power = power;
		}
		else if (buff[0] == 'm')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			Path = folder + (string("/") + buff);

			LPDIRECT3DTEXTURE9 texture;
			D3DXCreateTextureFromFileA(g_pD3DDevice, Path.c_str(), &texture);
			m_mapMtlTex[MtlName]->SetTexture(texture);
		}
	}

	fclose(SrcFile);
}
