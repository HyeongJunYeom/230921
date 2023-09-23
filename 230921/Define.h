#pragma once

#include "framework.h"

#define			WINCX		700
#define			WINCY		800
#define			FRAME_SIZE	20

#define			PURE		= 0

#define			PI			3.141592


#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			INT_SHOW		0
#define			INT_HIDE		1

#define			GUN_SIZE		40

#define			ITEMCX		20
#define			ITEMCY		20

#define			ASSISTCX	20
#define			ASSISTCY	20
#define			ASSIST_GUN_SIZE		20

#define			SUPCX		40
#define			SUPCY		20

typedef struct tagPos
{
	float fX;
	float fY;
} POS;

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
} INFO;

enum DIRECTION { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END};
enum OBJID {OBJ_PLAYER, OBJ_MONSTER, OBJ_BULLET, OBJ_NPC, OBJ_ITEM, OBJ_SPLY, OBJ_ITEMEFFECT, OBJ_END};

enum BULLET_TYPE { BULLET_NORMAL, BULLET_SPECIAL, BULLET_END};

//	형준 아이템 타입
enum ITEMTYPE {IT_ASSIST, IT_END};

template <typename T>
T		Square(T x)
{
	return x * x;
}

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