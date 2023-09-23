#pragma once

#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	~CBullet() override;

public:
	void		Initialize()			override;
	int			Update()				override;
	void		LateUpdate()			override;
	void		Release()				override;
	void		Render(HDC hDC) const	override;

	void		Crash(CObj* _pOther) override;
	void		Set_Dim(float _fDimention)
	{ 
		m_fAngle = _fDimention; 
		m_fBulletDim = m_fAngle;
	}
	void		Set_Type(BULLET_TYPE _eType) 
	{
		m_eBulletType = _eType; 

		if (BULLET_SPECIAL == m_eBulletType)
		{
			m_fSpeed = 8.f;
			m_tInfoTemp.fCX = 40;
			m_tInfoTemp.fCY = 40;

			m_tInfoTemp.fX = m_tInfo.fX;
			m_tInfoTemp.fY = m_tInfo.fY;

			/*m_tRectTemp.left	= LONG(m_tInfoTemp.fX - m_tInfoTemp.fCX * 0.5f);
			m_tRectTemp.right	= LONG(m_tInfoTemp.fX + m_tInfoTemp.fCX * 0.5f);
			m_tRectTemp.top		= LONG(m_tInfoTemp.fY - m_tInfoTemp.fCY * 0.5f);
			m_tRectTemp.bottom	= LONG(m_tInfoTemp.fY - m_tInfoTemp.fCY * 0.5f);*/
		}
	}

private:
	void		Calculate_SpecialBullet();

private:
	float				m_fAngle;
	BULLET_TYPE			m_eBulletType;
	RECT				m_tRectTemp;
	INFO				m_tInfoTemp;

	float				m_fBulletDim;
};

