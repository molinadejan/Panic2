#pragma once

#include "framework.h"
#include <vector>

using std::vector;
using namespace Gdiplus;

bool InRange(const int &x, const int &min, const int &max);

bool InRect(const int &x, const int &y, const RECT &rect);

bool OnLine(const int &x, const int &y, const Point& cur, const Point& next);

bool OnPath(const int &x, const int &y, const vector<Point> &p);
