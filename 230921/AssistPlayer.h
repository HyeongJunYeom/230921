#pragma once

#include "Obj.h"
#include "ItemEffect.h"

class CAssistPlayer : public CItemEffect
{
public:
	CAssistPlayer();
	~CAssistPlayer() override;

public:
	virtual void		Initialize()			override;
	virtual int			Update()				override;
	virtual void		LateUpdate()			override;
	virtual void		Release()				override;
	virtual void		Render(HDC hDC) const	override;

private:
	void		Update_SubRect();

	void		Calculate_Angle();

	virtual void		Crash(CObj* _pOther) { };

	//	디버깅 코드

public:

protected:
	//	지속시간
	DWORD			m_dwDuration;

	RECT			m_tSubRect;
	INFO			m_tSubInfo;

	float			m_fGunTargetAngle1;
	float			m_fGunTargetAngle2;

	float			m_fGunCurAngle1;
	float			m_fGunCurAngle2;

	POS			m_tGunPos1;
	POS			m_tGunPos2;

	DWORD		m_dwTime;
};

