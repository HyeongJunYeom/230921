#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	: m_pBulletList(nullptr), m_dwTime(GetTickCount())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 30.f, 30.f };

	m_fSpeed = 6.f;
}

int CPlayer::Update()
{
	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
}

void CPlayer::Release()
{
}

void CPlayer::Render(HDC hDC) const
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Crash(CObj* _pOther)
{
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_tRect.right < WINCX - FRAME_SIZE)
			m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_tRect.left > FRAME_SIZE)
			m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_tRect.top > FRAME_SIZE)
			m_tInfo.fY -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if(m_tRect.bottom < WINCY - FRAME_SIZE)
			m_tInfo.fY += m_fSpeed;
	}

	if (m_dwTime + 100 < GetTickCount())
	{
		if (GetAsyncKeyState(0x57) & 0x8000)
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, DIR_UP));
			m_dwTime = GetTickCount();
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
			m_dwTime = GetTickCount();
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
			m_dwTime = GetTickCount();
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
			m_dwTime = GetTickCount();
		}
	}
}

CObj* CPlayer::Create_Bullet(DIRECTION _eDir)
{
	CObj*		pBullet = new CBullet;

	if (!pBullet)
		return nullptr;

	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Direction(_eDir);

	return pBullet;
}
