#include "Enemy.h"

#include "MyUtil.h"

Enemy::Enemy(int _x, int _y, RECT _rect)
	: pos({ (REAL)_x, (REAL)_y }), size(16), speed(1), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{
	dir = GetRandomCircle();
}

void Enemy::Move()
{
	PointF newPos = pos + dir;

	int newPosX = Round(newPos.X);
	int newPosY = Round(newPos.Y);

	if (!InRange(newPosX, rect.left, rect.right))
	{
		newPos.X = pos.X;
		dir.X *= -1;
	}

	if (!InRange(newPosY, rect.top, rect.bottom))
	{
		newPos.Y = pos.Y;
		dir.Y *= -1;
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
