#pragma once

#include "Define.h"
#include "ItemEffect.h"

class CBeamSwrod : public CItemEffect
{
public:
	CBeamSwrod();
	~CBeamSwrod() override;

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		LateUpdate()	override;
	virtual void		Release()		override;
	virtual void		Render(HDC hDC) const	override;

public:
	virtual void		Crash(CObj* _pOther)	override;

public:
	CPlayer*		m_pPlayer;
	INFO*			m_pInfoArr;
	RECT*			m_pRectArr;
	POS				m_tEndPoint;
};

