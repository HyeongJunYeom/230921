#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		LateUpdate()	PURE;
	virtual void		Release()		PURE;
	virtual void		Render(HDC hDC) const	PURE;

public:
	INFO		Get_Info() const { return m_tInfo; }
	RECT&		Get_Rect() { return m_tRect; }
	void		Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
	void		Update_Rect();
	void		Set_Direction(DIRECTION _eDir) { m_eDir = _eDir; }

	virtual void		Crash(CObj* _pOther) PURE;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
	DIRECTION	m_eDir;
	bool		m_bDead;
};

