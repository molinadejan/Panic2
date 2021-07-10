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

bool InRect(const Point & p, const RECT & rect)
{
	return InRange(p.X, rect.left, rect.right) && InRange(p.Y, rect.top, rect.bottom);
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

bool OnLine(const Point & p, const Point & cur, const Point & next)
{
	if (cur.X == next.X)
		if (p.X == cur.X && InRange(p.Y, cur.Y, next.Y))
			return true;

	if (cur.Y == next.Y)
		if (p.Y == cur.Y && InRange(p.X, cur.X, next.X))
			return true;

	return (abs(p.X - cur.X) == abs(p.Y - cur.Y)) && InRange(p.X, cur.X, next.X) && InRange(p.Y, cur.Y, next.Y);
}

bool OnCircuit(const int & x, const int & y, const vector<Point>& circuit)
{
	int size = circuit.size();

	if (size < 2) return false;

	for (int i = 0; i < size; ++i)
	{
		Point cur = circuit[i];
		Point next = circuit[(i + 1) % size];

		if (OnLine(x, y, cur, next))
			return true;
	}

	return false;
}

bool OnCircuit(const Point & p, const vector<Point>& circuit)
{
	int size = circuit.size();

	if (size < 2) return false;

	for (int i = 0; i < size; ++i)
	{
		Point cur = circuit[i];
		Point next = circuit[(i + 1) % size];

		if (OnLine(p, cur, next))
			return true;
	}

	return false;
}

bool OnPath(const int & x, const int & y, const vector<Point>& path)
{
	int size = path.size();

	if (size < 2) return false;

	for (int i = 0; i < size - 1; ++i)
	{
		Point cur = path[i];
		Point next = path[i + 1];

		if (OnLine(x, y, cur, next))
			return true;
	}

	return false;
}

bool OnPath(const Point & p, const vector<Point>& path)
{
	int size = path.size();

	if (size < 2) return false;

	for (int i = 0; i < size - 1; ++i)
	{
		Point cur = path[i];
		Point next = path[i + 1];

		if (OnLine(p, cur, next))
			return true;
	}

	return false;
}

bool InPolygon(const Point & p, const vector<Point>& polygon)
{
	int size = polygon.size();

	if (size < 3) return false;

	for (int i = 0; i < size; ++i)
	{
		Point cur = polygon[i];
		Point next = polygon[(i + 1) % size];


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

Point Zero()
{
	Point ret = { 0, 0 };
	return ret;
}
