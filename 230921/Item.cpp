#include "pch.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"

CItem::CItem()
	: m_eItemType(IT_END)
{

}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_tInfo.fCX = ITEMCX;
	m_tInfo.fCY = ITEMCY;

}

int CItem::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
	
}

void CItem::Release()
{
}

void CItem::Render(HDC hDC) const
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::Crash(CObj* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	//	플레이어 객체와 충돌체크
	if (pPlayer)
	{

	}
}
