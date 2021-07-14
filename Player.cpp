#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "Myutil.h"

Player::Player(int _x, int _y, RECT _rect)
	: pos({ _x, _y }), oldDir({ 0, 0 }), size(8), speed(4), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{ 
	urBtn = ulBtn = drBtn = dlBtn = false;
}

void Player::AddPath(Point & newP)
{
	if (!path.empty() && path.back() == newP)
		return;

	path.push_back(newP);
}

void Player::SetIsSpace(bool _space)
{
	isSpace = _space;
}

void Player::DrawPlayer(Graphics * graphic)
{
	// 테스트용
	/*TCHAR tmp[20];
	_stprintf(tmp, _T("%d"), (int)path.size());

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 10.0f);
	SolidBrush  solidBrush(Color(255, 255, 255, 255));

	graphic->DrawString(tmp, -1, &font, pointF, &solidBrush);*/


	SolidBrush brush(Color(255, 255, 0, 0));
	graphic->FillRectangle(&brush, pos.X - size / 2, pos.Y - size / 2, size, size);

	int pathSize = (int)path.size();

	Pen pen(Color(255, 100, 200, 150));

	// 테스트용
	/*for (const Point& p : path)
		graphic->DrawEllipse(&pen, p.X - 2, p.Y - 2, 4, 4);*/

	for (int i = 0; i < pathSize - 1; ++i)
		DrawLine(graphic, path[i], path[i + 1]);

	if (pathSize > 0)
		DrawLine(graphic, path[path.size() - 1], pos);
}

void Player::MoveWithSpace(int moveX, int moveY, vector<Point>& p)
{
	if (!InRect(pos.X, pos.Y + moveY * speed, rect))
		moveY = 0;

	if (!InRect(pos.X + moveX * speed, pos.Y, rect))
		moveX = 0;

	Point oldPos = pos;

	if (moveX == 1 && moveY == -1)
		MoveDiagonal(moveX, moveY, urBtn);
	else if (moveX == -1 && moveY == -1)
		MoveDiagonal(moveX, moveY, ulBtn);
	else if (moveX == 1 && moveY == 1)
		MoveDiagonal(moveX, moveY, drBtn);
	else if (moveX == -1 && moveY == 1)
		MoveDiagonal(moveX, moveY, dlBtn);
	else if (moveX == 0 && moveY == -1)
		MoveVertical(moveY);
	else if (moveX == 0 && moveY == 1)
		MoveVertical(moveY);
	else if (moveX == 1 && moveY == 0)
		MoveHorizontal(moveX);
	else if (moveX == -1 && moveY == 0)
		MoveHorizontal(moveX);

	// 중간에 열린 영역이 끼어있을수도 있기 때문에 가운데 영역도 확인
	Point m = {(pos.X + oldPos.X) / 2, (pos.Y + oldPos.Y) / 2};

	if (InPolygon(pos, p, rect, false) || InPolygon(m, p, rect, false))
	{
		oldDir = { 0, 0 };
		pos = oldPos;
		path.clear();
		return;
	}

	Point newPos = pos;

	Point newDir = newPos - oldPos;
	Point zero = { 0, 0 };

	if (newDir != zero && newDir != oldDir)
		path.push_back(oldPos);

	if (newDir != zero)
		oldDir = newDir;

	if (OnCircuit(pos, p))
	{
		oldDir = { 0, 0 };

		if (path.empty())
		{
			path.clear();
		}
		else
		{
			path.push_back(pos);
			CombinePolygon(p, path, rect);
		}
	}
}

void Player::MoveWithoutSpace(int moveX, int moveY, vector<Point>& p)
{
	if (path.empty())
	{
		Point next = pos + Point(moveX * speed, moveY * speed);

		bool checkMove = false;

		if (moveY != 0 && OnCircuit(pos.X, next.Y, p))
		{
			Point m = { pos.X, (pos.Y + next.Y) / 2 };

			if (!InPolygon(m, p, rect, false) && OnCircuit(m, p))
			{
				checkMove = true;
				pos.Y = next.Y;
			}
		}
		
		if (!checkMove && moveX != 0 && OnCircuit(next.X, pos.Y, p))
		{
			Point m = { (pos.X + next.X) / 2, pos.Y };

			if (!InPolygon(m, p, rect, false) && OnCircuit(m, p))
				pos.X = next.X;
		}
	}
}

void Player::MoveBack()
{
	if (path.empty()) return;

	if (pos == path.back())
		path.pop_back();

	if (path.empty()) return;

	Point backP = path.back();

	Point backDir = GetDir(backP - pos);
	Point dir = backDir * speed;

	pos = pos + dir;
	oldDir = -1 * backDir;
}

void Player::MoveDiagonal(int moveX, int moveY, bool & btn)
{
	int nextX = pos.X + speed * moveX;
	int nextY = pos.Y + speed * moveY;

	if (btn)
	{
		if (!OnPath(nextX, pos.Y, path) && (path.empty() || !OnLine(nextX, pos.Y, path.back(), pos)))
			pos.X = nextX;
		else if (!OnPath(pos.X, nextY, path) && (path.empty() || !OnLine(pos.X, nextY, path.back(), pos)))
			pos.Y = nextY;
		else return;

		btn = false;
	}
	else
	{
		if (!OnPath(pos.X, nextY, path) && (path.empty() || !OnLine(pos.X, nextY, path.back(), pos)))
			pos.Y = nextY;
		else if (!OnPath(nextX, pos.Y, path) && (path.empty() || !OnLine(nextX, pos.Y, path.back(), pos)))
			pos.X = nextX;
		else return;

		btn = true;
	}

	/*if (!OnPath(nextX, nextY, path) && (path.empty() || !OnLine(nextX, nextY, path.back(), pos)))
	{
		if (btn)
		{
			pos.X = nextX;
			btn = false;
		}
		else
		{
			pos.Y = nextY;
			btn = true;
		}
	}
	else if (!OnPath(pos.X, nextY, path) && (path.empty() || !OnLine(pos.X, nextY, path.back(), pos)))
		pos.Y = nextY;
	else if (!OnPath(nextX, pos.Y, path) && (path.empty() || !OnLine(nextX, pos.Y, path.back(), pos)))
		pos.X = nextX;*/
}

void Player::MoveHorizontal(int moveX)
{
	int nextX = pos.X + speed * moveX;

	if(!OnPath(nextX, pos.Y, path) && (path.empty() || !OnLine(nextX, pos.Y, path.back(), pos)))
		pos.X = nextX;
}

void Player::MoveVertical(int moveY)
{
	int nextY = pos.Y + speed * moveY;

	if(!OnPath(pos.X, nextY, path) && (path.empty() || !OnLine(pos.X, nextY, path.back(), pos)))
		pos.Y = nextY;
}
