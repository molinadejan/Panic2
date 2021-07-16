#include "Enemy.h"

#include "MyUtil.h"

Enemy::Enemy(int _x, int _y, RECT _rect)
	: pos({ (REAL)_x, (REAL)_y }), size(16), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{
	speed = rand() % 2 + 1;
	dir = GetRandomCircle();
}

void Enemy::Move(vector<Point> &p)
{
	PointF newPos = { pos.X + dir.X * speed, pos.Y + dir.Y * speed };

	int newPosX = Round(newPos.X);
	int newPosY = Round(newPos.Y);

	if (!InRange(newPosX, rect.left, rect.right))
	{
		newPosX = Round(pos.X);
		newPos.X = pos.X;
		dir = GetRandomCircle();
	}

	if (!InRange(newPosY, rect.top, rect.bottom))
	{
		newPosY = Round(pos.Y);
		newPos.Y = pos.Y;
		dir = GetRandomCircle();
	}

	if (InPolygon({ newPosX, newPosY }, p, true))
	{
		newPosX = Round(pos.X);
		newPos.X = pos.X;

		newPosY = Round(pos.Y);
		newPos.Y = pos.Y;

		dir = GetRandomCircle();
	}

	pos = newPos;
}

void Enemy::DrawEnemy(Graphics * graphic)
{
	int posX = Round(pos.X);
	int posY = Round(pos.Y);

	SolidBrush brush(Color(255, 255, 125, 0));
	graphic->FillRectangle(&brush, posX - size / 2, posY - size / 2, size, size);
}
