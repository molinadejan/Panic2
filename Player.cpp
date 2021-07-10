#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "Myutil.h"

Player::Player(int _x, int _y, RECT _rect)
	: pos({ _x, _y }), oldDir({ 0, 0 }), size(8), speed(2), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{ }

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
	TCHAR tmp[20];
	_stprintf(tmp, _T("%d"), (int)path.size());

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 10.0f);
	SolidBrush  solidBrush(Color(255, 255, 255, 255));

	graphic->DrawString(tmp, -1, &font, pointF, &solidBrush);


	SolidBrush brush(Color(255, 255, 0, 0));
	graphic->FillRectangle(&brush, pos.X - size / 2, pos.Y - size / 2, size, size);

	int pathSize = path.size();

	Pen pen(Color(255, 100, 200, 150));

	for (const Point& p : path)
		graphic->DrawEllipse(&pen, p.X - 2, p.Y - 2, 4, 4);

	for (int i = 0; i < pathSize - 1; ++i)
		DrawLine(graphic, path[i], path[i + 1]);

	if (pathSize > 0)
		DrawLine(graphic, path[path.size() - 1], pos);
}

void Player::MoveWithSpace(int moveX, int moveY, vector<Point>& p)
{
	if (moveX == 0 && moveY == 0) return;

	for (int i = 0; i < speed; ++i)
	{
		Point oldPos = pos;
		Point newPos = pos;

		Point next = pos + Point(moveX, moveY);

		if (!InRect(pos.X, next.Y, rect))
			next.Y = pos.Y;

		if (!InRect(next.X, pos.Y, rect))
			next.X = pos.X;

		if (!OnPath(next, path) && !path.empty() && !OnLine(next, pos, path.back()))
			newPos = next;
		else if (!OnPath({ pos.X, next.Y }, path) && !path.empty() && !OnLine({ pos.X, next.Y }, pos, path.back()))
			newPos.Y = next.Y;
		else if (!OnPath({ next.X, pos.Y }, path) && !path.empty() && !OnLine({ next.X, pos.Y }, pos, path.back()))
			newPos.X = next.X;

		if (OnCircuit(newPos, p))
		{
			pos = newPos;
   			return;
		}

		Point newDir = GetDir(newPos - oldPos);

		Point z = Zero();

		if (GetPathSize() == 0)
			AddPath(oldPos);
		else if (newDir != z && newDir != oldDir)
			AddPath(oldPos);

		if (newDir != z)
			SetOldDir(newDir);

		pos = newPos;
	}
}

void Player::MoveWithoutSpace(int moveX, int moveY, vector<Point>& p)
{
	if (path.empty())
	{
		for (int i = 0; i < speed; ++i)
		{
			Point next = pos + Point(moveX, moveY);

			if (OnCircuit(next, p))
				pos = next;
			else if (OnCircuit(pos.X, next.Y, p))
				pos.Y = next.Y;
			else if (OnCircuit(next.X, pos.Y, p))
				pos.X = next.X;
			else return;
		}
	}
}

void Player::MoveBack()
{
	for (int i = 0; i < speed; ++i)
	{
		if (path.empty()) break;

		Point backP = path.back();

		if (pos == backP)
		{
			path.pop_back();
			--i;
			continue;
		}

		Point backDir = backP - pos;
		Point dir = GetDir(backDir);

		pos = pos + dir;
		oldDir = { -dir.X, -dir.Y };
	}
}