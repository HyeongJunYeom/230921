#include "pch.h"
#include "AssistPlayer.h"
#include "Monster.h"
#include "AbstractFactory.h"

CAssistPlayer::CAssistPlayer()
	: m_dwDuration(0), m_fGunTargetAngle1(0), m_fGunTargetAngle2(0), 
	m_fGunCurAngle1(0), m_fGunCurAngle2(0), m_dwTime(GetTickCount())
{
	ZeroMemory(&m_tSubRect, sizeof(RECT));
	ZeroMemory(&m_tSubInfo, sizeof(INFO));
	ZeroMemory(&m_tGunPos1, sizeof(POS));
	ZeroMemory(&m_tGunPos2, sizeof(POS));
}

CAssistPlayer::~CAssistPlayer()
{
	Release();
}

void CAssistPlayer::Initialize()
{
	m_tInfo.fCX = ASSISTCX;
	m_tInfo.fCY = ASSISTCY;

	m_tSubInfo.fCX = ASSISTCX;
	m_tSubInfo.fCY = ASSISTCY;
}

int CAssistPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pPlayer->Get_Info().fX - 50;
	m_tInfo.fY = m_pPlayer->Get_Info().fY + 20;

	m_tSubInfo.fX = m_tInfo.fX + 100;
	m_tSubInfo.fY = m_tInfo.fY;

	if (m_dwTime + 300 < GetTickCount())
	{
		if(m_fGunCurAngle1 == m_fGunTargetAngle1)
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tGunPos1.fX, m_tGunPos1.fY, m_fGunTargetAngle1));

		if (m_fGunCurAngle2 == m_fGunTargetAngle2)
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tGunPos2.fX, m_tGunPos2.fY, m_fGunTargetAngle2));

		m_dwTime = GetTickCount();
	}

	//	플레이어 양옆으로 50 픽셀 아래로 20픽셀하여 학익진 형태로 생성	
	__super::Update_Rect();
	Update_SubRect();

	return OBJ_NOEVENT;
}

void CAssistPlayer::LateUpdate()
{
	Calculate_Angle();

	if (m_fGunCurAngle1 != m_fGunTargetAngle1)
	{
		if (0 > m_fGunTargetAngle1)
		{
			if (m_fGunCurAngle1 - 5 < m_fGunTargetAngle1)
				m_fGunCurAngle1 = m_fGunTargetAngle1;
			else
				m_fGunCurAngle1 -= 5;
		}
		else
		{
			if (m_fGunCurAngle1 + 5 > m_fGunTargetAngle1)
				m_fGunCurAngle1 = m_fGunTargetAngle1;
			else
				m_fGunCurAngle1 += 5;
		}
		
	}

	if (m_fGunCurAngle2 != m_fGunTargetAngle2)
	{
		if (0 > m_fGunTargetAngle2)
		{
			if (m_fGunCurAngle2 - 5 < m_fGunTargetAngle2)
				m_fGunCurAngle2 = m_fGunTargetAngle2;
			else
				m_fGunCurAngle2 -= 5;
		}
		else
		{
			if (m_fGunCurAngle2 + 5 > m_fGunTargetAngle2)
				m_fGunCurAngle2 = m_fGunTargetAngle2;
			else
				m_fGunCurAngle2 += 5;
		}		
	}

	m_tGunPos1.fX = m_tInfo.fX - cos(m_fGunCurAngle1 * PI / 180) * ASSIST_GUN_SIZE;
	m_tGunPos1.fY = m_tInfo.fY - sin(m_fGunCurAngle1 * PI / 180) * ASSIST_GUN_SIZE;

	m_tGunPos2.fX = m_tSubInfo.fX - cos(m_fGunCurAngle2 * PI / 180) * ASSIST_GUN_SIZE;
	m_tGunPos2.fY = m_tSubInfo.fY - sin(m_fGunCurAngle2 * PI / 180) * ASSIST_GUN_SIZE;
}

void CAssistPlayer::Release()
{
}

void CAssistPlayer::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tSubRect.left, m_tSubRect.top, m_tSubRect.right, m_tSubRect.bottom);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tGunPos1.fX, m_tGunPos1.fY);
	MoveToEx(hDC, m_tSubInfo.fX, m_tSubInfo.fY, nullptr);
	LineTo(hDC, m_tGunPos2.fX, m_tGunPos2.fY);

	//	디버깅용 코드

	TCHAR szBuf[32] = L"";
	swprintf_s(szBuf, L"GunAngle1 : %f", m_fGunCurAngle1);
	TextOutW(hDC, 500, 500, szBuf, lstrlen(szBuf));

	swprintf_s(szBuf, L"GunAngle2 : %f", m_fGunCurAngle2);
	TextOutW(hDC, 500, 550, szBuf, lstrlen(szBuf));
}

void CAssistPlayer::Update_SubRect()
{
	m_tSubRect.left		= LONG(m_tSubInfo.fX - (m_tSubInfo.fCX * 0.5f));
	m_tSubRect.right	= LONG(m_tSubInfo.fX + (m_tSubInfo.fCX * 0.5f));
	m_tSubRect.top		= LONG(m_tSubInfo.fY - (m_tSubInfo.fCY * 0.5f));
	m_tSubRect.bottom	= LONG(m_tSubInfo.fY + (m_tSubInfo.fCY * 0.5f));
}

void CAssistPlayer::Calculate_Angle()
{
	if (m_pMonsterList->empty())
		return;

	CObj* pTarget1 = nullptr;
	CObj* pTarget2 = nullptr;

	float		fShortestDistance = 1000;
	for (auto iter = m_pMonsterList->begin(); iter != m_pMonsterList->end(); ++iter)
	{
		float fXDistance = m_tInfo.fX - (*iter)->Get_Info().fX;
		float fYDistance = m_tInfo.fY - (*iter)->Get_Info().fY;
		float fDistance = sqrt(Square(fXDistance) + Square(fYDistance));

		if (fDistance < fShortestDistance)
		{
			fShortestDistance = fDistance;
			pTarget1 = (*iter);
		}
	}

	if (pTarget1)
	{
		float fDeltaWidth = m_tInfo.fX - pTarget1->Get_Info().fX;

		m_fGunTargetAngle1 = acos(fDeltaWidth / fShortestDistance) * 180 / PI;

		if (m_tInfo.fY < pTarget1->Get_Info().fY)
			m_fGunTargetAngle1 = -m_fGunTargetAngle1;
	}

	fShortestDistance = 1000;

	for (auto iter = m_pMonsterList->begin(); iter != m_pMonsterList->end(); ++iter)
	{
		float fXDistance = m_tSubInfo.fX - (*iter)->Get_Info().fX;
		float fYDistance = m_tSubInfo.fY - (*iter)->Get_Info().fY;
		float fDistance = sqrt(Square(fXDistance) + Square(fYDistance));

		if (fDistance < fShortestDistance)
		{
			fShortestDistance = fDistance;
			pTarget2 = (*iter);
		}
	}

	if (pTarget2)
	{
		float fDeltaWidth = (m_tSubInfo.fX - pTarget2->Get_Info().fX);

		m_fGunTargetAngle2 = acos(fDeltaWidth / fShortestDistance) * 180 / PI;

		if (m_tSubInfo.fY < pTarget2->Get_Info().fY)
			m_fGunTargetAngle2 = -m_fGunTargetAngle2;
	}
}
