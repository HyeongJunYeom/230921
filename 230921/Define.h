#pragma once

#include "framework.h"

#define			WINCX		800
#define			WINCY		600
#define			FRAME_SIZE	50

#define			PURE	= 0


#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
} INFO;

enum DIRECTION { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END};
enum OBJID {OBJ_PLAYER, OBJ_MONSTER, OBJ_BULLET, OBJ_END};

template <typename T>
void		Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
void		Safe_Delete_Arr(T& p)
{
	if (p)
	{
		delete[] p;
		p = nullptr;
	}
}

struct CDeleteObj
{
	template <typename T>
	void operator() (T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

struct CDeleteMap
{
	template <typename T>
	void operator() (T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

extern HWND g_hWnd;