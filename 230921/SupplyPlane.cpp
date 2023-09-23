#include "pch.h"
#include "SupplyPlane.h"
#include "Monster.h"
#include "Item.h"

CSupplyPlane::CSupplyPlane()
	: m_pMonster(nullptr), m_iHitCount(0)
{
}

CSupplyPlane::~CSupplyPlane()
{
	Release();
}

void CSupplyPlane::Initialize()
{
	m_tInfo.fCX = SUPCX;
	m_tInfo.fCY = SUPCY;

	Set_Pos(0 - SUPCX * 0.5f, 300);

	m_fSpeed = 2.f;
}

int CSupplyPlane::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed;

	if (1 == m_iHitCount && m_dwHitDelay + 500 > GetTickCount())
	{
		m_tInfo.fCX += 1;
		m_tInfo.fCY += 1;
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSupplyPlane::LateUpdate()
{
	if (2 == m_iHitCount)
		m_bDead = true;

	if (m_tRect.left >= WINCX)
		m_bDead = true;
}

void CSupplyPlane::Release()
{
}

void CSupplyPlane::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	TCHAR szBuf[32] = L"º¸±Þ¼±";
	TextOut(hDC, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 1.5f, szBuf, lstrlen(szBuf));
}

void CSupplyPlane::Set_Monster(CObj* _pOther)
{
	m_pMonster = dynamic_cast<CMonster*>(_pOther);
}

void CSupplyPlane::Crash(CObj* _pOther)
{
	CBullet* pBullet = dynamic_cast<CBullet*>(_pOther);
	if (pBullet && m_dwHitDelay + 500 < GetTickCount())
	{
		bool bResult = false;
		RECT tRect { 0,0 };
		bResult = IntersectRect(&tRect, &(pBullet)->Get_Rect(), &(Get_Rect()));

		if (bResult)
		{
			m_ItemList->push_back(CAbstractFactory<CItem>::CreateObj());
			m_ItemList->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			++m_iHitCount;
			m_dwHitDelay = GetTickCount();

			m_tInfo.fCX -= 10;
			m_tInfo.fCY -= 10;
		}		
	}	
}

void CSupplyPlane::Drop_Item()
{
	//m_ItemList->push_back(CAbstractFactory::CreateObj<CItem>());
}

void CSupplyPlane::Set_ItemList(list<CObj*>* _ItemList)
{
	m_ItemList = _ItemList;
}
