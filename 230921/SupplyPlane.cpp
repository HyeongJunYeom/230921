#include "pch.h"
#include "SupplyPlane.h"
#include "Monster.h"

CSupplyPlane::CSupplyPlane()
	: m_pMonster(nullptr)
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

	Set_Pos(0 - SUPCX * 0.5f, 400);

	m_fSpeed = 5.f;
}

int CSupplyPlane::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSupplyPlane::LateUpdate()
{
	if (m_tRect.left >= WINCX)
		m_bDead = true;
}

void CSupplyPlane::Release()
{
}

void CSupplyPlane::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CSupplyPlane::Set_Monster(CObj* _pOther)
{
	m_pMonster = dynamic_cast<CMonster*>(_pOther);
}

void CSupplyPlane::Crash(CObj* _pOther)
{

}

void CSupplyPlane::Drop_Item()
{
	//m_ItemList->push_back(CAbstractFactory::CreateObj<CItem>());
}

void CSupplyPlane::Set_ItemList(list<CObj*>* _ItemList)
{
	m_ItemList = _ItemList;
}
