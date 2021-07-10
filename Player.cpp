#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "Myutil.h"

Player::Player(int _x, int _y, RECT _rect)
	: posX(_x), posY(_y), oldDirX(0), oldDirY(0), size(8), speed(2), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{ }

void Player::AddPath(const Point & newP)
{
	if (!path.empty() && path.back().X == newP.X && path.back().Y == newP.Y)
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
	graphic->FillRectangle(&brush, posX - size / 2, posY - size / 2, size, size);

	int pathSize = path.size();

	Pen pen(Color(255, 100, 200, 150));

	for (const Point& p : path)
		graphic->DrawEllipse(&pen, p.X - 2, p.Y - 2, 4, 4);

	for (int i = 0; i < pathSize - 1; ++i)
		DrawLine(graphic, path[i], path[i + 1]);

	if (pathSize > 0)
		DrawLine(graphic, path[path.size() - 1], { posX, posY });
}

void Player::MoveWithSpace(int moveX, int moveY, vector<Point>& p)
{
	for (int i = 0; i < speed; ++i)
	{
		int nextX = posX + moveX;
		int nextY = posY + moveY;

		// 화면 안쪽인지 체크합니다 //

		if (!InRect(nextX, nextY, rect))
			return;

		// ------------------------------- //

		// 이미 지나온 길인지 체크합니다 //
		// 마지막 지점과 현재 위치의 길도 체크 필요
		if (!OnPath(nextX, nextY, path) && !OnLine(nextX, nextY, {posX, posY}, path.back()))
		{
			posX = nextX;
			posY = nextY;
		}
		else return;

		// ----------------------------- //
	}
}

void Player::MoveWithoutSpace(int moveX, int moveY, vector<Point>& p)
{
	if (path.empty())
	{
		for (int i = 0; i < speed; ++i)
		{
			int nextX = posX + moveX;
			int nextY = posY + moveY;

			if (OnPath(nextX, nextY, p))
			{
				posX = nextX;
				posY = nextY;
			}
			else if (OnPath(posX, nextY, p))
				posY = nextY;
			else if (OnPath(nextX, posY, p))
				posX = nextX;
			else return;
		}
	}
}

void Player::Move(int moveX, int moveY, vector<Point> &p)
{
	if (isSpace)
	{
		for (int i = 0; i < speed; ++i)
		{
			int nextX = posX + moveX;
			int nextY = posY + moveY;

			// 화면 안쪽인지 체크합니다 //

			if (!InRect(nextX, nextY, rect))
				return;

			// ------------------------------- //

			// 이미 지나온 길인지 체크합니다 //

			if (!OnPath(nextX, nextY, path))
			{
				posX = nextX;
				posY = nextY;
			}
			else return;

			// ----------------------------- //
		}
	}
	else
	{
		if (path.empty())
		{
			for (int i = 0; i < speed; ++i)
			{
				int nextX = posX + moveX;
				int nextY = posY + moveY;

				if (OnPath(nextX, nextY, p))
				{
					posX = nextX;
					posY = nextY;
				}
				else return;
			}
		}
	}
}

void Player::MoveBack()
{
	for (int i = 0; i < speed; ++i)
	{
		if (path.empty()) break;

		Point backP = path.back();

		if (posX == backP.X && posY == backP.Y)
		{
			path.pop_back();
			--i;
			continue;
		}

		Point backDir = { backP.X - posX, backP.Y - posY };

		Point dir = GetDir(backDir);

		posX += dir.X;
		posY += dir.Y;

		oldDirX = -dir.X;
		oldDirY = -dir.Y;
	}
}
