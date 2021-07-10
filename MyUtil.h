#pragma once

#include "framework.h"
#include <vector>

using std::vector;
using namespace Gdiplus;

Point operator+(Point& p1, Point& p2);
Point operator-(Point& p1, Point& p2);
bool operator==(Point& p1, Point& p2);
bool operator!=(Point& p1, Point& p2);

bool InRange(const int &x, const int &min, const int &max);

bool InRect(const int &x, const int &y, const RECT &rect);

bool OnLine(const int &x, const int &y, const Point& cur, const Point& next);

bool OnPath(const int &x, const int &y, const vector<Point> &p);

void DrawLine(Graphics *graphic, const Point& p1, const Point& p2);

Point GetDir(const Point& p);
