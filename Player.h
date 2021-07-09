#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "framework.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

class Player
{
private:

	// 위치
	int posX, posY;

	// 크기
	int size;

	// 속력
	int speed;

	// 이동 가능한 영역
	RECT rect;

public:

	Player(int _x, int _y, RECT _rect);

	void DrawPlayer(Graphics *graphic);
	void MovePlayer(int moveX, int moveY, vector<Point> &p);
};

#endif // !__PLAYER_H__
