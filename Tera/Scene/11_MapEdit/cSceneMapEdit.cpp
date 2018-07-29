#include "stdafx.h"
#include "cSceneMapEdit.h"

#include "cTestMap.h"

//== Object�۾�
#include "GameObject/Town/cTown_House.h"

#include "Spere/cSpere.h"
#include "BoundingBox/cBoundingBox.h"
#include "Scene/11_MapEdit/cBoundingObject.h"

#include "Ray_toCube.h"

cSceneMapEdit::cSceneMapEdit()
	: m_iNum_group(0)
	, m_bIsSelected(false)
	, m_iNum_Face(0)
	, m_bRenderMode_Object(true)
	, m_sFileName("")
{
}

cSceneMapEdit::~cSceneMapEdit()
{
	if (*SCENEMANAGER->GetCurrentSceneName() == "MapEdit")
	{
		SAFE_DELETE(m_pMap);

		if (m_pTown_House)
		{
			m_pTown_House->Destroy();
		}
		//SAFE_DELETE(m_pSpere);
		//SAFE_DELETE(m_pGameObject);
		//SAFE_DELETE(m_pBoundingBox);
	}
}

void cSceneMapEdit::Setup()
{
	if (*SCENEMANAGER->GetCurrentSceneName() == "MapEdit")
	{
		m_pMap = new cTestMap;
		m_pMap->Setup();
		//m_pPopori->SetMap(m_pMap);

		//== �۾�Object
		m_pTown_House = new cTown_House;
		m_pTown_House->Setup();
	}
}

void cSceneMapEdit::Update()
{
	if (*SCENEMANAGER->GetCurrentSceneName() == "MapEdit")
	{
		m_pLine.clear(); // ���ø� �ʱ�ȭ.

						 //== Key���� ����
		if (m_bIsSelected)
		{
			KeyMoveWASDRF();
		}

		RaytoCube();

		//==SaveLoda
		if (KEYMANAGER->IsOnceKeyDown(VK_F7)) // ���� ������
		{
			m_sFileName = "Monster_Object.txt";
			ObjectSave(m_sFileName);
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_F8)) // bound box save
		{
			m_sFileName = "Save_Object.txt";
			ObjectSave(m_sFileName);
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_F9))
		{
			ObjectLoad();
		}

		//== Object ������ Sphere����
		if (KEYMANAGER->IsOnceKeyDown(VK_F1))
		{
			//==������ ��ǥ���
			D3DXVECTOR3 pos;
			float ray_distance;
			m_pMap->IntersectTri(pos, ray_distance);

			CreateBox(pos);

			if (!m_vecBObject.empty())
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup().back()->Update();
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_F2))
		{
			ResizeSphere();
			m_vecBObject.back()->GetSpere()->Update();
		}

		//==Object���� ��������� 1.Solid 2.Wire
		if (KEYMANAGER->IsOnceKeyDown('1'))
		{
			m_bRenderMode_Object = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown('2'))
		{
			m_bRenderMode_Object = false;
		}

		//== delete box
		if (KEYMANAGER->IsOnceKeyDown(VK_DELETE))
		{
			if (!m_vecBObject.empty())
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup().erase(
					m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup().begin() + m_iNum_group);

				if (m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup().empty()) //box���� �� �׷� ����
				{
					m_vecBObject.erase(m_vecBObject.begin() + m_iNum_BSet);
				}

				m_bIsSelected = false; //���ø� Ǯ���ֱ�
			}
		}

	}
}

