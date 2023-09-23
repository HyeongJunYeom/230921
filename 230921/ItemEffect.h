#pragma once

#include "Define.h"
#include "Obj.h"
#include "Player.h"

class CItemEffect : public CObj
{
public:
	CItemEffect();
	~CItemEffect() override;

public:
	void		Release() override;

public:
	void		Set_Player(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
	void		Set_MonsterList(list<CObj*>* _pMonsterList) { m_pMonsterList = _pMonsterList; }
	void		Set_BulletList(list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }

protected:
	CPlayer*		m_pPlayer;
	list<CObj*>*	m_pMonsterList;
	list<CObj*>*	m_pBulletList;
};

