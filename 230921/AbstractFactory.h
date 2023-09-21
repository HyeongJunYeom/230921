#pragma once

#include "Obj.h"

template <typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;

		pObj->Initialize();

		return pObj;
	}

	static CObj* CreateObj(float _fX, float _fY, DIRECTION _eDir = DIR_END)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Direction(_eDir);

		return pObj;
	}
};