void cSceneMapEdit::Render()
{
	if (*SCENEMANAGER->GetCurrentSceneName() == "MapEdit") // loader�� �ҷ������� ���� ����ó��
	{
		//== Map
		m_pMap->Render();

		//== �۾�Object
		if (m_pTown_House)
		{
			if (m_bRenderMode_Object)
				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			else g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			m_pTown_House->Render();

			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

	if (!m_vecBObject.empty())
	{
		for (auto b : m_vecBObject)
		{
			b->Render();
		}
	}

	if (*SCENEMANAGER->GetCurrentSceneName() == "MapEdit") // loader�� �ҷ������� ���� ����ó��
	{
		if (m_bIsSelected)
		{
			//==���õ� �� line �׸���
			ST_PC_VERTEX a;
			a.c = 0xff00ff00;

			D3DXVECTOR3 max = m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos;
			D3DXVECTOR3 min = m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos;

			switch (m_iNum_Face)
			{

			case 0:
			{
				a.p = D3DXVECTOR3(min.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, min.z);		m_pLine.push_back(a);
			}
			break;
			case 1:
			{
				a.p = D3DXVECTOR3(max.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, max.z);		m_pLine.push_back(a);
			}
			break;
			case 2:
			{
				a.p = D3DXVECTOR3(min.x, min.y, max.z);  	m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, max.z);  	m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, min.z);  	m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, min.z);  	m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, min.z); 	m_pLine.push_back(a);
			}
			break;
			case 3:
			{
				a.p = D3DXVECTOR3(max.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, max.z);		m_pLine.push_back(a);
			}
			break;
			case 4:
			{
				a.p = D3DXVECTOR3(min.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, max.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, max.y, max.z);		m_pLine.push_back(a);
			}
			break;
			case 5:
			{
				a.p = D3DXVECTOR3(min.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, min.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(min.x, min.y, max.z);		m_pLine.push_back(a);
				a.p = D3DXVECTOR3(max.x, min.y, max.z);		m_pLine.push_back(a);
			}
			break;
			}

			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->GetWorld());
			g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP,
				5,
				&m_pLine[0],
				sizeof(ST_PC_VERTEX));
		}
	}
}

void cSceneMapEdit::FaceControl()
{
	//== �� vertex����.
	if (KEYMANAGER->IsStayKeyDown('Z')) //���
	{
		switch (m_iNum_Face)
		{
		case 0:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z += 10.0f;
		}
		break;
		case 1:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z -= 10.0f;
		}
		break;
		case 2:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x += 10.0f;
		}
		break;
		case 3:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x -= 10.0f;
		}
		break;
		case 4:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y -= 10.0f;
		}
		break;
		case 5:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y += 10.0f;
		}
		break;
		}
	}
	else if (KEYMANAGER->IsStayKeyDown('C'))
	{
		switch (m_iNum_Face)
		{
		case 0:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.z -= 10.0f;
		}
		break;
		case 1:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.z += 10.0f;
		}
		break;
		case 2:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.x -= 10.0f;
		}
		break;
		case 3:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.x += 10.0f;
		}
		break;
		case 4:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y += 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y += 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMaxPos.y += 10.0f;
		}
		break;
		case 5:
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y -= 100.0f;
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
			{
				m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y -= 1.0f;
			}
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vMinPos.y -= 10.0f;
		}
		break;
		}
	}
}

