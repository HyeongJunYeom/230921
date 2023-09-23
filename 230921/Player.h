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
	int			Get_Demention() const { return m_fAngle; }

	void		Key_Input();
	CObj*		Create_Bullet(DIRECTION _eDir);
	void		ShotGun();

	POS			Calculate_GunPos();

private:
	list<CObj*>*		m_pBulletList;
	DWORD		m_dwTime;
	float		m_fAngle;
	POS			m_tGunPos;	
};

