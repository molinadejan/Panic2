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
	//int posX, posY;

	Point pos;

	// ���� �ӵ�
	//int oldDirX, oldDirY;

	Point oldDir;

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

	//Point GetOldDir() const { return { oldDirX, oldDirY }; }
	Point GetOldDir() const { return oldDir; }
	//void SetOldDir(int _x, int _y) { oldDirX = _x; oldDirY = _y; }
	void SetOldDir(Point _oldDir) { oldDir = _oldDir; }

	int GetPathSize() const { return (int)(path.size()); }

	//Point GetPos() const { return { posX, posY }; }
	Point GetPos() const { return pos; }

	void AddPath(Point& newP);

	void SetIsSpace(bool _space);

	void DrawPlayer(Graphics *graphic);

	void MoveWithSpace(int moveX, int moveY, vector<Point> &p);
	void MoveWithoutSpace(int moveX, int moveY, vector<Point> &p);
	void MoveBack();
};

#endif // !__PLAYER_H__