void cSceneMapEdit::KeyMoveWASDRF()
{
	if (KEYMANAGER->IsStayKeyDown('W'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z += 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z += 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z += 10.0f;
	}
	else if (KEYMANAGER->IsStayKeyDown('S'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z -= 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z -= 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.z -= 10.0f;
	}

	if (KEYMANAGER->IsStayKeyDown('R'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y += 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y += 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y += 10.0f;
	}
	else if (KEYMANAGER->IsStayKeyDown('F'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y -= 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y -= 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.y -= 10.0f;
	}

	if (KEYMANAGER->IsStayKeyDown('D'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x += 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x += 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x += 10.0f;
	}
	else if (KEYMANAGER->IsStayKeyDown('A'))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x -= 100.0f;
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_LCONTROL))
		{
			m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x -= 1.0f;
		}
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition.x -= 10.0f;
	}

	FaceControl();

	if (KEYMANAGER->IsStayKeyDown('Q'))
	{
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vRoatation.y += 0.05f;
	}
	if (KEYMANAGER->IsStayKeyDown('E'))
	{
		m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vRoatation.y -= 0.05f;
	}

	m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->Update();
}

void cSceneMapEdit::RaytoCube()
{
	cRay_toCube ray;
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))// ���콺 ��ŷ�� ���� ��ư
	{
		float distMax = 100000.0f; // ray �ִ�Ÿ�
		float ray_dis = 0.0f; // �浹�� ray�� �Ÿ�;
		float minDist = distMax; // �ּ� ray�Ÿ�;

		cRay_toCube r = ray.RayAtWorldSpace(ptMouse.x, ptMouse.y);

		D3DXVECTOR3 target;
		int previousSelectB = -1; int previousSelectG = -1;

		for (UINT b = 0; b < m_vecBObject.size(); b++)
		{
			for (UINT g = 0; g < m_vecBObject[b]->GetvecBBoxGroup().size(); g++)
			{
				m_vecBObject[b]->GetvecBBoxGroup()[g]->m_bIsPicked = false;

				for (UINT i = 0; i < 36; i += 3)
				{
					D3DXVECTOR3 p0;
					D3DXVec3TransformCoord(&p0, &m_vecBObject[b]->GetvecBBoxGroup()[g]->GetBoundingBox()->GetVertex()[i + 0].p,
						&m_vecBObject[b]->GetvecBBoxGroup()[g]->GetWorld());
					D3DXVECTOR3 p1;
					D3DXVec3TransformCoord(&p1, &m_vecBObject[b]->GetvecBBoxGroup()[g]->GetBoundingBox()->GetVertex()[i + 1].p,
						&m_vecBObject[b]->GetvecBBoxGroup()[g]->GetWorld());
					D3DXVECTOR3 p2;
					D3DXVec3TransformCoord(&p2, &m_vecBObject[b]->GetvecBBoxGroup()[g]->GetBoundingBox()->GetVertex()[i + 2].p,
						&m_vecBObject[b]->GetvecBBoxGroup()[g]->GetWorld());

					if (r.IntersectTri(p0, p1, p2, target, ray_dis)) // �ﰢ���� �浹�ߴ��� �Ǵ�.
					{
						if (minDist > ray_dis) //�Ÿ����� ���������� �� ������ �Ǻ�.
						{
							m_bIsSelected = true; // �ڽ����� ���õȰ��� �ִ�!

							minDist = ray_dis;  //�� ���� ���簪���� ��ü
							if (previousSelectB != -1)
							{
								if (previousSelectG != -1) //���� ���õȰ� �����
								{
									m_vecBObject[previousSelectB]->GetvecBBoxGroup()[previousSelectG]->m_bIsPicked = false;
								}
							}
							m_vecBObject[b]->GetvecBBoxGroup()[g]->m_bIsPicked = true;
							previousSelectG = g;
							previousSelectB = b;

							if (i == 0)	m_iNum_Face = 0; // 0�� ������ ���� ����. ���� box broup�� set�� ��ȣ�� �޴´�.
							else
							{
								m_iNum_BSet = b;
								m_iNum_group = g;
								m_iNum_Face = i / 6;
							}
						}
					}
					else if (ray_dis == 0) // 'ray_dis' ray�� �Ÿ����� �޾ƿ��� ���ϸ�, pick���δ� 'false'�� �ȴ�.
					{
						m_bIsSelected = false;
					}
				}
			} // m_vecBBoxGroup.size()
		}
	}// KEYMANAGER->IsOnceKeyDown(VK_LBUTTON)

	 //== ī�޶� ����κ�
	if (!m_vecBObject.empty() && m_bIsSelected == true)
	{
		m_vPosToCamera = m_vecBObject[m_iNum_BSet]->GetvecBBoxGroup()[m_iNum_group]->m_vPosition; // ���õ� �ڽ��� ī�޶� ����
		g_vPlayerPos = &m_vPosToCamera;
	}

}

void cSceneMapEdit::CreateBox(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 size(100, 100, 100);

	D3DXVECTOR3 min = -size;
	D3DXVECTOR3 max = size;
	cBoundingBox *m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(min, max);

	D3DXVECTOR3 position = D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z);
	m_pBoundingBox->m_vPosition = position;

	//m_pGameObject = new cGameObject;
	if (m_vecBObject.empty()) //����ó��. ���� ������������ ����
	{
		m_pGameObject = new cBoundingObject;
		m_pGameObject->GetvecBBoxGroup().push_back(m_pBoundingBox);
		m_vecBObject.push_back(m_pGameObject);

		m_pSphere = new cSpere;
		m_pSphere->Setup(pos, 0); // �� 0������ ���ο� m_vecBObject���� ���θ� �Ǻ�.
		m_vecBObject.back()->SetSpere(m_pSphere);
	}
	else if ((m_vecBObject.back()->GetSpere()->GetRadius() != 0)) // �� �������� 0�� �ƴҰ��(�����Ϸ�)...
	{
		m_pGameObject = new cBoundingObject;
		m_pGameObject->GetvecBBoxGroup().push_back(m_pBoundingBox);
		m_vecBObject.push_back(m_pGameObject);

		m_pSphere = new cSpere;
		m_pSphere->Setup(pos, 0);
		m_vecBObject.back()->SetSpere(m_pSphere);
	} //�Ȱ��� code�� else�� else if�� ���� ���Ҵ�.
	else
	{
		m_vecBObject.back()->GetvecBBoxGroup().push_back(m_pBoundingBox);
	}
}

