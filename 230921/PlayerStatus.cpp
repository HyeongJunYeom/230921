#include "pch.h"
#include "ScoreBoard.h"

CPlayerStatus::CPlayerStatus()
{
}

CPlayerStatus::~CPlayerStatus()
{
	Release();
}

void CPlayerStatus::CPlayerStatus()
{
	
}

void CPlayerStatus::Update()
{

	__super::Update_Rect();
}

void CPlayerStatus::LateUpdate()
{

}

void CPlayerStatus::Release()
{

}

void CPlayerStatus::Render(HDC hDC)
{
	if (!m_bShow)
		return;


}