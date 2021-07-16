#pragma once

#include "framework.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

#ifndef __ENEMY_H__
#define __ENEMY_H__

class Enemy
{
private:
	
	// 위치
	PointF pos;

	// 방향
	PointF dir;

	// 크기
	int size;

	// 속력
	int speed;

	// 이동 가능한 영역
	RECT rect;

public:

	Enemy(int _x, int _y, RECT _rect);
	void Move(vector<Point> &p);

	PointF GetPos() const { return pos; }

	int GetSize() const { return size; }

	// 적 그리기
	void DrawEnemy(Graphics *graphic);
};

#endif // !__ENEMY_H__
