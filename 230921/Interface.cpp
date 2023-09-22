#include "pch.h"
#include "Interface.h"

CInterface::CInterface()
	: m_bShow(false)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CInterface::~CInterface()
{
}

void CInterface::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5));
	m_tRect.bottom	= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5));
}
