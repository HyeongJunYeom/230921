#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Npc.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	: m_pBulletList(nullptr), m_dwTime(GetTickCount()), m_fAngle(270)
{
	ZeroMemory(&m_tGunPos, sizeof(POS));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 30.f, 30.f };

	m_fSpeed = 5.f;
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();

	m_tGunPos = Calculate_GunPos();

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

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tGunPos.fX, m_tGunPos.fY);
}

void CPlayer::Crash(CObj* _pOther)
{
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		/*if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_tInfo.fX += m_fSpeed / sqrt(2);
			m_tInfo.fY -= m_fSpeed / sqrt(2);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_tInfo.fX += m_fSpeed / sqrt(2);
			m_tInfo.fY += m_fSpeed / sqrt(2);
		}
		else
			m_tInfo.fX += m_fSpeed;*/
		if (180 <= m_fAngle)
		{
			m_fAngle -= 360;
		}
		m_fAngle += 5;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		/*if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_tInfo.fX -= m_fSpeed / sqrt(2);
			m_tInfo.fY -= m_fSpeed / sqrt(2);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_tInfo.fX -= m_fSpeed / sqrt(2);
			m_tInfo.fY += m_fSpeed / sqrt(2);
		}
		else
			m_tInfo.fX -= m_fSpeed;*/

		if (-180 >= m_fAngle)
		{
			m_fAngle += 360;
		}
		m_fAngle -= 5;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//	³ôÀÌ = ºøº¯ * sin µð¸à¼Ç

		//	¹Øº¯ = ºøº¯ * cos dimention
		m_tInfo.fX -= m_fSpeed * cos(m_fAngle * PI / 180);
		m_tInfo.fY -= m_fSpeed * sin(m_fAngle * PI / 180);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fX += m_fSpeed * cos(m_fAngle * PI / 180);
		m_tInfo.fY += m_fSpeed * sin(m_fAngle * PI / 180);
	}

	/*if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_tRect.top > FRAME_SIZE)
			m_tInfo.fY -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if(m_tRect.bottom < WINCY - FRAME_SIZE)
			m_tInfo.fY += m_fSpeed;
	}*/

	/*if (m_dwTime + 100 < GetTickCount())
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
	}*/

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_dwTime + 100 < GetTickCount())
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tGunPos.fX, m_tGunPos.fY, m_fAngle));

			m_dwTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_dwTime + 100 < GetTickCount())
		{
			//m_pBulletList
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tGunPos.fX, m_tGunPos.fY, m_fAngle, BULLET_SPECIAL));

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

void CPlayer::ShotGun()
{
	m_fAngle;
}

POS CPlayer::Calculate_GunPos()
{
	float fX = (-(cos(m_fAngle * PI / 180) * (float)GUN_SIZE) + m_tInfo.fX);
	float fY = (-(sin(m_fAngle * PI / 180) * (float)GUN_SIZE) + m_tInfo.fY);

	POS pos = { fX, fY };

	return pos;
}
