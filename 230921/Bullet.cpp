#include "pch.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"
#include "SupplyPlane.h"

CBullet::CBullet()
	: m_fAngle(0), m_eBulletType(BULLET_END)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
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

	if (BULLET_NORMAL == m_eBulletType)
	{
		m_tInfo.fX -= cos(m_fAngle * PI / 180) * m_fSpeed;
		m_tInfo.fY -= sin(m_fAngle * PI / 180) * m_fSpeed;
	}

	if (BULLET_SPECIAL == m_eBulletType)
	{
		m_fSpeed = 3.f;
		m_fBulletDim += 30;
		m_tInfoTemp.fX	-= cos(m_fAngle * PI / 180) * m_fSpeed;
		m_tInfoTemp.fY  -= sin(m_fAngle * PI / 180) * m_fSpeed;

		m_tInfo.fX = ((cos(double(m_fBulletDim * PI / 180)) * (m_tInfoTemp.fCX * 0.5f) + m_tInfoTemp.fX));
		m_tInfo.fY = ((sin(double(m_fBulletDim * PI / 180)) * (m_tInfoTemp.fCY * 0.5f) + m_tInfoTemp.fY));
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
	CSupplyPlane* pSupply = dynamic_cast<CSupplyPlane*>(_pOther);

	if (pPlayer)
	{

	}

	if (pSupply)
	{
		bool bResult = false;
		RECT tRect;
		bResult = IntersectRect(&tRect, &(pSupply->Get_Rect()), &(Get_Rect()));

		if (bResult)
			m_bDead = true;
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

void CBullet::Calculate_SpecialBullet()
{
	
}
