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

void cObjLoader::LoadOBJ(OUT vector<cGroup*> & vecGroup, const char* folder, const char* file)
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
		/*	unsigned int Index[3][3];
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
			}*/

			vector<int> list;
			int i = 0;

			while (buff[i] != '\r' && buff[i] != '\n')
			{

				string szIndex;

				while (buff[i] != 'f' &&
					buff[i] != ' ' &&
					buff[i] != '/' &&
					buff[i] != '\r')
				{
					szIndex += buff[i];
					++i;
				}

				if (!szIndex.empty())
				{
					list.push_back(atoi(szIndex.c_str()));
				}
				else
					++i;
			}

			if (list.size() == 12)
			{
				// 4 1
				// 3 2


				ST_PNT_VERTEX v;
				//2
				v.p = positions[list[3] - 1];
				v.t = UVs[list[4] - 1];
				v.n = normals[list[5] - 1];
				vertices.push_back(v);
				//4
				v.p = positions[list[9] - 1];
				v.t = UVs[list[10] - 1];
				v.n = normals[list[11] - 1];
				vertices.push_back(v);
				//3
				v.p = positions[list[6] - 1];
				v.t = UVs[list[7] - 1];
				v.n = normals[list[8] - 1];
				vertices.push_back(v);

				//2
				v.p = positions[list[3] - 1];
				v.t = UVs[list[4] - 1];
				v.n = normals[list[5] - 1];
				vertices.push_back(v);
				//1
				v.p = positions[list[0] - 1];
				v.t = UVs[list[1] - 1];
				v.n = normals[list[2] - 1];
				vertices.push_back(v);
				//4
				v.p = positions[list[9] - 1];
				v.t = UVs[list[10] - 1];
				v.n = normals[list[11] - 1];
				vertices.push_back(v);

			}
			else
			{
				for (int i = 0; i < list.size(); i += 3)
				{
					ST_PNT_VERTEX v;
					v.p = positions[list[i + 0] - 1];
					v.t = UVs[list[i + 1] - 1];
					v.n = normals[list[i + 2] - 1];
					vertices.push_back(v);
				}
			}
		}
	}

	fclose(SrcFile);

	//
	cGroup* group = new cGroup;
	group->SetVertices(vertices);
	group->SetMaterialTexture(m_mapMtlTex[MtlName]);
	vecGroup.push_back(group);
	//
	//for (auto it : m_mapMtlTex)
	//{
	//	SafeRelease(it.second->m_Texture);
	//	//SafeDelete(it.second);
	//}
	//m_mapMtlTex.clear();
}

void cObjLoader::LoadMtlLib(const char* folder, const char* file)
{
	string Path = folder + string("/") + file;

	FILE* SrcFile;

	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		return;
	}

	string MtlName;
	int nCnt = 0;

	while (!feof(SrcFile))
	{
		char buff[1024];
		fgets(buff, sizeof(buff), SrcFile);

		if (buff[0] == '#' || buff[1] == '#') continue;

		if (buff[0] == 'n')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = string(buff);
			if (m_mapMtlTex.find(MtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[MtlName] = new cMtlTex;
				m_mapMtlTex[MtlName]->SetAttribute(nCnt++);	//nCnt대신 맵사이즈로 해도 된다
			}
		}
		else if (buff[0] == 'K' || buff[1] == 'K')
		{
			float r(0), g(0), b(0);
			sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);
			int k = buff[0] == 'K' ? 1 : 2;
			
			switch (buff[k])
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
		else if (buff[0] == 'd' || buff[1] == 'd')
		{
			float power = 0.0f;
			sscanf_s(buff, "%*s %f", &power);

			m_mapMtlTex[MtlName]->GetMaterial().Power = power;
		}
		else if (buff[0] == 'm' || buff[1] == 'm')
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

LPD3DXMESH cObjLoader::LoadMeshOBJ(OUT vector<cMtlTex*> & vecMtlTex, const char* folder, const char* file)
{
	vector<DWORD> vecAttrBuf;
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;

	string sFullPath(folder);
	sFullPath += (string("/") + string(file));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "rb");

	string sMtlName;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);//%*s 애는 버리고 %s만 가져오겠다
			LoadMtlLib(folder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			// Skip
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			//int nIndex[3][3];
			//sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
			//	&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
			//	&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
			//	&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]
			//);

			vector<int> list;
			int i = 0;
			
			while (szTemp[i] != '\r' && szTemp[i] != '\n')
			{

				string szIndex;
				
				while(szTemp[i] != 'f' && 
					szTemp[i] != ' ' &&
					szTemp[i] != '/' &&
					szTemp[i] != '\r')
				{
					szIndex += szTemp[i];
					++i;
				}

				if (!szIndex.empty())
				{
					list.push_back(atoi(szIndex.c_str()));
				}
				else
					++i;
			}


			if (list.size() == 12)
			{
				// 4 1
				// 3 2


				ST_PNT_VERTEX v;
				//2
				v.p = vecV[list[3] - 1];
				v.t = vecVT[list[4] - 1];
				v.n = vecVN[list[5] - 1];
				vecVertex.push_back(v);
				//4
				v.p = vecV[list[9] - 1];
				v.t = vecVT[list[10] - 1];
				v.n = vecVN[list[11] - 1];
				vecVertex.push_back(v);
				//3
				v.p = vecV[list[6] - 1];
				v.t = vecVT[list[7] - 1];
				v.n = vecVN[list[8] - 1];
				vecVertex.push_back(v);

				//2
				v.p = vecV[list[3] - 1];
				v.t = vecVT[list[4] - 1];
				v.n = vecVN[list[5] - 1];
				vecVertex.push_back(v);
				//1
				v.p = vecV[list[0] - 1];
				v.t = vecVT[list[1] - 1];
				v.n = vecVN[list[2] - 1];
				vecVertex.push_back(v);
				//4
				v.p = vecV[list[9] - 1];
				v.t = vecVT[list[10] - 1];
				v.n = vecVN[list[11] - 1];
				vecVertex.push_back(v);

			}
			else
			{
				for (int i = 0; i < list.size(); i += 3)
				{
					ST_PNT_VERTEX v;
					v.p = vecV[list[i + 0] - 1];
					v.t = vecVT[list[i + 1] - 1];
					v.n = vecVN[list[i + 2] - 1];
					vecVertex.push_back(v);
				}
			}

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttribute());	//속성값을 얻어와서 어트리뷰트에 넣어준다

		}
	}
	fclose(fp);
	
	vecMtlTex.resize(m_mapMtlTex.size());

	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttribute()] = it.second;
	}

	LPD3DXMESH pMesh = NULL;
	//D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);
	D3DXCreateMeshFVF(vecVertex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);
	ST_PNT_VERTEX * pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecVertex.size(); ++i)
		pI[i] = i;
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	//memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	ZeroMemory(pA, (vecVertex.size() / 3) *sizeof(DWORD));
	pMesh->UnlockVertexBuffer();

	vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}