void cSceneMapEdit::ResizeSphere()
{
	int roll = m_pGameObject->GetvecBBoxGroup().size();
	float tempA, r, value = 0;
	D3DXVECTOR3 pos;

	for (int i = 0; i < roll; i++)
	{
		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMaxPos.x;
		if (value < abs(tempA)) value = abs(tempA);
		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMinPos.x;
		if (value < abs(tempA)) value = abs(tempA);

		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMaxPos.y;
		if (value < abs(tempA)) value = abs(tempA);
		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMinPos.y;
		if (value < abs(tempA)) value = abs(tempA);

		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMaxPos.z;
		if (value < abs(tempA)) value = abs(tempA);
		tempA = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vMinPos.z;
		if (value < abs(tempA)) value = abs(tempA);
	}

	float x = 0, y = 0, z = 0, sumPX = 0, sumPY = 0, sumPZ = 0, temp = 0;
	for (int i = 0; i < roll; i++)
	{
		x = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vPosition.x;
		if (temp < abs(x)) temp = abs(x);
		sumPX += x;

		y = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vPosition.y;
		if (temp < abs(y)) temp = abs(y);
		sumPY += y;

		z = m_vecBObject.back()->GetvecBBoxGroup()[i]->m_vPosition.z;
		if (temp < abs(z)) temp = abs(z);
		sumPZ += z;
	}

	pos = { (sumPX / roll) , (sumPY / roll), (sumPZ / roll) };

	r = 500.0f;

	// �� �浹 ���� ũ�� �� ����
	m_vecBObject.back()->GetSpere()->SetRadius(r);
	m_vecBObject.back()->GetSpere()->SetPosition(pos);
}

void cSceneMapEdit::Destroy()
{
	for (auto a : m_vecBObject)
	{
		a->Destroy_g();
		SAFE_DELETE(a);
	}
	delete this;
}

void cSceneMapEdit::ObjectSave(string fileName)
{
	//const string file_name = "Save_Object.txt";
	ofstream file_out;
	file_out.open(fileName, ifstream::out);

	//==[1] �� vector�� size ũ�� ��������
	file_out << '#' << ' ' << 1 << '\n';
	file_out << '^' << ' ';
	file_out << m_vecBObject.size();
	file_out << '\n';

	//==[2]
	file_out << '#' << ' ' << 2 << '\n';
	file_out << '^' << ' ';
	for (UINT b = 0; b < m_vecBObject.size(); b++)
	{
		file_out << m_vecBObject[b]->GetvecBBoxGroup().size() << ' ';
	}
	file_out << '\n';

	//==[3] sphere���� ��������
	file_out << '#' << ' ' << 3 << '\n';
	for (UINT b = 0; b < m_vecBObject.size(); b++)
	{
		file_out << '^' << ' ';
		file_out << b; file_out << ' ';

		D3DXVECTOR3 posS;
		posS = m_vecBObject[b]->GetSpere()->GetPosition();
		file_out << posS.x << ' ';
		file_out << posS.y << ' ';
		file_out << posS.z << ' ';
		file_out << m_vecBObject[b]->GetSpere()->GetRadius();
		file_out << '\n';
	}

	//==[4] ������ cube data��������
	file_out << '#' << ' ' << 4 << '\n';
	for (UINT b = 0; b < m_vecBObject.size(); b++)
	{
		for (UINT g = 0; g < m_vecBObject[b]->GetvecBBoxGroup().size(); g++)
		{
			file_out << '^' << ' ';
			file_out << b << ' ';
			file_out << g << ' ';

			D3DXVECTOR3 min = m_vecBObject[b]->GetvecBBoxGroup()[g]->m_vMinPos;
			file_out << min.x << ' ';
			file_out << min.y << ' ';
			file_out << min.z << ' ';

			D3DXVECTOR3 max = m_vecBObject[b]->GetvecBBoxGroup()[g]->m_vMaxPos;
			file_out << max.x << ' ';
			file_out << max.y << ' ';
			file_out << max.z << ' ';

			D3DXVECTOR3 position = m_vecBObject[b]->GetvecBBoxGroup()[g]->m_vPosition;
			file_out << position.x << ' ';
			file_out << position.y << ' ';
			file_out << position.z << ' ';

			D3DXVECTOR3 rotation = m_vecBObject[b]->GetvecBBoxGroup()[g]->m_vRoatation;
			file_out << rotation.x << ' ';
			file_out << rotation.y << ' ';
			file_out << rotation.z;

			file_out << '\n';
		}
	}

	file_out.close();
}

