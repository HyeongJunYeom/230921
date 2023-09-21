#pragma once

#include "Define.h"
#include "Obj.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void			Initilize();
	void			Update();
	void			LateUpdate();
	void			Release();
	void			Render();

private:
	HDC			m_hDC;
	DWORD		m_dwTime;
	int			m_iFps;
	TCHAR		m_szFps[16];

	list<CObj*>		m_ObjList[OBJ_END];
};

