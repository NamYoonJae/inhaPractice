#include "stdafx.h"
#include "cObject.h"
#include "cOBB.h"

cObject::cObject()
	: m_pOBB(NULL)
	, m_vScale(1, 1, 1)
	, m_vRot(0, 0, 0)
	, m_vPos(0, 0, 0)
	, m_vDir(0, 0, -1)
	, m_nTag(999)
	, m_isDelete(false)
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

void cObject::BuildBoneData(DWORD *BoneNum,
	D3DXFRAME *Frame,
	D3DXMESHCONTAINER *pMesh)
{
	// Don't handle NULL frames   
	if (!Frame)
		return;


	// Get the size of this bone and its joint offset   
	D3DXVECTOR3 vecSize, vecJointOffset;
	GetBoundingBoxSize(Frame,
		pMesh,
		&vecSize,
		&vecJointOffset);

	// Set mass   
	float Mass = vecSize.x * vecSize.y * vecSize.z;

	// Mass must be > 0.0   
	if (Mass == 0.0f)
		Mass = 1.0f;

	// Set the coefficient of restitution (higher = more bounce)   
	float Coefficient = 0.4f;

	// Clear force and torque vectors   
	D3DXVECTOR3 vecForce = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vecTorque = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Set the angular resolution rate   
	float ResolutionRate = 0.05f;

	// Calculate the inverse body inertia tensor   
	float xScalar = vecSize.x * vecSize.x;
	float yScalar = vecSize.y * vecSize.y;
	float zScalar = vecSize.z * vecSize.z;

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld._11 = 1.0f / (Mass * (yScalar + zScalar));
	matWorld._22 = 1.0f / (Mass * (xScalar + zScalar));
	matWorld._33 = 1.0f / (Mass * (xScalar + yScalar));

	// Setup the point's coordinates based on half    
	// the bounding box size   
	D3DXVECTOR3 vecHalfSize = vecSize * 0.5f;

	//

	if (Frame->Name)
	{

		BoneOBB *obb = new BoneOBB;
		obb->szName = Frame->Name;
		//
		D3DXVECTOR3 vecPoints[9];
		vecPoints[0] = D3DXVECTOR3(-vecHalfSize.x, -vecHalfSize.y, -vecHalfSize.z);
		vecPoints[1] = D3DXVECTOR3(-vecHalfSize.x, vecHalfSize.y, -vecHalfSize.z);
		vecPoints[2] = D3DXVECTOR3(vecHalfSize.x, vecHalfSize.y, -vecHalfSize.z);
		vecPoints[3] = D3DXVECTOR3(vecHalfSize.x, -vecHalfSize.y, -vecHalfSize.z);

		vecPoints[4] = D3DXVECTOR3(-vecHalfSize.x, -vecHalfSize.y, vecHalfSize.z);
		vecPoints[5] = D3DXVECTOR3(-vecHalfSize.x, vecHalfSize.y, vecHalfSize.z);
		vecPoints[6] = D3DXVECTOR3(vecHalfSize.x, vecHalfSize.y, vecHalfSize.z);
		vecPoints[7] = D3DXVECTOR3(vecHalfSize.x, -vecHalfSize.y, vecHalfSize.z);

		ST_PC_VERTEX v;
		v.c = D3DCOLOR_XRGB(255, 255, 255);
		//front
		v.p = vecPoints[0];
		obb->vPoints.push_back(v);

		v.p = vecPoints[1];
		obb->vPoints.push_back(v);

		v.p = vecPoints[2];
		obb->vPoints.push_back(v);

		v.p = vecPoints[0];
		obb->vPoints.push_back(v);

		v.p = vecPoints[2];
		obb->vPoints.push_back(v);

		v.p = vecPoints[3];
		obb->vPoints.push_back(v);

		//back
		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		v.p = vecPoints[5];
		obb->vPoints.push_back(v);

		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[7];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		//up
		v.p = vecPoints[1];
		obb->vPoints.push_back(v);

		v.p = vecPoints[5];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		v.p = vecPoints[1];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		v.p = vecPoints[2];
		obb->vPoints.push_back(v);

		//down
		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[0];
		obb->vPoints.push_back(v);

		v.p = vecPoints[3];
		obb->vPoints.push_back(v);

		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[3];
		obb->vPoints.push_back(v);

		v.p = vecPoints[7];
		obb->vPoints.push_back(v);

		//left
		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[5];
		obb->vPoints.push_back(v);

		v.p = vecPoints[1];
		obb->vPoints.push_back(v);

		v.p = vecPoints[4];
		obb->vPoints.push_back(v);

		v.p = vecPoints[1];
		obb->vPoints.push_back(v);

		v.p = vecPoints[0];
		obb->vPoints.push_back(v);


		//right
		v.p = vecPoints[3];
		obb->vPoints.push_back(v);

		v.p = vecPoints[2];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		v.p = vecPoints[3];
		obb->vPoints.push_back(v);

		v.p = vecPoints[6];
		obb->vPoints.push_back(v);

		v.p = vecPoints[7];
		obb->vPoints.push_back(v);



		// Set the joint offset (offset to parent bone connection)   
		//vecPoints[8] = vecJointOffset;
		obb->vJointOffset = vecJointOffset;
		// Set the bone's center position based on transformed    
		// joint offset coordinates  
		D3DXVECTOR3 pos;
		D3DXVec3TransformCoord(&pos,
			&(-1.0f * vecJointOffset),
			&Frame->TransformationMatrix);
		obb->vPosition = pos;

		if (pos != D3DXVECTOR3(0, 0, 0))
			m_vBoneArray.push_back(obb);

	}


	// Store state matrix-based orientation. Be sure   
	// to remove translation values.   
	//Bone->m_State.m_matOrientation = Bone->m_Frame->matCombined;
	//Bone->m_State.m_matOrientation._41 = 0.0f;
	//Bone->m_State.m_matOrientation._42 = 0.0f;
	//Bone->m_State.m_matOrientation._43 = 0.0f;

	// Store state quaternion-based orientation   
	// We need to inverse it the quaternion due to the fact    
	// that we're using a left-handed coordinates system   
	//D3DXQuaternionRotationMatrix(&Bone->m_State.m_quatOrientation,
	//	&Bone->m_Frame->matCombined);
	//D3DXQuaternionInverse(&Bone->m_State.m_quatOrientation,
	//	&Bone->m_State.m_quatOrientation);

	//// Clear angular momentum   
	//Bone->m_State.m_vecAngularMomentum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// Clear force and angular velocities   
	//Bone->m_State.m_vecLinearVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Bone->m_State.m_vecAngularVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// Clear inverse world intertia tensor matrix   
	//D3DXMatrixIdentity(&Bone->m_State.m_matInvWorldInertiaTensor);

	//// Transform points   
	//for (DWORD j = 0; j < 9; j++)
	//	Bone->m_State.m_vecPoints[j] = Transform(&Bone->m_vecPoints[j],
	//		&Bone->m_State.m_matOrientation,
	//		&Bone->m_State.m_vecPosition);

	//// Get the difference in orientations from parent bone   
	//// to bone. This is used to later slerp for angular    
	//// resolution. The difference (C) from A to B    
	//// is calculated as: C = inverse(A) * B   
	//if (ParentBone) {
	//	D3DXQUATERNION quatInv;
	//	D3DXQuaternionInverse(&quatInv, &ParentBone->m_State.m_quatOrientation);
	//	Bone->m_quatOrientation = quatInv * Bone->m_State.m_quatOrientation;
	//}

	//// If there is a parent bone, then set connection position   
	//if ((Bone->m_ParentBone = ParentBone)) {

	//	// Get the inversed coordinates from the joint connection point   
	//	// to the center of the parent's bone.   
	//	D3DXMATRIX matInv;
	//	D3DXMatrixInverse(&matInv, NULL, &ParentBone->m_State.m_matOrientation);
	//	D3DXVECTOR3 vecDiff = Bone->m_State.m_vecPoints[8] -
	//		ParentBone->m_State.m_vecPosition;
	//	Bone->m_vecParentOffset = Transform(&vecDiff, &matInv);
	//}

	// Go to next bone   
	//(*BoneNum) += 1;

	// Process sibling frames   
	if (Frame->pFrameSibling)
		BuildBoneData(BoneNum, (D3DXFRAME*)Frame->pFrameSibling, pMesh);

	// Process child frames   
	if (Frame->pFrameFirstChild)
		BuildBoneData(BoneNum, (D3DXFRAME*)Frame->pFrameFirstChild, pMesh);
}



