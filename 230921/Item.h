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
	float			m_fAngle;
	int				m_iBoundCount;
};

//	아이템은 5번 튕기면 소멸
//	바운드 카운트로 추적

//	아이템은 튕길때마다 속도가 1씩 줄며 처음속도 10;

//	top bottom 충돌시 y축속도 부호반전

//	left right 충돌시 x축 속도 부호 반전

//	바운드 될때마다 진행방향의 각도가 5씩 작아지게..?

//	처음 튕기는 방향은 45 or 135 or 225 or 315

//	플레이어와 충돌시 기능 넘겨주기


