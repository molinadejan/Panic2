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

	// 이전 속도
	int oldDirX, oldDirY;

	// 크기
	int size;

	// 속력
	int speed;

	// 스페이스 바
	int isSpace;

	// 이동 가능한 영역
	RECT rect;

	// 닫힌 공간으로 나아갈때 플레이어의 경로
	vector<Point> path;

public:

	Player(int _x, int _y, RECT _rect);

	Point GetOldDir() const { return { oldDirX, oldDirY }; }
	void SetOldDir(int _x, int _y) { oldDirX = _x; oldDirY = _y; }

	int GetPathSize() const { return (int)(path.size()); }

	Point GetPos() const { return { posX, posY }; }

	void AddPath(const Point& newP);

	void SetIsSpace(bool _space);

	void DrawPlayer(Graphics *graphic);

	void MoveWithSpace(int moveX, int moveY, vector<Point> &p);
	void MoveWithoutSpace(int moveX, int moveY, vector<Point> &p);

	void Move(int moveX, int moveY, vector<Point> &p);
	void MoveBack();
};

#endif // !__PLAYER_H__
