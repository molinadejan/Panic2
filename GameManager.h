#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"

#include "InputManager.h"
#include "Player.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

class GameManager
{
private:

	// 입력 관리
	InputManager* input;

	// 배경 이미지, 커버
	Image *image;

	// 플레이어
	Player *player;

	// 스크린 크기
	int screenW, screenH;

	// 배경 이미지 크기
	int imageW, imageH;

	vector<Point> opened;

	void DrawCover(Graphics *graphic);
	void DrawOpenedImage(Graphics *graphic);
	void DrawGame(Graphics *graphic);

public:
	GameManager();
	~GameManager();

	InputManager* Input() const { return input; }

	void Init();
	void Update();
	void Draw(HWND hWnd, HDC hdc);
};



#endif // !__GAMEMANAGER_H__
