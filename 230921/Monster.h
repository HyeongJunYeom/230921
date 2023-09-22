#pragma once

#include "Obj.h"

class CMonster : public CObj
{
public:
	CMonster();
	~CMonster() override;

public:
	void		Initialize()			override;
	int			Update()				override;
	void		LateUpdate()			override;
	void		Release()				override;
	void		Render(HDC hDC) const	override;

	void		Crash(CObj* _pOther) override;
};