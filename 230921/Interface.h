#pragma once

#include "Define.h"
class CInterface
{
public:
	CInterface();
	virtual ~CInterface();

public:
	virtual void		Initialize()		PURE;
	virtual void		Update()			PURE;
	virtual void		LateUpdate()		PURE;
	virtual void		Release()			PURE;
	virtual void		Render(HDC hDC)		PURE;

public:
	void		Update_Rect();

public:
	const INFO&			Get_Info() const { return m_tInfo; }
	const RECT&			Get_Rect() const { return m_tRect; }

protected:
	RECT		m_tRect;
	INFO		m_tInfo;
	bool		m_bShow;
};

