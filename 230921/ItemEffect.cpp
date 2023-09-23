#include "pch.h"
#include "ItemEffect.h"

CItemEffect::CItemEffect()
	: m_pPlayer(nullptr)
{
}

CItemEffect::~CItemEffect()
{
	Release();
}

void CItemEffect::Release()
{
}
