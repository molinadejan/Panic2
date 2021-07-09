#include "MyUtil.h"

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

	for (int i = 0; i < size; ++i)
	{
		Point cur = p[i];
		Point next = p[(i + 1) % size];

		if (OnLine(x, y, cur, next))
			return true;
	}

	return false;
}
