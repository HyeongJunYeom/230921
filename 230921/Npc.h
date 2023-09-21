#pragma once

#include "Obj.h"

class CNpc : public CObj
{
public:
	CNpc();
	~CNpc() override;

public:
	void		Initialize() override;
	int			Update() override;
	void		LateUpdate() override;
	void		Release() override;
	void		Render(HDC hDC) const override;

	void		Crash(CObj* _pOther) override;
};

