#pragma once

#include "Interface.h"

class CPlayerStatus : public CInterface
{
public:
	CPlayerStatus();
	~CPlayerStatus() override;

public:
	virtual void		Initialize()		override;
	virtual void		Update()			override;
	virtual void		LateUpdate()		override;
	virtual void		Release()			override;
	virtual void		Render(HDC hDC)		override;
};