void GetBoundingBoxSize(D3DXFRAME *pFrame,
	D3DXMESHCONTAINER *pMesh,
	D3DXVECTOR3 *vecSize,
	D3DXVECTOR3 *vecJointOffset)
{
	// Set default min and max coordinates   
	D3DXVECTOR3 vecMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vecMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Only process bone vertices if there is a bone to work with   
	if (pFrame->Name && pMesh) {

		// Get a pointer to ID3DXSkinInfo interface for   
		// easier handling.   

		ID3DXSkinInfo *pSkin = pMesh->pSkinInfo;

		// Search for a bone by same name as frame   
		DWORD BoneNum = -1;
		for (DWORD i = 0; i < pSkin->GetNumBones(); i++) {
			if (!strcmp(pSkin->GetBoneName(i), pFrame->Name)) {
				BoneNum = i;
				break;
			}
		}

		// Process vertices if a bone was found   
		if (BoneNum != -1) {

			// Get the number of vertices attached   
			DWORD NumVertices = pSkin->GetNumBoneInfluences(BoneNum);
			if (NumVertices) {

				// Get the bone influcences   
				DWORD *Vertices = new DWORD[NumVertices];
				float *Weights = new float[NumVertices];
				pSkin->GetBoneInfluence(BoneNum, Vertices, Weights);

				// Get stride of vertex data   
				DWORD Stride = D3DXGetFVFVertexSize(pMesh->MeshData.pMesh->GetFVF());

				// Get bone's offset inversed transformation matrix   
				D3DXMATRIX *matInvBone = pSkin->GetBoneOffsetMatrix(BoneNum);

				// Lock vertex buffer and go through all of   
				// the vertices that are connected to bone   
				char *pVertices;
				pMesh->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
				for (int i = 0; i < NumVertices; i++) {

					// Get pointer to vertex coordinates   
					D3DXVECTOR3 *vecPtr = (D3DXVECTOR3*)(pVertices + Vertices[i] * Stride);

					// Transform vertex by bone offset transformation   
					D3DXVECTOR3 vecPos;
					D3DXVec3TransformCoord(&vecPos, vecPtr, matInvBone);

					// Get min/max values   
					vecMin.x = min(vecMin.x, vecPos.x);
					vecMin.y = min(vecMin.y, vecPos.y);
					vecMin.z = min(vecMin.z, vecPos.z);

					vecMax.x = max(vecMax.x, vecPos.x);
					vecMax.y = max(vecMax.y, vecPos.y);
					vecMax.z = max(vecMax.z, vecPos.z);
				}
				pMesh->MeshData.pMesh->UnlockVertexBuffer();

				// Free resource   
				delete[] Vertices;
				delete[] Weights;
			}
		}
	}

	// Factor in child bone connection points to size   
	if (pFrame->pFrameFirstChild) {

		// Get the bone's inverse transformation to    
		// position child connections.   
		D3DXMATRIX matInvFrame;
		D3DXMatrixInverse(&matInvFrame, NULL, &pFrame->TransformationMatrix);

		// Go through all child frames connected to this frame   
		D3DXFRAME *pFrameChild = (D3DXFRAME*)pFrame->pFrameFirstChild;
		while (pFrameChild) {
			// Get the frame's vertex coordinates and transform it   
			D3DXVECTOR3 vecPos;
			vecPos = D3DXVECTOR3(pFrameChild->TransformationMatrix._41,
				pFrameChild->TransformationMatrix._42,
				pFrameChild->TransformationMatrix._43);
			D3DXVec3TransformCoord(&vecPos, &vecPos, &matInvFrame);

			// Get min/max values   
			vecMin.x = min(vecMin.x, vecPos.x);
			vecMin.y = min(vecMin.y, vecPos.y);
			vecMin.z = min(vecMin.z, vecPos.z);

			vecMax.x = max(vecMax.x, vecPos.x);
			vecMax.y = max(vecMax.y, vecPos.y);
			vecMax.z = max(vecMax.z, vecPos.z);

			// Go to next child bone   
			pFrameChild = (D3DXFRAME*)pFrameChild->pFrameSibling;
		}
	}

	// Set the bounding box size   
	vecSize->x = (float)fabs(vecMax.x - vecMin.x);
	vecSize->y = (float)fabs(vecMax.y - vecMin.y);
	vecSize->z = (float)fabs(vecMax.z - vecMin.z);

	// Make sure each bone has a minimal size   
	// code delete

	// Set the bone's offset to center based on half the size    
	// of the bounding box and the max position   
	(*vecJointOffset) = ((*vecSize) * 0.5f) - vecMax;
}

