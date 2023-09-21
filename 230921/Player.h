#pragma once

#include "Define.h"
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	~CPlayer() override;

public:
	void		Initialize()			override;
	int			Update()				override;
	void		LateUpdate()			override;
	void		Release()				override;
	void		Render(HDC hDC) const	override;

	void		Crash(CObj* _pOther) override;

public:
	void		Set_Bullet_List(list<CObj*>* _pBulletList)
	{
		if(_pBulletList)
			m_pBulletList = _pBulletList;
	}

	void		Key_Input();
	CObj*		Create_Bullet(DIRECTION _eDir);

private:
	list<CObj*>*		m_pBulletList;
	DWORD		m_dwTime;
};

