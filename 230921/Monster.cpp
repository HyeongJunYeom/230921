#include "pch.h"
#include "Monster.h"
#include "Player.h"
#include "Bullet.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_eDir = DIR_RIGHT;

	m_tInfo.fCX = 50;
	m_tInfo.fCY = 20;

	m_tInfo.fX = FRAME_SIZE + m_tInfo.fCX * 0.5;
	m_tInfo.fY = FRAME_SIZE + m_tInfo.fCY * 0.5;

	m_fSpeed = 10.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if(DIR_RIGHT == m_eDir)
		m_tInfo.fX += m_fSpeed;

	else if (DIR_LEFT == m_eDir)
		m_tInfo.fX -= m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate()
{
	if (m_tRect.right >= WINCX - FRAME_SIZE)
		m_eDir = DIR_LEFT;

	else if (m_tRect.left <= FRAME_SIZE)
		m_eDir = DIR_RIGHT;		
}

void CMonster::Release()
{
}

void CMonster::Render(HDC hDC) const
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Crash(CObj* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);
	CBullet* pBullet = dynamic_cast<CBullet*>(_pOther);

	if (pPlayer)
	{

	}

	if (pBullet)
	{
		bool bResult = false;
		RECT tRect;
		bResult = IntersectRect(&tRect, &(pBullet->Get_Rect()), &(Get_Rect()));

		if (bResult)
			m_bDead = true;
	}
}