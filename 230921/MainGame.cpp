#include "pch.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Monster.h"
#include "Npc.h"
#include "Item.h"
#include "SupplyPlane.h"
#include "AssistPlayer.h"

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

	srand(time(NULL));

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::CreateObj());
	
	//	테스트 코드
	for (int i = 0; i < 3; ++i)
	{
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::CreateObj());
	}
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::CreateObj());
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::CreateObj());
	m_ObjList[OBJ_MONSTER].back()->Set_Pos(WINCX - FRAME_SIZE - m_ObjList[OBJ_MONSTER].back()->Get_Info().fCX * 0.5f, WINCY - FRAME_SIZE - m_ObjList[OBJ_MONSTER].back()->Get_Info().fCY * 0.5f);
	m_ObjList[OBJ_NPC].push_back(CAbstractFactory<CNpc>::CreateObj());
	m_ObjList[OBJ_ITEMEFFECT].push_back(CAbstractFactory<CAssistPlayer>::CreateObj());

	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_List(&m_ObjList[OBJ_BULLET]);
	
	for (auto iter = m_ObjList[OBJ_ITEMEFFECT].begin(); iter != m_ObjList[OBJ_ITEMEFFECT].end(); ++iter)
	{
		dynamic_cast<CItemEffect*>(*iter)->Set_BulletList(&m_ObjList[OBJ_BULLET]);
		dynamic_cast<CItemEffect*>(*iter)->Set_Player(dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front()));
		dynamic_cast<CItemEffect*>(*iter)->Set_MonsterList(&m_ObjList[OBJ_MONSTER]);
	}
}

void CMainGame::Update()
{
	// 테스트 코드
	if (m_ObjList[OBJ_MONSTER].size() < 2)
	{
		m_ObjList[OBJ_MONSTER].back()->Set_Pos(WINCX - FRAME_SIZE - m_ObjList[OBJ_MONSTER].back()->Get_Info().fCX * 0.5f, WINCY - FRAME_SIZE - m_ObjList[OBJ_MONSTER].back()->Get_Info().fCY * 0.5f);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::CreateObj());
	}
	if (m_ObjList[OBJ_SPLY].empty())
	{
		m_ObjList[OBJ_SPLY].push_back(CAbstractFactory<CSupplyPlane>::CreateObj());
		dynamic_cast<CSupplyPlane*>(m_ObjList[OBJ_SPLY].front())->Set_ItemList(&m_ObjList[OBJ_ITEM]);
	}

	/*if (m_ObjList[OBJ_ITEM].size() < 10)
	{
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::CreateObj());
	}*/


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
