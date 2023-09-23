#include "pch.h"
#include "BeamSwrod.h"
#include "Monster.h"
#include "Bullet.h"

CBeamSwrod::CBeamSwrod()
	: m_pPlayer(nullptr), m_pInfoArr(nullptr), m_pRectArr(nullptr)
{
	ZeroMemory(&m_tEndPoint, sizeof(POS));
}

CBeamSwrod::~CBeamSwrod()
{
	Release();
}

void CBeamSwrod::Initialize()
{
}

int CBeamSwrod::Update()
{
	return 0;
}

void CBeamSwrod::LateUpdate()
{
}

void CBeamSwrod::Release()
{
	Safe_Delete_Arr<INFO*>(m_pInfoArr);
	Safe_Delete_Arr<RECT*>(m_pRectArr);
}

void CBeamSwrod::Render(HDC hDC) const
{
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tEndPoint.fX, m_tEndPoint.fY);
}

void CBeamSwrod::Crash(CObj* _pOther)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther);
	CBullet* pBullet = dynamic_cast<CBullet*>(_pOther);

	if (pMonster)
	{

	}

	if (pBullet)
	{

	}
}
