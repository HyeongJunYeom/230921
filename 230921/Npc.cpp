#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Initialize()
{
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;

	Set_Direction(DIR_LEFT);
	
}

int CNpc::Update()
{
	


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
}
