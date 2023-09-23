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
	m_iBoundCount = 5;
	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = WINCY * 0.5f;

	m_tInfo.fCX = ITEMCX;
	m_tInfo.fCY = ITEMCY;

	float fRandom = rand() % 4;
	float fRandomAngle = rand() % 45 + 1;
	
	m_fAngle = fRandomAngle + fRandom * 90;
	m_fSpeed = 4.f;

	m_fXSpeed =	-cos(m_fAngle * PI / 180) * m_fSpeed;
	m_fYSpeed = -sin(m_fAngle * PI / 180) * m_fSpeed;
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fXSpeed;
	m_tInfo.fY += m_fYSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
	if (FRAME_SIZE >= m_tRect.top || WINCY - FRAME_SIZE <= m_tRect.bottom)
	{
		m_fYSpeed = -m_fYSpeed;
		--m_iBoundCount;
	}

	if (FRAME_SIZE >= m_tRect.left || WINCX - FRAME_SIZE <= m_tRect.right)
	{
		m_fXSpeed = -m_fXSpeed;
		--m_iBoundCount;
	}

	if (m_iBoundCount == 0)
		m_bDead = true;
}

void CItem::Release()
{
}

void CItem::Render(HDC hDC) const
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	TCHAR szBuf[] = L"아이템";
	TextOut(hDC, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 1.5f, szBuf, lstrlen(szBuf));
}

void CItem::Crash(CObj* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	//	플레이어 객체와 충돌체크
	if (pPlayer)
	{
		RECT tRect{ 0, 0 };
		bool bResult = IntersectRect(&tRect, &(pPlayer->Get_Rect()), &(Get_Rect()));

		if (bResult)
			m_bDead = true;
	}
}
