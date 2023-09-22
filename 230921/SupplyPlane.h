#pragma once

#include "Obj.h"
#include "Define.h"
#include "AbstractFactory.h"

class CMonster;

class CSupplyPlane : public CObj
{
public:
	CSupplyPlane();
	~CSupplyPlane() override;

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		LateUpdate()	override;
	virtual void		Release()		override;
	virtual void		Render(HDC hDC) const	override;

public:
	void		Set_Monster(CObj* _pOther);

	void		Crash(CObj* _pOther) override;

	void		Drop_Item();
	void		Set_ItemList(list<CObj*>* _ItemList);

private:
	CMonster*			m_pMonster;
	list<CObj*>*		m_ItemList;
};

