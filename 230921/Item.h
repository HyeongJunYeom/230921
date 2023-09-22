#pragma once

#include "Obj.h"
#include "Define.h"
#include "AbstractFactory.h"

class CPlayer;
class CMonster;

class CItem : public CObj
{
public:
	CItem();
	~CItem() override;

public:												
	virtual void		Initialize()				override;
	virtual int			Update()					override;
	virtual void		LateUpdate()				override;
	virtual void		Release()					override;
	virtual void		Render(HDC hDC) const		override;
													
public:											
	virtual void		Crash(CObj* _pOther)		override;

public:
	
private:
	ITEMTYPE		m_eItemType;
};