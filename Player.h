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

	// ��ġ
	int posX, posY;

	// ���� �ӵ�
	int oldDirX, oldDirY;

	// ũ��
	int size;

	// �ӷ�
	int speed;

	// �����̽� ��
	int isSpace;

	// �̵� ������ ����
	RECT rect;

	// ���� �������� ���ư��� �÷��̾��� ���
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
