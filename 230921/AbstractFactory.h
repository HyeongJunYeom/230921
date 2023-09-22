#pragma once

#include "Obj.h"
#include "Bullet.h"

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

	static CObj* CreateObj(float _fX, float _fY, int _iDimention, BULLET_TYPE _eType = BULLET_NORMAL)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		
		dynamic_cast<CBullet*>(pObj)->Set_Dim(_iDimention);
		dynamic_cast<CBullet*>(pObj)->Set_Type(_eType);

		return pObj;
	}
};