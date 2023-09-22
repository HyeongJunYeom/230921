#include "pch.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Monster.h"
#include "Npc.h"
#include "Item.h"
#include "SupplyPlane.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFps(0)
{
	ZeroMemory(&m_szFps, sizeof(TCHAR) * 16);
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initilize()
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::CreateObj());
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::CreateObj());
	m_ObjList[OBJ_NPC].push_back(CAbstractFactory<CNpc>::CreateObj());
	m_ObjList[OBJ_SPLY].push_back(CAbstractFactory<CSupplyPlane>::CreateObj());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_List(&m_ObjList[OBJ_BULLET]);
}

void CMainGame::Update()
{
	if(m_ObjList[OBJ_MONSTER].empty())
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::CreateObj());
	if(m_ObjList[OBJ_SPLY].empty())
		m_ObjList[OBJ_SPLY].push_back(CAbstractFactory<CSupplyPlane>::CreateObj());
	for (auto i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMainGame::LateUpdate()
{
	for (auto i = 0; i < OBJ_END; ++i)
	{
		for (auto iterSrc = m_ObjList[i].begin(); iterSrc != m_ObjList[i].end(); ++iterSrc)
		{
			(*iterSrc)->LateUpdate();

			//	충돌 처리 (각각의 리스트와 충돌처리 확인하며 동일 리스트일 시 break;
			for (auto j = 0; j < OBJ_END; ++j)
			{
				for (auto iterDst = m_ObjList[j].begin(); iterDst != m_ObjList[j].end(); ++iterDst)
				{
					if (i == j)
						break;
					(*iterSrc)->Crash(*iterDst);
				}
			}			
		}
	}
}

void CMainGame::Release()
{
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, FRAME_SIZE, FRAME_SIZE, WINCX- FRAME_SIZE, WINCY- FRAME_SIZE);

	for (auto i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render(m_hDC);
		}
	}
	TCHAR szBuf[32] = L"";
	swprintf_s(szBuf, L"Bullet: %d", m_ObjList[OBJ_BULLET].size());
	TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf));
	++m_iFps;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFps, L"FPS: %d", m_iFps);
		SetWindowText(g_hWnd, m_szFps);

		m_iFps = 0;

		m_dwTime = GetTickCount();
	}

	int iDim = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Demention();

	swprintf_s(szBuf, L"DIM: %d", iDim);
	TextOut(m_hDC, 10, 10, szBuf, lstrlen(szBuf));
}
