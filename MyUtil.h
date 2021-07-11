#pragma once

#include "framework.h"
#include <vector>

using std::vector;
using namespace Gdiplus;

Point operator+(Point& p1, Point& p2);
Point operator-(Point& p1, Point& p2);
bool operator==(Point& p1, Point& p2);
bool operator!=(Point& p1, Point& p2);

Point operator*(Point& p, int m);
Point operator*(int m, Point& p);

bool InRange(const int &x, const int &min, const int &max);

bool InRect(const int &x, const int &y, const RECT &rect);
bool InRect(const Point &p, const RECT &rect);

bool OnLine(const int &x, const int &y, const Point& cur, const Point& next);
bool OnLine(const Point &p, const Point& cur, const Point& next);

bool OnCircuit(const int &x, const int &y, const vector<Point> &circuit);
bool OnCircuit(const Point &p, const vector<Point> &circuit);

bool OnPath(const int &x, const int &y, const vector<Point> &path);
bool OnPath(const Point& p, const vector<Point> &path);

bool InPolygon(const Point &p, const vector<Point> &polygon, RECT rect);

void DrawLine(Graphics *graphic, const Point& p1, const Point& p2);

Point GetDir(const Point& p);

Point Zero();
