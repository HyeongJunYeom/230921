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

//	�������� 5�� ƨ��� �Ҹ�
//	�ٿ�� ī��Ʈ�� ����

//	�������� ƨ�涧���� �ӵ��� 1�� �ٸ� ó���ӵ� 10;

//	top bottom �浹�� y��ӵ� ��ȣ����

//	left right �浹�� x�� �ӵ� ��ȣ ����

//	�ٿ�� �ɶ����� ��������� ������ 5�� �۾�����..?

//	ó�� ƨ��� ������ 45 or 135 or 225 or 315

//	�÷��̾�� �浹�� ��� �Ѱ��ֱ�


