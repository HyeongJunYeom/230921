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
	int					m_iHitCount;

	DWORD				m_dwHitDelay;
};

//	2대까지 버티며 맞을때마다 아이템 드랍

//	2대 맞으면 소멸

//	1대 맞으면 0.5 초간 슈퍼아머
