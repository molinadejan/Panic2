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

	if (newPos.X < size / 2)
	{
		newPos.X = size / 2;
		dir.X *= -1;
	}

	if (newPos.X > rect.right - size / 2)
	{
		newPos.X = rect.right - size / 2;
		dir.X *= -1;
	}

	if (newPos.Y < size / 2)
	{
		newPos.Y = size / 2;
		dir.Y *= -1;
	}

	if (newPos.Y > rect.bottom - size / 2)
	{
		newPos.Y = rect.bottom - size / 2;
		dir.Y *= -1;
	}

	int pSize = p.size();

	Point _newPos = { Round(newPos.X), Round(newPos.Y) };

	if (InPolygon(_newPos, p, true))
	{
		newPos.X = pos.X;
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