void cSceneMapEdit::ObjectLoad()
{
	const string file_name = "Save_Object.txt";
	ifstream file_load;
	stringstream ss;
	string line;		//���پ� ���� ����
	int tokenNum = 0;	//���ο� ���� ������ �Ҵ��Ѵ�.
	char frontChar = NULL;
	int value = 0;			//ss���� ���� ����

	file_load.open(file_name, ifstream::in);

	while (getline(file_load, line)) //���پ� �б�
	{
		ss << line;

		ss >> frontChar;
		if (frontChar == '#')
		{
			ss >> tokenNum;
			ss.clear();	ss.str("");
			continue;
		}

		switch (tokenNum)
		{
		case 1: // vector<cGameObject*> ũ��
		{
			ss >> value;
			m_vecBObject.resize(value);
		}
		break;
		case 2: //vector<cGameObject*> �� ����, vector<cBoundingBox*> ũ��
		{
			for (UINT b = 0; b < m_vecBObject.size(); b++)
			{
				ss >> value;
				m_pGameObject = new cBoundingObject;
				m_pGameObject->GetvecBBoxGroup().resize(value);
				m_vecBObject[b] = m_pGameObject;
			}
		}
		break;
		case 3:
		{
			int b;
			float r;
			D3DXVECTOR3 posS;
			m_pSphere = new cSpere;

			ss >> b;
			ss >> posS.x;
			ss >> posS.y;
			ss >> posS.z;
			ss >> r;

			m_pSphere->Setup(posS, r);

			m_vecBObject[b]->SetSpere(m_pSphere);
		}
		break;
		case 4:
		{
			int b;
			int g;
			ss >> b;
			ss >> g;

			cBoundingBox* m_pBoundingBox = new cBoundingBox;

			D3DXVECTOR3 min;
			ss >> min.x;
			ss >> min.y;
			ss >> min.z;

			D3DXVECTOR3 max;
			ss >> max.x;
			ss >> max.y;
			ss >> max.z;

			D3DXVECTOR3 position;
			ss >> position.x;
			ss >> position.y;
			ss >> position.z;
			m_pBoundingBox->m_vPosition = position;

			D3DXVECTOR3 rotation;
			ss >> rotation.x;
			ss >> rotation.y;
			ss >> rotation.z;
			m_pBoundingBox->m_vRoatation = rotation;
			m_pBoundingBox->Setup(min, max);

			m_vecBObject[b]->GetvecBBoxGroup()[g] = m_pBoundingBox;
		}
		break;
		}

		ss.clear();	ss.str("");
	} //while()

	file_load.close();

	for (int b = 0; b < m_vecBObject.size(); b++)
	{
		for (int g = 0; g < m_vecBObject[b]->GetvecBBoxGroup().size(); g++)
		{
			OBJECTMANAGER->AddObject(m_vecBObject);
		}
	}

	for (auto a : m_vecBObject)
	{
		a->Update();
	}
}

void cSceneMapEdit::FG_Sight()
{
	for (int b = 0; b < m_vecBObject.size(); b++)
	{
		if (KEYMANAGER->IsOnceKeyDown('F'))
			m_vecBObject[b]->SetSightBox(!m_vecBObject[b]->GetSightBox());
		if (KEYMANAGER->IsOnceKeyDown('G'))
			m_vecBObject[b]->SetSightSpere(!m_vecBObject[b]->GetSightSpere());
	}
}


