#include "pch.h"
#include "Npc.h"
#include "Player.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Initialize()
{
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 30;

	m_tInfo.fX = 100;
	m_tInfo.fY = 100;

	Set_Direction(DIR_LEFT);	
}

int CNpc::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNpc::LateUpdate()
{
	
}

void CNpc::Release()
{
}

void CNpc::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CNpc::Crash(CObj* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	if (pPlayer)
	{
		float fCX = Square((pPlayer->Get_Info().fX - Get_Info().fX));
		float fCY = Square((pPlayer->Get_Info().fY - Get_Info().fY));
		float fCH = Square(pPlayer->Get_Info().fCX * 0.5f + Get_Info().fCX * 0.5f);

		if ((fCX + fCY) <= fCH)
			m_bDead = true;
	}
}
