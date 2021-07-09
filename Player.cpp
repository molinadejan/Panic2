#include "Player.h"
#include "Myutil.h"

Player::Player(int _x, int _y, RECT _rect)
	: posX(_x), posY(_y), size(10), speed(2), rect({ _rect.left + size / 2, _rect.top + size / 2, _rect.right - size / 2, _rect.bottom - size / 2 })
{ }

void Player::DrawPlayer(Graphics * graphic)
{
	SolidBrush brush(Color(255, 255, 0, 0));
	graphic->FillRectangle(&brush, posX - size / 2, posY - size / 2, size, size);
}

void Player::MovePlayer(int moveX, int moveY, vector<Point> &p)
{
	for (int i = 0; i < speed; ++i)
	{
		int nextX = posX + moveX;
		int nextY = posY + moveY;

		if (!InRect(nextX, nextY, rect))
			return;

		if (!OnPath(nextX, nextY, p))
			return;

		posX = nextX;
		posY = nextY;
	}
}
