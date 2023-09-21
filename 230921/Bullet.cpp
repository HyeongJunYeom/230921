#include "pch.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 5.f;

	m_fSpeed = 10.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= 10;
		break;

	case DIR_RIGHT:
		m_tInfo.fX += 10;
		break;

	case DIR_UP:
		m_tInfo.fY -= 10;
		break;

	case DIR_DOWN:
		m_tInfo.fY += 10;
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate()
{
	if (FRAME_SIZE >= m_tRect.top || WINCY - FRAME_SIZE <= m_tRect.bottom ||
		FRAME_SIZE >= m_tRect.left || WINCX - FRAME_SIZE <= m_tRect.right)
		m_bDead = true;
}

void CBullet::Release()
{
}

void CBullet::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CBullet::Crash(CObj* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther);

	if (pPlayer)
	{

	}

	if (pMonster)
	{
		bool bResult = false;
		RECT tRect;
		bResult = IntersectRect(&tRect, &(pMonster->Get_Rect()), &(Get_Rect()));

		if (bResult)
			m_bDead = true;
	}
}
