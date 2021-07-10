#include "MyUtil.h"

Point operator+(Point & p1, Point & p2)
{
	return { p1.X + p2.X, p1.Y + p2.Y };
}

Point operator-(Point & p1, Point & p2)
{
	return { p1.X - p2.X, p1.Y - p2.Y };
}

bool operator==(Point & p1, Point & p2)
{
	return (p1.X == p2.X && p1.Y == p2.Y);
}

bool operator!=(Point & p1, Point & p2)
{
	return !(p1.X == p2.X && p1.Y == p2.Y);
}

bool InRange(const int & x, const int & min, const int & max)
{
	if (min > max)
		return InRange(x, max, min);

	if(x < min || x > max)
		return false;

	return true;
}

bool InRect(const int & x, const int & y, const RECT & rect)
{
	return InRange(x, rect.left, rect.right) && InRange(y, rect.top, rect.bottom);
}

bool OnLine(const int & x, const int & y, const Point & cur, const Point & next)
{
	if (cur.X == next.X)
		if (x == cur.X && InRange(y, cur.Y, next.Y))
			return true;

	if (cur.Y == next.Y)
		if (y == cur.Y && InRange(x, cur.X, next.X))
			return true;

	return (abs(x - cur.X) == abs(y - cur.Y)) && InRange(x, cur.X, next.X) && InRange(y, cur.Y, next.Y);
}

bool OnPath(const int & x, const int & y, const vector<Point>& p)
{
	int size = p.size();

	if (size < 2) return false;

	for (int i = 0; i < size; ++i)
	{
		Point cur = p[i];
		Point next = p[(i + 1) % size];

		if (OnLine(x, y, cur, next))
			return true;
	}

	return false;
}

void DrawLine(Graphics * graphic, const Point& p1, const Point& p2)
{
	Pen pen(Color(255, 255, 0, 255));
	graphic->DrawLine(&pen, p1, p2);
}

// 기울기의 절대값이 1이거나 수직, 수평선만 입력으로 들어온다고 가정합니다.
Point GetDir(const Point & p)
{
	Point ret = p;

	if (ret.X != 0) ret.X /= abs(ret.X);
	if (ret.Y != 0) ret.Y /= abs(ret.Y);

	return ret;
}
