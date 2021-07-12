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
	else if (InPolygon(pos, p, rect, false))
	{
		oldDir = { 0, 0 };
		pos = oldPos;
		path.clear();
	}
	else
	{
		Point newPos = pos;

		Point newDir = newPos - oldPos;
		Point zero = { 0, 0 };

		if (newDir != zero && newDir != oldDir)
			path.push_back(oldPos);

		if (newDir != zero)
			oldDir = newDir;
	}
}

void Player::MoveWithoutSpace(int moveX, int moveY, vector<Point>& p)
{
	if (path.empty())
	{
		Point next = pos + Point(moveX * speed, moveY * speed);

		if (OnCircuit(next, p))
			pos = next;
		else if (OnCircuit(pos.X, next.Y, p))
			pos.Y = next.Y;
		else if (OnCircuit(next.X, pos.Y, p))
			pos.X = next.X;
		else return;
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

void Player::MoveUR(vector<Point>& p)
{
	int nextX = pos.X + speed;
	int nextY = pos.Y - speed;

	if (!OnPath(nextX, nextY, path) && !OnLine(nextX, nextY, path.back(), pos))
	{
		if (urBtn)
		{
			pos.X = nextX;
			urBtn = false;
		}
		else
		{
			pos.Y = nextY;
			urBtn = true;
		}
	}
	else if (!OnPath(pos.X, nextY, path) && !OnLine(pos.X, nextY, path.back(), pos))
		pos.Y = nextY;
	else if (!OnPath(nextX, pos.Y, path) && !OnLine(nextX, pos.Y, path.back(), pos))
		pos.X = nextX;
}

void Player::MoveUL(vector<Point>& p)
{
	int nextX = pos.X - speed;
	int nextY = pos.Y - speed;

	if (ulBtn)
	{
		pos.X = nextX;
		ulBtn = false;
	}
	else
	{
		pos.Y = nextY;
		ulBtn = true;
	}
}

void Player::MoveDR(vector<Point>& p)
{
	int nextX = pos.X + speed;
	int nextY = pos.Y + speed;

	if (drBtn)
	{
		pos.X = nextX;
		drBtn = false;
	}
	else
	{
		pos.Y = nextY;
		drBtn = true;
	}
}

void Player::MoveDL(vector<Point>& p)
{
	int nextX = pos.X - speed;
	int nextY = pos.Y + speed;

	if (dlBtn)
	{
		pos.X = nextX;
		dlBtn = false;
	}
	else
	{
		pos.Y = nextY;
		dlBtn = true;
	}
}

void Player::MoveDiagonal(int moveX, int moveY, bool & btn)
{
	int nextX = pos.X + speed * moveX;
	int nextY = pos.Y + speed * moveY;

	if (!OnPath(nextX, nextY, path) && (path.empty() || !OnLine(nextX, nextY, path.back(), pos)))
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
		pos.X = nextX;
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

void Player::MoveU(vector<Point>& p)
{
	int nextY = pos.Y - speed;

	pos.Y = nextY;
}

void Player::MoveD(vector<Point>& p)
{
	int nextY = pos.Y + speed;

	pos.Y = nextY;
}

void Player::MoveR(vector<Point>& p)
{
	int nextX = pos.X + speed;

	pos.X = nextX;
}

void Player::MoveL(vector<Point>& p)
{
	int nextX = pos.X - speed;

	pos.X = nextX;
}
